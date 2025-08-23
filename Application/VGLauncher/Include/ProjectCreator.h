// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// For the latest information, see https://github.com/DarlingZeroX/VisionGal
// See the LICENSE file in the project root for details.

#pragma once
#include <string>
#include <vector>

namespace VisionGal::Editor
{
	struct ProjectCreateConfig
	{
		/// @brief 项目名称
		std::string ProjectName;
		/// @brief 项目路径
		std::string ProjectPath;
	};

	struct ProjectCreator
	{
		ProjectCreator() = default;
		ProjectCreator(const ProjectCreator&) = default;
		ProjectCreator& operator=(const ProjectCreator&) = default;
		ProjectCreator(ProjectCreator&&) noexcept = default;
		ProjectCreator& operator=(ProjectCreator&&) noexcept = default;
		~ProjectCreator() = default;

		/// @brief 创建一个新项目。
		/// @return 如果项目创建成功，则返回 true；否则返回 false。
		static bool CreateProject(const ProjectCreateConfig& config);
	};
}
