#pragma once
#include <string>
#include <vector>

namespace VisionGal::Editor
{
	struct VGProjectItem
	{
		/// @brief 项目名称
		std::string Name;

		/// @brief 项目路径
		std::string Path;
	};

	struct VGLauncherData
	{
		VGLauncherData();
		VGLauncherData(const VGLauncherData&) = default;
		VGLauncherData& operator=(const VGLauncherData&) = default;
		VGLauncherData(VGLauncherData&&) noexcept = default;
		VGLauncherData& operator=(VGLauncherData&&) noexcept = default;
		~VGLauncherData() = default;

		/// @brief 加载启动器数据
		/// @param settings 
		static void Load(VGLauncherData& settings);
		/// @brief 保存启动器数据
		/// @param settings 
		static void Save(VGLauncherData& settings);

		/// @brief 加载启动器数据
		static void LoadLauncherData();
		/// @brief 保存启动器数据
		static void SaveLauncherData();
		/// @brief 获取启动器数据
		static VGLauncherData& GetLauncherData();

		void AddProject(const VGProjectItem& project);

		/// @brief 最后的创建项目的目录
		std::string LastProjectCreateDirectory;

		/// @brief 项目列表
		std::vector<VGProjectItem> Projects;
	};

}
