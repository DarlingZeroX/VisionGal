#pragma once
#pragma warning(push)
#pragma warning(disable : 26819)
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#pragma warning(pop)

#include "SDL3Input.h"
#include "../WindowInterface.h"
#include "../../CoreModuleDefinitions.h"
#include <vector>

#ifdef SDL3_WINDOW_SUPPORTED

namespace Horizon::SDL3
{
	enum SDL3_WINDOW_LAYER_RESULT
	{
		WINDOW_LAYER_RESULT_DEFAULT = 0,
		WINDOW_LAYER_RESULT_NO_PROPAGATE = 1 
	};

	struct Layer
	{
		virtual ~Layer() = default;

		virtual int ProcessEvent(const SDL_Event& event) = 0;
	};

	struct ISDL3Window :public IWindow
	{
		~ISDL3Window() override = default;

		virtual SDL_Window* GetSDLWindow() noexcept = 0;
		virtual const char* GetGLSLVersion() noexcept = 0;
		virtual void AddLayer(std::unique_ptr<Layer>&& layer) noexcept = 0;
		virtual void AddLayer(Layer* layer) noexcept = 0;
	};

	class CROSS_PLATFORM_API Window : public ISDL3Window
	{
	public:
		Window();
		Window(int width, int height);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		~Window() override;
	private:
		void Initialize(int width, int height);
		static SDL_HitTestResult HitTestCallback(SDL_Window* win, const SDL_Point* area, void* data);
	public:
		std::string GetTitle() const noexcept override;
		void SetTitle(const std::string& title) override;

		void* GetNativeWindow() noexcept override;
		EWindow GetWindowType() const noexcept override;

		unsigned WindowWidth() const noexcept override;
		unsigned WindowHeight() const noexcept override;

		void SetWindowPos(int x, int y) override;
		uint2 GetWindowPos() const override;

		void MinimizeWindow() override;
		void MaximizeWindow() override;
		void RestoreWindow() override;
		void SetFullscreen(bool fullscreen) override;

		void Close() override;

		int ProcessMessages() noexcept override;
		bool SwapWindow() override;
		int ProcessEvent(const SDL_Event& event);
		void Clear() noexcept override;
		void AddLayer(std::unique_ptr<Layer>&& layer) noexcept override;
		void AddLayer(Layer* layer) noexcept override;
		void AddWindowEventListener(WindowEventListener listener) override;
		bool IsCurrentWindowEvent(unsigned int windowID) override;

		SDL_Window* GetSDLWindow() noexcept override;
		const char* GetGLSLVersion() noexcept override;
	protected:
		void SetSDLWindowPtr(SDL_Window* ptr);
		void InitialMouseKeyboard();

	protected:
		std::string m_OpenGLVersion;
	private:
		SDL_Window* m_pWindow;

		std::vector<WindowEventListener> m_WindowEventListeners;
		std::vector<std::unique_ptr<Layer>> m_Layers;
		std::vector<Layer*> m_LayerPtr;

		Ref<Mouse> m_Mouse = nullptr;
		Ref<Keyboard> m_Keyboard = nullptr;

		bool m_OnResizeWindowMode = false;
	};

	struct CROSS_PLATFORM_API OpenGLWindow: public Window
	{
		~OpenGLWindow() override = default;

		virtual SDL_GLContext GetContext() = 0;
		bool SwapWindow() override;
	};
}

#endif
