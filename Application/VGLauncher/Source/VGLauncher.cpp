#include "VGLauncher.h"
#include "MainWindow.h"
#include <HCore/Include/System/HFileSystem.h>
#include <VGImgui/IncludeImGuiEx.h>
#include <VGImgui/Include/ImGuiLayer/SDL3Decorator.h>
#include <VGImgui/Include/Imgui/imgui_impl_opengl3.h>
#include <VGEditorFramework/Framework.h>
#include <VGEngine/Include/Engine/UISystem.h>
#include "VGLauncherData.h"
#include "VGEditorFramework/Include/EditorCore/EditorCore.h"
#include "VGEngine/Include/Core/VFS.h"

namespace VisionGal::Editor
{
	VGLauncher::VGLauncher()
		:m_GameEngine(nullptr)
	{
	}

	VGLauncher::~VGLauncher()
	{

	}
	 
	void VGLauncher::Initialize()
	{
		auto& editorConfig = EditorCore::GetEditorPreferences().Editor;

		// 初始化启动器窗口数据
		auto editorName = "VisionGal Launcher";
		auto windowWidth = editorConfig.EditorWindowWidth;
		auto windowHeight = editorConfig.EditorWindowHeight;

		// 创建启动器窗口
		m_LauncherWindow = CreateRef<VGWindow>();
		m_LauncherWindow->Initialize(editorName, windowWidth, windowHeight,true);

		//m_GameEngine = CreateRef<CoreGameEngine>();
		//m_GameEngine->Initialize(m_LauncherWindow.get());

		// 添加ImGui Layer
		AddImguiLayer();
		// 初始化编辑器UI
		InitializeEditorUI();
		// 初始化启动器面板
		InitializeLauncherPanels();
	}

	void VGLauncher::AddApplicationLayer(IEngineApplicationLayer* layer)
	{
	}

	void VGLauncher::InitializeLauncherPanels()
	{
		auto* editor = PanelManager::GetInstance();

		//auto mainWindow = CreateRef<EditorMainWindow>();
		//editor->AddPanelWithID("EditorMenuBar", CreateRef<EditorMenuBar>());

		editor->AddPanelWithID("LauncherMainWindow", CreateRef<VGLauncherMainWindow>());
	}

	void VGLauncher::InitializeEditorUI()
	{
		auto& editorConfig = EditorCore::GetEditorPreferences().Editor;

		// 设置本地语言
		EditorLoadLanguage(editorConfig.EditorLanguage);

		// 设置主题
		EditorStyle::DarkTheme();

		// 创建Imgui的UI任务执行器
		ImGuiEx::ImTaskManager::CreateManager();
	}

	void VGLauncher::AddImguiLayer()
	{
		// 添加ImGui Layer
		m_LauncherWindow->AddLayer(std::make_unique<ImGuiEx::Opengl3ImGuiWindowLayer>(m_LauncherWindow.get()));
		m_ImguiOpengl3Layer = std::make_unique<ImguiOpengl3Layer>(m_LauncherWindow.get(), m_LauncherWindow->GetContext());

		ImGuiIO& io = ImGui::GetIO();

		auto& editorConfig = EditorCore::GetEditorPreferences().Editor;

		// 读取中文字体
		VFS::SafeReadFileFromVFS(Core::GetEngineResourcePathVFS() + "fonts/msyh.ttc", [&](const VFS::DataRef& data) {
			ImGuiIO& io = ImGui::GetIO();
			ImFontConfig icons_config;
			icons_config.FontDataOwnedByAtlas = false;

			//io.Fonts->AddFontFromMemoryTTF(data->data(), data->size(), 17, &icons_config, ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			io.Fonts->AddFontFromMemoryTTF(data->data(), data->size(), 20, &icons_config, ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());

			return 0;
			});

		// 读取图标字体
		VFS::SafeReadFileFromVFS(Core::GetEngineResourcePathVFS() + "fonts/fa-regular-400.ttf", [&](const VFS::DataRef& data) {
			ImGuiIO& io = ImGui::GetIO();
			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

			ImFontConfig icons_config;
			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.GlyphOffset = ImVec2(0, 2);
			icons_config.FontDataOwnedByAtlas = false;

			io.Fonts->AddFontFromMemoryTTF(data->data(), data->size(), 20, &icons_config, icons_ranges);
			return 0;
			});

		// 构建字体图集
		io.Fonts->Build();
	}

	void VGLauncher::OnRender()
	{
		if (m_GameEngine)
		{
			m_GameEngine->OnRender();
		}
	}

	void VGLauncher::OnUpdate(float deltaTime)
	{
		if (m_GameEngine)
		{
			m_GameEngine->OnUpdate(deltaTime);
		}

		PanelManager::GetInstance()->OnUpdate(deltaTime);
	}

	void VGLauncher::OnFixedUpdate()
	{
		PanelManager::GetInstance()->OnFixedUpdate();
	}

	void VGLauncher::OnGUI()
	{
		m_ImguiOpengl3Layer->BeginFrame();
		PanelManager::GetInstance()->OnGUI();
		ImGuiEx::ImTaskManager::GetInstance().RenderUITask();
		ImGuiEx::RenderNotifications();
		m_ImguiOpengl3Layer->EndFrame();
	}

	void VGLauncher::OnApplicationUpdate(float deltaTime)
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OnFixedUpdate();
		OnUpdate(deltaTime);
		OnRender();
		OnGUI();

		SDL_GL_SwapWindow(m_LauncherWindow->GetSDLWindow());
	}

	int VGLauncher::ProcessEvent(const SDL_Event& event)
	{
		return m_LauncherWindow->ProcessEvent(event);
	}

	void VGLauncher::MakeCurrentRenderContext()
	{
		SDL_GL_MakeCurrent(m_LauncherWindow->GetSDLWindow(), m_LauncherWindow->GetContext());
	}
}
