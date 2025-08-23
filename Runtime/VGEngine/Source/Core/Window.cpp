#include "Core/Window.h"
#include "Graphics/OpenGL/OpenGL.h"

namespace VisionGal
{
	VGWindow::VGWindow()
	{
		this->AddWindowEventListener([this](const Horizon::Events::HWindowEvent& evt)
			{
				OnWindowEvent.Invoke(evt);
			});
	}

	bool VGWindow::Initialize(const char* window_name, int width, int height, bool allow_resize)
	{
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO))
			return false;

		// Submit click events when focusing the window.
		SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

		// GL 3.3 Core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		// ���� Backbuffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);    // ������Ȼ�������С

		// ���ù������ԣ���SDL3֧�֣�  
		SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

		const float window_size_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
		SDL_PropertiesID props = SDL_CreateProperties();
		SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, window_name);
		SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
		SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
		SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, int(width));
		SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, int(height));
		SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
		SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, allow_resize);
		SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);
		SDL_Window* window = SDL_CreateWindowWithProperties(props);
		SDL_DestroyProperties(props);

		SetSDLWindowPtr(window);

		if (!window)
		{
			H_LOG_ERROR("SDL error on create window: %s", SDL_GetError());
			return false;
		}

		m_GLContext = SDL_GL_CreateContext(GetSDLWindow());
		m_OpenGLVersion = "#version 330";

		if (!m_GLContext) {
			SDL_Log("OpenGL context creation failed: %s", SDL_GetError());
			return false;
		}

		// ��ʼ��GLAD
		//if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		//	H_LOG_ERROR("Failed to initialize GLAD");
		//	return 1;
		//}
		const int gl_version = gladLoaderLoadGL();
		if (gl_version == 0)
		{
			H_LOG_ERROR("Failed to initialize OpenGL context.");
			return false;
		}

		// ��ʼ�����ͼ���
		//InitialMouseKeyboard();

		//ע�⣺�������ڰ����ַ���ʱ���� SDL ���ı�����ģʽ��
		//SDL_StartTextInput(window);   // ��Ӧ�ÿ�ʼʱ����

		return true;
	}
}
