#pragma once
//#include "RenderPipeline.h"
//#include "../EngineConfig.h"
//#include "../Core/Viewport.h"
//#include "../Render/Sprite.h"
#include "../Interface/GameEngineInterface.h"
#include <HCore/Include/Platform/SDL3/SDL3Window.h>
#include "RenderEngine.h"

namespace VisionGal
{
    struct CoreGameEngineContext : public IGameEngineContext
    {
        ~CoreGameEngineContext() override = default;

        IUISystem* GetUISystem() override;
        Horizon::SDL3::OpenGLWindow* GetWindow() override;
        Viewport* GetViewport() override;

        // 在渲染引擎设置各种渲染状态之前，添加渲染回调
        void AddBeforeRenderCallback(const String& callbackID, const std::function<void(OpenGL::RenderTarget2D*)>& callback) override;
        void ExecuteBeforeRenderCallbacks(OpenGL::RenderTarget2D* rt) override;
		 
        // 在渲染引擎渲染完成场景之后，解除各种渲染状态之后，添加渲染回调
        void AddAfterRenderCallback(const String& callbackID, const std::function<void(OpenGL::RenderTarget2D*)>& callback) override;
        void ExecuteAfterRenderCallbacks(OpenGL::RenderTarget2D* rt) override;

        IUISystem* uiSystem = nullptr;
        Horizon::SDL3::OpenGLWindow* window = nullptr;
        Viewport* viewport = nullptr;

        std::unordered_map<String, std::function<void(OpenGL::RenderTarget2D*)>> beforeRenderCallbacks;
        std::unordered_map<String, std::function<void(OpenGL::RenderTarget2D*)>> afterRenderCallbacks;
    };

    class VG_ENGINE_API CoreGameEngine: public IGameEngine
    {
    public:
        CoreGameEngine();
        ~CoreGameEngine() override = default;
        CoreGameEngine(const CoreGameEngine&) = delete;
        CoreGameEngine& operator=(const CoreGameEngine&) = delete;
        CoreGameEngine(CoreGameEngine&&) noexcept = default;
        CoreGameEngine& operator=(CoreGameEngine&&) noexcept = default;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;

        void Initialize(Horizon::SDL3::OpenGLWindow* window);
        Viewport* GetViewport() const { return m_Viewport; }

		void SetRenderFinalResultToScreen(bool enable);
    protected:
        void OnMainSceneChanged(const EngineEvent& evt);
    private:
        Viewport* m_Viewport;
        Ref<CoreRenderEngine> m_RenderEngine;

        std::vector<Ref<ISubGameEngine>> m_SubGameEngines;
        CoreGameEngineContext m_EngineContext;
    };


}
