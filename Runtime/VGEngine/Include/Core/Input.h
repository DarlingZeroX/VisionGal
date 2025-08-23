#pragma once
#include "Core.h"
#include "Viewport.h"
#include <HCore/Include/Platform/SDL3/SDL3Input.h>
#include <HCore/Include/System/Input/HKeyboardBase.h>
#include <HCore/Include/Platform/SDL3/SDL3Window.h>

namespace VisionGal
{
	struct VG_ENGINE_API Input: public Horizon::SDL3::Layer
	{
		Input();

		static bool GetMouseButtonDown(int button);
		static bool GetMouseButtonUp(int button);
		static bool GetMouseButtonHeld(int button);

		static bool GetKey(Horizon::HKeycode code);
		static bool GetKeyDown(Horizon::HKeycode code);
		static bool GetKeyUp(Horizon::HKeycode code);

		static bool GetKeyName(const String& name);
		static bool GetKeyNameDown(const String& name);
		static bool GetKeyNameUp(const String& name);

		static Input* Get();

		int ProcessEvent(const SDL_Event& event) override;
		void AttachWindow(Horizon::SDL3::Window* window);
		void AttachViewport(Viewport* viewport);

		static Horizon::HMouse& GetMouse();
		static Horizon::HKeyboard& GetKeyboard();

		void Update();
	private:
		Ref<Horizon::SDL3::Mouse> m_Mouse = nullptr;
		Ref<Horizon::SDL3::Keyboard> m_Keyboard = nullptr;

		Viewport* m_Viewport;
		std::unordered_map<std::string, Horizon::HKeycode> m_NameKeycodeMap;
	};

}
