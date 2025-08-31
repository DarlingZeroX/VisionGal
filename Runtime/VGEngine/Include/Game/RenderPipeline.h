#pragma once
#include "../Core/Viewport.h"
#include "../Interface/GameEngineInterface.h"

#include "../Graphics/OpenGL/RenderTarget.h"

namespace VisionGal
{
    class CoreRenderPipeline: public IRenderPipeline
    {
    public:
        CoreRenderPipeline() = default;
        ~CoreRenderPipeline() override = default;
        CoreRenderPipeline(const CoreRenderPipeline&) = delete;
        CoreRenderPipeline& operator=(const CoreRenderPipeline&) = delete;
        CoreRenderPipeline(CoreRenderPipeline&&) noexcept = default;
        CoreRenderPipeline& operator=(CoreRenderPipeline&&) noexcept = default;

        void Initialize(IGameEngineContext* context);

        void SetScene(IScene* scene);
        void SetViewport(Viewport* viewport);
        void OnUpdate() override;
        void OnRender() override;

		void RenderScene(IScene* scene,ICamera* camera ,uint pipelineIndex);

        void CreateRenderTargets(float2 size);

        VGFX::ITexture* GetRenderResult();
    private:
        IGameEngineContext* m_GameEngineContext = nullptr;
        IScene* m_Scene = nullptr;
        Viewport* m_Viewport = nullptr;

        Ref<OpenGL::RenderTarget2D> m_RenderBufferFinal;
    };
}
