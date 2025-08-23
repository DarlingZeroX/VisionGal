#pragma once
#include <string>
#include <vector>

namespace VisionGal::Editor
{
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
		bool CreateProject();

		/// @brief 项目名称
		std::string ProjectName;
		/// @brief 项目路径
		std::string ProjectPath;
	};
}
