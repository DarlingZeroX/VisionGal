#include "Graphics/GFX/GFX.h"
#include "Engine/Backend.h"
#include "Engine/VGWindow.h"
#include <SDL3/SDL.h>

VISIONGAL_GFX_NAMESPACE_BEGIN

void Initliaze()
{
    VGWindow* window = VGBackend::Get()->GetWindow();

    // 确保上下文是当前的
    //SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetContext());

    bgfx::PlatformData pd;
    pd.nwh = window->GetNativeWindow();
    //pd.context = window->GetContext();     // OpenGL上下文（bgfx会自动创建）
    pd.backBuffer = nullptr;               // 后台缓冲区
    pd.backBufferDS = nullptr;             // 深度模板缓冲区

    // 初始化bgfx
    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL; // 选择渲染器类型
    init.platformData = pd;
    init.resolution.width = window->WindowWidth();
    init.resolution.height = window->WindowHeight();
    init.resolution.reset = BGFX_RESET_VSYNC;
    //init.resolution.reset = BGFX_RESET_NONE;

    if (!bgfx::init(init)) {
        SDL_Log("bgfx初始化失败");
        return;
    }


    bgfx::setViewRect(0, 0, 0, window->WindowWidth(), window->WindowHeight());

    VGBackend::Get()->GetWindow()->OnWindowEvent.Subscribe([](const Horizon::Events::HWindowEvent& e) {

        // 更新bgfx视图尺寸
        bgfx::setViewRect(0, 0, 0, e.data1, e.data2);

        });
}

void BeginFrame()
{
    VGWindow* window = VGBackend::Get()->GetWindow();

    // 设置视图
    int width = window->WindowWidth();
    int height = window->WindowHeight();

    // 设置视图
    //bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 255, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);
}

void EndFrame()
{
    bgfx::touch(0);  // 确保视图被更新
    //bgfx::frame();
}

void ShutDown()
{
    // 关闭bgfx
    bgfx::shutdown();
}

VISIONGAL_GFX_NAMESPACE_END


