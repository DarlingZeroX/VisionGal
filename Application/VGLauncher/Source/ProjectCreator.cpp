#include "ProjectCreator.h"
#include <filesystem>

#include "VGLauncherData.h"

namespace VisionGal::Editor
{
	// 创建新项目的函数
	bool ProjectCreator::CreateProject()
	{
		// 检查项目名称和路径是否为空
		if (ProjectName.empty() || ProjectPath.empty())
		{
			return false;
		}

		// 获取启动器数据的单例实例
		auto& data = VGLauncherData::GetLauncherData();

		// 构建项目的完整路径
		std::filesystem::path projectPath(ProjectPath);
		projectPath /= ProjectName;

		// 创建项目主目录
		std::filesystem::create_directories(projectPath);

		// 创建 Assets 资源目录
		std::filesystem::path assetPath = projectPath / "Assets";
		std::filesystem::create_directories(assetPath);

		// 创建 ProjectSettings 配置目录
		std::filesystem::path projectSettings = projectPath / "ProjectSettings";
		std::filesystem::create_directories(projectSettings);

		// 创建项目项并添加到启动器数据中
		VGProjectItem project;
		project.Name = ProjectName;
		project.Path = projectPath.string();
		data.Projects.emplace_back(project);

		// 返回创建成功
		return true;
	}
}
