#include "VGLauncherData.h"

#include "HCore/Include/File/nlohmann/json.hpp"
#include "HCore/Include/System/HFileSystem.h"

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

	/// @brief 将 VGLauncherData 转换为 JSON
	void to_json(nlohmann::json& j, const VGLauncherData& data)
	{
		j = nlohmann::json{
			{"LastProjectCreateDirectory", data.LastProjectCreateDirectory},
			{"Projects", data.Projects}
		};
	}

	/// @brief 将 JSON 转换为 VGLauncherData
	void from_json(const nlohmann::json& j, VGLauncherData& data)
	{
		j.at("LastProjectCreateDirectory").get_to(data.LastProjectCreateDirectory);
		j.at("Projects").get_to(data.Projects);
	}

	VGLauncherData::VGLauncherData()
	{
	}

	void VGLauncherData::Load(VGLauncherData& settings)
	{
		/// @brief 从文件加载启动器数据
		std::string text;
		if (Horizon::HFileSystem::ReadTextFromFile("Data/VGLauncher/VGLauncherData.json", text))
		{
			// 尝试解析 JSON 数据
			try {
				nlohmann::json json = nlohmann::json::parse(text);
				settings = json.get<VGLauncherData>();
			}
			catch (const nlohmann::json::parse_error& e) {

			}
			catch (...)
			{

			}
		}
	}

	void VGLauncherData::Save(VGLauncherData& settings)
	{
		std::string dataPath = "Data/VGLauncher/VGLauncherData.json";

		// 如果目录不存在则创建
		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data");
		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data/VGLauncher");

		// 将数据转换为 JSON 字符串
		nlohmann::json json;
		json = settings;
		std::string jsonStr = json.dump(2);

		// 将 JSON 字符串写入文件
		Horizon::HFileSystem::WriteTextToFile(dataPath, jsonStr);
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

	void VGLauncherData::AddProject(const VGProjectItem& project)
	{
		// 检查项目是否已存在
		for (const auto& existingProject : Projects)
		{
			if (existingProject.Path == project.Path)
			{
				// 如果项目已存在，则不添加
				return;
			}
		}

		Projects.push_back(project);
	}
}
