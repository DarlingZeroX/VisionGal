#pragma once
#include "Input/HNativeMouse.h"
#include "Input/HNativeKeyboard.h"

namespace Horizon
{
	struct CROSS_PLATFORM_API HNativeKeyboard
	{
		static HKeyboard& Get();
		static HKeyboard* GetPtr();
		static HKeyboardContext& GetContext();
	};

	struct CROSS_PLATFORM_API HNativeMouse
	{
		static HMouse& Get();
		static HMouse* GetPtr();
		static HMouseContext& GetContext();
	};

	struct CROSS_PLATFORM_API HInput
	{
		static HMouse& Mouse();
		static HKeyboard& Keyboard();

		static void FixedUpdate();
		static void FrameUpdate();

		static void Update();
	};
}
