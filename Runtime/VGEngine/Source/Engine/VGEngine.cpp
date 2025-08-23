#include "Engine/VGEngine.h"
#include "Resource/ResourceManager.h"
#include "Core/Core.h"
#include "Core/EventBus.h"
#include "Core/VFS.h"
#include "Engine/Manager.h"
#include "Scene/GameActorFactory.h"
#include <HCore/Include/Platform/NativeFileDialog/portable-file-dialogs.h>

#include "HCore/Include/Core/HStringTools.h"

namespace VisionGal
{
	VGEngine::VGEngine()
	{
		m_LastUpdateTime = std::chrono::high_resolution_clock::now();

		// 断言错误记录
		//_CrtSetReportHook([](int reportType, char* message, int* retVal)
		//{
		//	H_LOG_ERROR(message);
		//	return 0;
		//});
	}

	VGEngine* VGEngine::Get()
	{
		static VGEngine* s_VGEngine = new VGEngine();
		return s_VGEngine;
	}

	bool VGEngine::LoadProject()
	{
		Initialize();

		// 加载项目配置
		ProjectSettings::LoadProjectSettings();

		CreateResourceManagers();
		return true;
	}

	ProjectSettings& VGEngine::GetProjectConfig()
	{
		return m_ProjectConfig;
	}

	void VGEngine::LoadEditorMainScene()
	{
		auto& setting = ProjectSettings::GetProjectSettings().Editor;
		m_Scene = GetSceneManager()->LoadScene(setting.MainScene);

		if (m_Scene == nullptr)
		{
			m_Scene = CreateRef<Scene>();
			GetSceneManager()->SetCurrentScene(m_Scene);
		}
	}

	void VGEngine::Initialize()
	{
        Core::Initialize();
	}

	void VGEngine::OnUpdateSubSystem(float deltaTime)
	{
		GetViewportManager()->FrameUpdate();
	}

	void VGEngine::LoadProjectMainScene()
	{
		auto& setting = ProjectSettings::GetProjectSettings().Application;
		m_Scene = GetSceneManager()->LoadScene(setting.RunningMainScene);

		if (m_Scene == nullptr)
		{
			std::string error = Horizon::HStringTools::Format("Invalid project main scene %s", setting.RunningMainScene.c_str());
			pfd::message("Error", error, pfd::choice::ok, pfd::icon::error);

			RequestExit();
		}
	}

	void VGEngine::Run() {
		using clock = std::chrono::high_resolution_clock;
		const double FIXED_TIME = 1.0 / 60.0;
		const double MAX_FRAME_TIME = 0.25; // 防止长帧

		double updateLag = 0.0;
		auto lastTime = clock::now();

		while (ProcessEvents()) {
			// 1. 计算时间间隔 (deltaTime)
			auto now = clock::now();
			double deltaTime = std::chrono::duration<double>(now - lastTime).count();
			deltaTime = std::min(deltaTime, MAX_FRAME_TIME);
			lastTime = now;

			updateLag += deltaTime;

			// 2. 固定更新
			while (updateLag >= FIXED_TIME) {
				//FixedUpdate(FIXED_TIME);
				updateLag -= FIXED_TIME;
			}

			// 3. 渲染和应用更新
			//float alpha = static_cast<float>(updateLag / FIXED_TIME);
			OnUpdateSubSystem(static_cast<float>(deltaTime));
			OnApplicationUpdate(static_cast<float>(deltaTime));
			//RenderWithInterpolation(alpha);

			// 4. 可选帧率控制
			double frameTime = std::chrono::duration<double>(clock::now() - now).count();
			if (frameTime < FIXED_TIME) {
				std::this_thread::sleep_for(std::chrono::duration<double>(FIXED_TIME - frameTime));
			}
		}
	}

	void VGEngine::AddApplication(Ref<IEngineApplication> layer)
	{
		m_Applications.push_back(layer);
	}

	void VGEngine::OnApplicationUpdate(float deltaTime)
	{
        for (auto& app : m_Applications)
        {
			app->MakeCurrentRenderContext();
			app->OnApplicationUpdate(deltaTime);
        }
	}

    bool VGEngine::ProcessEvents()
	{
#if defined RMLUI_PLATFORM_EMSCRIPTEN

		// Ideally we would hand over control of the main loop to emscripten:
		//
		//  // Hand over control of the main loop to the WebAssembly runtime.
		//  emscripten_set_main_loop_arg(EventLoopIteration, (void*)user_data_handle, 0, true);
		//
		// The above is the recommended approach. However, as we don't control the main loop here we have to make due with another approach. Instead, use
		// Asyncify to yield by sleeping.
		// Important: Must be linked with option -sASYNCIFY
		// See https://emscripten.org/docs/porting/asyncify.html for more information.

		// 理想情况下，我们应该将主循环的控制权交给 Emscripten：
		//
		//   // 将主循环的控制权交给 WebAssembly 运行时
		//   emscripten_set_main_loop_arg(EventLoopIteration, (void*)user_data_handle, 0, true);
		//
		// 上面是推荐的方式。然而，由于我们在这里无法控制主循环，因此只能采用另一种方式。
		// 我们将使用 Asyncify，通过休眠的方式让出控制权。
		// 重要提示：链接时必须使用选项 -sASYNCIFY
		// 更多信息请参考：https://emscripten.org/docs/porting/asyncify.html

		emscripten_sleep(1);

#endif
		bool has_event = false;
		bool result = m_Running;
		m_Running = true;

		SDL_PumpEvents();

		SDL_Event ev;
		//if (m_PowerSave)
		//	has_event = SDL_WaitEventTimeout(&ev, static_cast<int>(Rml::Math::Min(context->GetNextUpdateDelay(), 10.0) * 1000));
		//else
		//	has_event = SDL_PollEvent(&ev);
		has_event = SDL_PollEvent(&ev);

		while (has_event)
		{
			switch (ev.type)
			{
			case SDL_EVENT_QUIT:
				return false;
			//case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			//	return false;
			}

			// 交给窗口处理事件
			for (auto& app : m_Applications)
			{
				app->MakeCurrentRenderContext();
				app->ProcessEvent(ev);
			}

			has_event = SDL_PollEvent(&ev);
		}

		return result;
	}

    void VGEngine::Shutdown()
    {
		SDL_Quit();
    }

    void VGEngine::RequestExit()
    {
        m_Running = false;
    }

}
