#pragma once


#include<iostream>
#include<deque>
#include<sstream>

#include <HCore/Include/Core/HException.h>
#include "OpenGL.h"

VISIONGAL_OPENGL_NAMESPACE_BEGIN

	class Exception : public Horizon::EngineException
	{
	public:
		static void ClearError();

		static bool CheckError(const char* function, const char* file, int line);

	public:
		Exception(int line, const char* file) noexcept :EngineException(line, file) {}
		const char* GetWindowType() const noexcept override { return "OpenGL Graphic Exception"; }
		const char* what() const noexcept override;
		virtual std::string GetErrorInfo() const noexcept = 0;
	};


	class InitException : public Exception
	{
	public:
		InitException(int line, const char* file) noexcept :Exception(line, file) {}
		const char* GetWindowType() const noexcept override { return "OpenGL Graphic Init Exception"; }

		std::string GetErrorInfo() const noexcept;
	};

VISIONGAL_OPENGL_NAMESPACE_END
