// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// For the latest information, see https://github.com/DarlingZeroX/VisionGal
// See the LICENSE file in the project root for details.

#pragma once
#include <HCore/Include/File/nlohmann/json.hpp>
#include <string>
#include <vector>
#include <filesystem>

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
		// 声明为友元
		friend void to_json(nlohmann::json& j, const VGLauncherData& data);
		friend void from_json(const nlohmann::json& j, VGLauncherData& data);

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

		/// @brief 添加项目
		/// @param project 项目
		bool AddProject(const VGProjectItem& project);
		/// @brief 移除项目
		/// @param index 索引
		bool RemoveProject(int index);
		/// @brief 获取项目列表
		const std::vector<VGProjectItem>& GetProjects() const;
		/// @brief 移除无效的项目
		void RemoveInvalidProjects();

		/// @brief 获取最后创建项目的目录
		const std::string& GetLastProjectCreateDirectory() const;
		/// @brief 设置最后创建项目的目录
		void SetLastProjectCreateDirectory(const std::string& directory);

	private:
		std::string m_LastProjectCreateDirectory;			/// @brief 最后的创建项目的目录
		std::vector<VGProjectItem> m_Projects;				/// @brief 项目列表
		std::filesystem::path m_LauncherDataFilePath;		/// @brief 数据文件路径
	};

}
