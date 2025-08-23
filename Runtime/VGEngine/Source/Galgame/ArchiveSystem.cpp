#include "Galgame/ArchiveSystem.h"
#include <HCore/Include/System/HFileSystem.h>
#include <HCore/Include/File/nlohmann/json.hpp>

namespace VisionGal::GalGame
{
	ArchiveSystem::ArchiveSystem()
	{
		m_SaveDirectoryPath = m_BasePath / "GalGameSaves/";
		ReadArchives();
	}

	ArchiveSystem::~ArchiveSystem()
	{
	}

	void ArchiveSystem::UpdateSaveArchive(const SaveArchive& archive)
	{
		m_CurrentSaveArchiveState = archive;
	}

	bool ArchiveSystem::Initialise()
	{
		// 如果不存在
		if (!Horizon::HFileSystem::ExistsDirectory(m_SaveDirectoryPath))
		{
			Horizon::HFileSystem::CreateDirectory(m_SaveDirectoryPath);
		}

		return true;
	}

	void ArchiveSystem::ReadArchives()
	{
		for (int i = 1; i <= 99; ++i) {
			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << i;
			std::string saveNumber = oss.str();
			std::filesystem::path savePath = m_SaveDirectoryPath / (saveNumber + m_ArchiveExt);

			// 是否存在这个存档文件
			if (!Horizon::HFileSystem::ExistsFile(savePath))
				continue;

			// 存在就尝试打开
			std::ifstream file(savePath);
			if (file.is_open()) {

				try {
					nlohmann::json json = nlohmann::json::parse(file);

					ReadArchive(saveNumber, json);
					H_LOG_INFO("The galgame archive was parsed successfully: %s", saveNumber.c_str());
				}
				catch (const nlohmann::json::parse_error& e) {
					H_LOG_WARN("The galgame archive parsing error: %s", e.what());
				}
				catch (...) {
					H_LOG_WARN("The galgame archive parsing error: %s", saveNumber.c_str());
				}

				file.close();
			}
			else {
				//H_LOG_WARN("无法打开存档: %s", savePath.string().c_str());
			}
		}
	}

	void ArchiveSystem::ReadArchive(const String& saveNumber, nlohmann::json& json)
	{
		auto save = json.value("Save", nlohmann::json({}));

		// 反序列化本地数据到存档
		SaveArchive archive;
		archive.isValid = false;
		archive.isGalGameArchive = save.value("IsGalGameArchive", false);
		archive.version = save.value("Version", "");
		archive.scriptPath = save.value("ScriptPath", "");
		archive.line = save.value("Line", 0);

		archive.saveNumberString = save.value("SaveNumberString", "");
		archive.date = save.value("Date", "");
		archive.time = save.value("Time", "");
		archive.dateTime = save.value("DateTime", "");
		archive.description = save.value("Description", "");

		archive.isValid = archive.isGalGameArchive;
		m_Archives[saveNumber] = archive;
	}

	std::string ArchiveSystem::GetCurrentDateFormat()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

		// 转换为本地时间
		std::tm* localTime = std::localtime(&currentTime);

		// 格式化输出
		std::stringstream ss;
		ss << std::put_time(localTime, "%Y/%m/%d");
		return ss.str();
	}

	std::string ArchiveSystem::GetCurrentTimeFormat()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

		// 转换为本地时间
		std::tm* localTime = std::localtime(&currentTime);

		// 使用stringstream格式化时间
		std::stringstream ss;
		ss << std::put_time(localTime, "%H:%M:%S");
		return ss.str();
	}

	SaveArchive ArchiveSystem::SaveArchiveByNumber(const String& number)
	{
		std::filesystem::path savePath = m_SaveDirectoryPath / (number + m_ArchiveExt);

		// 设置存档的一些参数
		SaveArchive archive = m_CurrentSaveArchiveState;
		archive.date = GetCurrentDateFormat();
		archive.time = GetCurrentTimeFormat();
		archive.dateTime = archive.date + " " + archive.time;
		archive.isValid = true;
		archive.saveNumberString = number;

		// 序列化到json
		nlohmann::json json;
		json["Save"]["IsGalGameArchive"] = archive.isGalGameArchive;
		json["Save"]["Version"] = archive.version;
		json["Save"]["ScriptPath"] = archive.scriptPath;
		json["Save"]["Line"] = archive.line;

		json["Save"]["SaveNumberString"] = archive.saveNumberString;
		json["Save"]["Date"] = archive.date;
		json["Save"]["Time"] = archive.time;
		json["Save"]["DateTime"] = archive.dateTime;
		json["Save"]["Description"] = archive.description;

		std::string jsonStr = json.dump(2);

		// 写入JSON到文件
		try {
			std::ofstream file(savePath);
			if (file.is_open()) {
				file << jsonStr;
				file.close();
				H_LOG_INFO("The galgame archive has been saved successfully: %s", savePath.string().c_str());
			}
			else {
				H_LOG_WARN("Unable to open the galgame file: %s", savePath.string().c_str());
			}
		}
		catch (const std::exception& e) {
			H_LOG_WARN("The galgame archive saving failed: %s", e.what());
		}

		// 存档缓存到存档系统
		m_Archives[number] = archive;

		return archive;
	}

	SaveArchive ArchiveSystem::GetArchiveByNumber(const String& number)
	{
		auto result = m_Archives.find(number);
		if (result != m_Archives.end())
		{
			return m_Archives[number];
		}

		// 返回无效存档
		SaveArchive archive;
		archive.isGalGameArchive = false;
		archive.isValid = false;

		return archive;
	}

	bool ArchiveSystem::HasArchiveByNumber(const String& number)
	{
		auto result = m_Archives.find(number);
		if (result == m_Archives.end())
		{
			return false;
		}

		if (result->second.isGalGameArchive == false || result->second.isValid == false)
		{
			return false;
		}

		return true;
	}
}
