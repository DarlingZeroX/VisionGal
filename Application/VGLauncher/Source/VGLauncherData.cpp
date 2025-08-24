// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// For the latest information, see https://github.com/DarlingZeroX/VisionGal
// See the LICENSE file in the project root for details.

#include "VGLauncherData.h"
#include <HCore/Include/File/nlohmann/json.hpp>
#include <HCore/Include/System/HFileSystem.h>

namespace VisionGal::Editor
{
	struct VGLauncherDataImp
	{
		VGLauncherDataImp()
		{

		}

		~VGLauncherDataImp()
		{
			VGLauncherData::SaveLauncherData();
		}

		static VGLauncherDataImp* GetInstance()
		{
			static VGLauncherDataImp imp;
			return &imp;
		}

		void Initialize()
		{
		}

		/// @brief 全局启动器数据
		VGLauncherData m_VGLauncherData;
	};

	/// @brief 将 VGProjectItem 转换为 JSON
	void to_json(nlohmann::json& j, const VGProjectItem& item)
	{
		j = nlohmann::json{
			{"Name", item.Name},
			{"Path", item.Path}
		};
	}

	/// @brief 将 JSON 转换为 VGProjectItem
	void from_json(const nlohmann::json& j, VGProjectItem& item)
	{
		j.at("Name").get_to(item.Name);
		j.at("Path").get_to(item.Path);
	}

	// @brief 将 VGLauncherData 转换为 JSON
	void to_json(nlohmann::json& j, const VGLauncherData& data)
	{
		j = nlohmann::json{
			{"LastProjectCreateDirectory", data.m_LastProjectCreateDirectory},
			{"Projects", data.m_Projects}
		};
	}
	
	/// @brief 将 JSON 转换为 VGLauncherData
	void from_json(const nlohmann::json& j, VGLauncherData& data)
	{
		j.at("LastProjectCreateDirectory").get_to(data.m_LastProjectCreateDirectory);
		j.at("Projects").get_to(data.m_Projects);
	}

	VGLauncherData::VGLauncherData()
	{
		m_LauncherDataFilePath = "Data/VGLauncher/VGLauncherData.json";
	}

	VGLauncherData::VGLauncherData(const std::filesystem::path& dataPath)
	{
		m_LauncherDataFilePath = dataPath;
	}

	bool VGLauncherData::Load(VGLauncherData& data)
	{
		/// @brief 从文件加载启动器数据
		auto dataFilePath = data.m_LauncherDataFilePath;
		std::string text;
		if (Horizon::HFileSystem::ReadTextFromFile(data.m_LauncherDataFilePath, text))
		{
			// 尝试解析 JSON 数据
			try {
				nlohmann::json json = nlohmann::json::parse(text);
				data = json.get<VGLauncherData>();
				data.m_LauncherDataFilePath = dataFilePath;
				return true;
			}
			catch (const nlohmann::json::parse_error& e) {

			}
			catch (...)
			{

			}

			// 移除无效的项目
			data.RemoveInvalidProjects();
		}

		return false;
	}

	bool VGLauncherData::Save(VGLauncherData& data)
	{
		// 如果目录不存在则创建
		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data");
		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data/VGLauncher");

		// 将数据转换为 JSON 字符串
		nlohmann::json json;
		json = data;
		std::string jsonStr = json.dump(2);

		// 将 JSON 字符串写入文件
		return Horizon::HFileSystem::WriteTextToFile(data.m_LauncherDataFilePath, jsonStr);
	}

	void VGLauncherData::LoadLauncherData()
	{
		Load(VGLauncherDataImp::GetInstance()->m_VGLauncherData);
	}

	void VGLauncherData::SaveLauncherData()
	{
		Save(VGLauncherDataImp::GetInstance()->m_VGLauncherData);
	}

	VGLauncherData& VGLauncherData::GetLauncherData()
	{
		return VGLauncherDataImp::GetInstance()->m_VGLauncherData;
	}

	bool VGLauncherData::AddProject(const VGProjectItem& project)
	{
		// 检查项目是否已存在
		for (const auto& existingProject : m_Projects)
		{
			if (existingProject.Path == project.Path)
			{
				// 如果项目已存在，则不添加
				return false;
			}
		}

		if (Horizon::HFileSystem::ExistsDirectory(project.Path) == false)
			return false;

		m_Projects.push_back(project);

		return true;
	}

	bool VGLauncherData::RemoveProject(int index)
	{
		if (index < 0)
			return false;

		if (index >= m_Projects.size())
			return false;

		// 删除项目
		m_Projects.erase(m_Projects.begin() + index);
	}

	const std::vector<VGProjectItem>& VGLauncherData::GetProjects() const
	{
		return m_Projects;
	}

	const std::string& VGLauncherData::GetLastProjectCreateDirectory() const
	{
		return m_LastProjectCreateDirectory;
	}

	void VGLauncherData::SetLastProjectCreateDirectory(const std::string& directory)
	{
		m_LastProjectCreateDirectory = directory;
	}

	void VGLauncherData::RemoveInvalidProjects()
	{
		// 移除路径不存在的项目
		m_Projects.erase(std::remove_if(m_Projects.begin(), m_Projects.end(),
			[](const VGProjectItem& project)
			{
				return !Horizon::HFileSystem::ExistsDirectory(project.Path);
			}), m_Projects.end());
	}
}
