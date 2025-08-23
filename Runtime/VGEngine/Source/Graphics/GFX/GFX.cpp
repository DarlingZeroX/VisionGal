#include "Graphics/GFX/GFX.h"
#include "Engine/Backend.h"
#include "Engine/VGWindow.h"
#include <SDL3/SDL.h>

VISIONGAL_GFX_NAMESPACE_BEGIN

void Initliaze()
{
    VGWindow* window = VGBackend::Get()->GetWindow();

    // ȷ���������ǵ�ǰ��
    //SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetContext());

    bgfx::PlatformData pd;
    pd.nwh = window->GetNativeWindow();
    //pd.context = window->GetContext();     // OpenGL�����ģ�bgfx���Զ�������
    pd.backBuffer = nullptr;               // ��̨������
    pd.backBufferDS = nullptr;             // ���ģ�建����

    // ��ʼ��bgfx
    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL; // ѡ����Ⱦ������
    init.platformData = pd;
    init.resolution.width = window->WindowWidth();
    init.resolution.height = window->WindowHeight();
    init.resolution.reset = BGFX_RESET_VSYNC;
    //init.resolution.reset = BGFX_RESET_NONE;

    if (!bgfx::init(init)) {
        SDL_Log("bgfx��ʼ��ʧ��");
        return;
    }


    bgfx::setViewRect(0, 0, 0, window->WindowWidth(), window->WindowHeight());

    VGBackend::Get()->GetWindow()->OnWindowEvent.Subscribe([](const Horizon::Events::HWindowEvent& e) {

        // ����bgfx��ͼ�ߴ�
        bgfx::setViewRect(0, 0, 0, e.data1, e.data2);

        });
}

void BeginFrame()
{
    VGWindow* window = VGBackend::Get()->GetWindow();

    // ������ͼ
    int width = window->WindowWidth();
    int height = window->WindowHeight();

    // ������ͼ
    //bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 255, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);
}

void EndFrame()
{
    bgfx::touch(0);  // ȷ����ͼ������
    //bgfx::frame();
}

void ShutDown()
{
    // �ر�bgfx
    bgfx::shutdown();
}

VISIONGAL_GFX_NAMESPACE_END


