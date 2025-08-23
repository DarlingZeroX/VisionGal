#include "Game/RenderPipeline.h"

#include "Engine/Manager/ShaderManager.h"
#include "Graphics/Interface/VGFX.h"
#include "Scene/Components.h"

namespace VisionGal
{
	void CoreRenderPipeline::Initialize(IGameEngineContext* context)
	{
		m_GameEngineContext = context;
	}

	void CoreRenderPipeline::SetScene(IScene* scene)
	{
		m_Scene = scene;
	}

	void CoreRenderPipeline::SetViewport(Viewport* viewport)
	{
		m_Viewport = viewport;

		m_Viewport->OnViewportEvent.Subscribe([this](const ViewportEvent& evt)
			{
				CreateRenderTargets(evt.NewViewportSize);
			});
	}

	void CoreRenderPipeline::OnUpdate()
	{
	}

	void CoreRenderPipeline::OnRender()
	{
		if (m_RenderBufferFinal == nullptr)
			return;

		VGFX::SetViewRect(0, 0,m_Viewport->Width() , m_Viewport->Height());

		auto view = m_Scene->GetWorld()->view<TransformComponent, SpriteRendererComponent>();

		if (m_Viewport->GetCameras().empty())
			return;

		auto& cameras= m_Viewport->GetCameras();
		ICamera* camera;
		for (auto cam : cameras)
			camera = cam;

		// 先清除帧缓冲
		{
			m_RenderBufferFinal->GetFrameBuffer()->Bind();
			glClearColor(0, 0, 0, 1);
			// 清除颜色缓冲区（和深度缓冲区，若启用了深度测试）
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_RenderBufferFinal->GetFrameBuffer()->Unbind();
		}

		// 执行场景渲染前回调
		if (m_GameEngineContext)
		{
			m_GameEngineContext->ExecuteBeforeRenderCallbacks(m_RenderBufferFinal.get());
		}

		// 渲染场景
		{
			VGFX::EnableDepthTest(true);
			// Set blending function for premultiplied alpha.
			glEnable(GL_BLEND);
			//glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_RenderBufferFinal->GetFrameBuffer()->Bind();

			// 渲染精灵
			view.each([this, &camera](TransformComponent& transform, SpriteRendererComponent& spriteRenderer) { // flecs::entity argument is optional
				if (transform.visible == false)
					return;

				auto* tex = spriteRenderer.sprite->GetITexture();
				auto* program = spriteRenderer.material->GetShaderProgram();

				VGFX::UseProgram(program);
				VGFX::SetTexture(0, "texture1", tex);
				VGFX::SetUniformFloat4("color", spriteRenderer.color);
				VGFX::SetUniformInt2("flip", spriteRenderer.flip);
				VGFX::SetUniformMatrix4("model", transform.model);
				VGFX::SetUniformMatrix4("projection", camera->GetMatrix());
				VGFX::RenderMesh(spriteRenderer.sprite->GetMesh());

				});

			// 渲染视频
			auto view1 = m_Scene->GetWorld()->view<TransformComponent, VideoPlayerComponent>();
			view1.each([this, &camera](TransformComponent& transform, VideoPlayerComponent& videoPlayer) { // flecs::entity argument is optional
				if (transform.visible == false)
					return;
				if (videoPlayer.videoPlayer == nullptr)
					return;
				if (videoPlayer.videoPlayer->GetSprite() == nullptr)
					return;

				videoPlayer.Update();

				auto* tex = videoPlayer.videoPlayer->GetSprite()->GetITexture();
				auto* program = ShaderManager::Get()->GetBuiltinProgram("SpriteDefault");

				VGFX::UseProgram(program);
				VGFX::SetTexture(0, "texture1", tex);
				VGFX::SetUniformFloat4("color", float4(1.0, 1.0, 1.0, 1.0));
				VGFX::SetUniformInt2("flip", int2(0, 0));
				VGFX::SetUniformMatrix4("model", transform.model);
				VGFX::SetUniformMatrix4("projection", camera->GetMatrix());
				VGFX::RenderMesh(videoPlayer.videoPlayer->GetSprite()->GetMesh());

				});

			m_RenderBufferFinal->GetFrameBuffer()->Unbind();
			VGFX::EnableDepthTest(false);
			glDisable(GL_BLEND);
		}

		// 执行渲染后回调
		if (m_GameEngineContext)
		{
			m_GameEngineContext->ExecuteAfterRenderCallbacks(m_RenderBufferFinal.get());
		}
	}

	void CoreRenderPipeline::CreateRenderTargets(float2 size)
	{
		m_RenderBufferFinal = OpenGL::RenderTarget2D::Create(size.x, size.y);
	}

	VGFX::ITexture* CoreRenderPipeline::GetRenderResult()
	{
		if (m_RenderBufferFinal == nullptr)
			return nullptr;

		return m_RenderBufferFinal->GetTexture();
	}
}
