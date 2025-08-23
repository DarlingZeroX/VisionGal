#include <windows.h>
#include <shellapi.h>
#include <iostream>

#include "Graphics/GFX/ShaderCompiler.h"
#include "Core/Core.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

ShaderCompiler::ShaderCompiler()
{
    m_shadercPath = "E:/vcpkg/installed/x64-windows/tools/bgfx/shaderc.exe";
    m_bgfxIncludePath = Core::GetContentRootDirectory();
}

bool ShaderCompiler::NeedsCompilation(const std::string& inputFile, const std::string& outputFile)
{
    WIN32_FILE_ATTRIBUTE_DATA inputAttr, outputAttr;

    // 获取输入文件时间戳
    if (!GetFileAttributesEx(inputFile.c_str(), GetFileExInfoStandard, &inputAttr)) {
        std::cerr << "无法获取输入文件属性: " << inputFile << std::endl;
        return false;
    }

    // 检查输出文件是否存在
    if (!GetFileAttributesEx(outputFile.c_str(), GetFileExInfoStandard, &outputAttr)) {
        return true;  // 输出文件不存在，需要编译
    }

    // 比较修改时间
    return CompareFileTime(&inputAttr.ftLastWriteTime, &outputAttr.ftLastWriteTime) > 0;
}

bool ShaderCompiler::CompileIfNeeded(const std::string& inputFile, const std::string& outputFile, const std::string& platform, const std::string& profile, const std::string& type)
{
    if (!NeedsCompilation(inputFile, outputFile)) {
        std::cout << "着色器未修改，跳过编译: " << inputFile << std::endl;
        return true;
    }

    return CompileShader(inputFile, outputFile, platform, profile, type);
}

bool ShaderCompiler::CompileShader(const std::string& inputFile, const std::string& outputFile, const std::string& platform, const std::string& profile, const std::string& type)
{
    // 构建命令行
    std::string command = m_shadercPath + " "
        + "-f \"" + inputFile + "\" "
        + "-o \"" + outputFile + "\" "
        + "-i \"" + m_bgfxIncludePath + "\" "
        + "--platform " + platform + " "
        + "--type " + type + " "
        + "--profile " + profile + " "
        + "--varyingdef \"" + m_bgfxIncludePath + "/../src/shader.varying\" "
        + "--verbose";

    // 执行命令
    std::cout << "执行命令: " << command << std::endl;

    // 使用CreateProcess执行命令
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char* cmd = const_cast<char*>(command.c_str());

    if (!CreateProcess(nullptr, cmd, nullptr, nullptr, FALSE,
        CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        std::cerr << "着色器编译失败: " << GetLastError() << std::endl;
        return false;
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取退出代码
    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cerr << "无法获取编译进程退出代码" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }

    // 清理句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        std::cerr << "着色器编译失败，退出代码: " << exitCode << std::endl;
        return false;
    }

    std::cout << "着色器编译成功: " << outputFile << std::endl;
    return true;
}

VISIONGAL_GFX_NAMESPACE_END

