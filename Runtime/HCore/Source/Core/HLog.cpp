﻿#include "pch.h"
#include "Core/HLog.h"
#include "Core/HStringTools.h"
#include <SDL3/SDL_log.h>
#include <sstream>
#include <string>
#include <iostream>

#include "Core/HLocalization.h"

namespace Horizon
{
	struct HCoreLoggerImp
	{
		static HCoreLoggerImp* GetInstance()
		{
			static HCoreLoggerImp s_Imp;
			return &s_Imp;
		}

		void NotifyListeners(HLogLevel level, const std::string& message) const
		{
			for (auto& listener: LogListeners)
			{
				listener(level, message);
			}
		}

		std::vector<HCoreLogger::LogCallback> LogListeners;
	};

	// ANSI颜色代码
	enum class Color {
		RESET = 0,
		RED = 31,
		GREEN = 32,
		YELLOW = 33,
		BLUE = 34,
		MAGENTA = 35,
		CYAN = 36,
		WHITE = 37
	};

	namespace LogColor
	{	// 设置文本颜色
		static std::string setColor(Color color) {
			return "\033[" + std::to_string(static_cast<int>(color)) + "m";
		}

		std::string Warn(){ return setColor(Color::YELLOW); }
		std::string Error(){ return setColor(Color::RED); }
		std::string Critical(){ return setColor(Color::BLUE); }
		std::string Reset() { return setColor(Color::RESET); }
	};

	void HCoreLogger::Error(const char* fmt, ...)
	{
		std::string fmtString = fmt;
		fmtString = GetTranslateText(fmtString);

		va_list args;
		va_start(args, fmt);
	
		std::string error = HStringTools::Format(fmtString.c_str(), args);

		va_end(args);

		std::ostringstream ostream;
		ostream << LogColor::Error() << "[Error] " << error << LogColor::Reset() << std::endl;

		//SDL_LogError(3,"[Error] %s", error.c_str());
		SDL_LogError(3, ostream.str().c_str());

		HCoreLoggerImp::GetInstance()->NotifyListeners(HLogLevel::Error, error);
	}

	void HCoreLogger::Info(const char* fmt, ...)
	{
		std::string fmtString = fmt;
		fmtString = GetTranslateText(fmtString);

		va_list args;
		va_start(args, fmt);

		std::string info = HStringTools::Format(fmtString.c_str(), args);

		va_end(args);

		std::ostringstream ostream;
		ostream << "[Info] " << info << std::endl;

		//SDL_LogInfo(0,"[Info] %s", info.c_str());
		SDL_LogInfo(0, ostream.str().c_str());

		HCoreLoggerImp::GetInstance()->NotifyListeners(HLogLevel::Info, info);
	}

	void HCoreLogger::Warn(const char* fmt, ...)
	{
		std::string fmtString = fmt;
		fmtString = GetTranslateText(fmtString);

		va_list args;
		va_start(args, fmt);

		std::string warn = HStringTools::Format(fmtString.c_str(), args);

		va_end(args);

		std::ostringstream ostream;
		ostream << LogColor::Warn() << "[Warn] " << warn << LogColor::Reset() << std::endl;

		//SDL_LogError(1,"[Warn] %s", warn.c_str());
		SDL_LogError(1, ostream.str().c_str());

		HCoreLoggerImp::GetInstance()->NotifyListeners(HLogLevel::Warn, warn);
	}

	void HCoreLogger::Critical(const char* fmt, ...)
	{
		std::string fmtString = fmt;
		fmtString = GetTranslateText(fmtString);

		va_list args;
		va_start(args, fmt);

		std::string critical = HStringTools::Format(fmtString.c_str(), args);

		va_end(args);

		std::ostringstream ostream;
		ostream << LogColor::Critical() << "[Critical] " << critical << LogColor::Reset() << std::endl;

		//SDL_LogError(2,"[Critical] %s", critical.c_str());
		SDL_LogError(2, ostream.str().c_str());

		HCoreLoggerImp::GetInstance()->NotifyListeners(HLogLevel::Critical, critical);
	}

	void HCoreLogger::Error(const std::string& fmt, ...)
	{
		va_list args;
		va_start(args, &fmt);
		Error(fmt.c_str(), args);
		va_end(args);
	}

	void HCoreLogger::Info(const std::string& fmt, ...)
	{
		va_list args;
		va_start(args, &fmt);
		Info(fmt.c_str(), args);
		va_end(args);
	}

	void HCoreLogger::Warn(const std::string& fmt, ...)
	{
		va_list args;
		va_start(args, &fmt);
		Warn(fmt.c_str(), args);
		va_end(args);
	}

	void HCoreLogger::Critical(const std::string& fmt, ...)
	{
		va_list args;
		va_start(args, &fmt);
		Critical(fmt.c_str(), args);
		va_end(args);
	}

	void HCoreLogger::AddListener(LogCallback callback)
	{
		HCoreLoggerImp::GetInstance()->LogListeners.push_back(callback);
	}
}


