#include "pch.h"
#include "System/HInput.h"

namespace Horizon
{
	//======================================================================================
	// HNativeKeyboard
	//======================================================================================
	static HKeyboard keyboard;

	HKeyboard& HNativeKeyboard::Get()
	{
		return keyboard;
	}

	HKeyboard* HNativeKeyboard::GetPtr()
	{
		return &keyboard;
	}

	HKeyboardContext& HNativeKeyboard::GetContext()
	{
		return keyboard.GetContext();
	}

	//======================================================================================
	// HNativeMouse
	//======================================================================================
	static HMouse mouse;

	HMouse& HNativeMouse::Get()
	{
		return mouse;
	}

	HMouse* HNativeMouse::GetPtr()
	{
		return &mouse;
	}

	HMouseContext& HNativeMouse::GetContext()
	{
		return const_cast<HMouseContext&>(mouse.GetContext());
	}

	HMouse& HInput::Mouse()
	{
		return HNativeMouse::Get();
	}

	HKeyboard& HInput::Keyboard()
	{
		return HNativeKeyboard::Get();
	}

	void HInput::FixedUpdate()
	{
		Mouse().FixedUpdate();
	}

	void HInput::FrameUpdate()
	{
		Mouse().FrameUpdate();
		Keyboard().Update();
	}

	void HInput::Update()
	{
	}
}