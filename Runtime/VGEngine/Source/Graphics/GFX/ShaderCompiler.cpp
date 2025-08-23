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

    // ��ȡ�����ļ�ʱ���
    if (!GetFileAttributesEx(inputFile.c_str(), GetFileExInfoStandard, &inputAttr)) {
        std::cerr << "�޷���ȡ�����ļ�����: " << inputFile << std::endl;
        return false;
    }

    // �������ļ��Ƿ����
    if (!GetFileAttributesEx(outputFile.c_str(), GetFileExInfoStandard, &outputAttr)) {
        return true;  // ����ļ������ڣ���Ҫ����
    }

    // �Ƚ��޸�ʱ��
    return CompareFileTime(&inputAttr.ftLastWriteTime, &outputAttr.ftLastWriteTime) > 0;
}

bool ShaderCompiler::CompileIfNeeded(const std::string& inputFile, const std::string& outputFile, const std::string& platform, const std::string& profile, const std::string& type)
{
    if (!NeedsCompilation(inputFile, outputFile)) {
        std::cout << "��ɫ��δ�޸ģ���������: " << inputFile << std::endl;
        return true;
    }

    return CompileShader(inputFile, outputFile, platform, profile, type);
}

bool ShaderCompiler::CompileShader(const std::string& inputFile, const std::string& outputFile, const std::string& platform, const std::string& profile, const std::string& type)
{
    // ����������
    std::string command = m_shadercPath + " "
        + "-f \"" + inputFile + "\" "
        + "-o \"" + outputFile + "\" "
        + "-i \"" + m_bgfxIncludePath + "\" "
        + "--platform " + platform + " "
        + "--type " + type + " "
        + "--profile " + profile + " "
        + "--varyingdef \"" + m_bgfxIncludePath + "/../src/shader.varying\" "
        + "--verbose";

    // ִ������
    std::cout << "ִ������: " << command << std::endl;

    // ʹ��CreateProcessִ������
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char* cmd = const_cast<char*>(command.c_str());

    if (!CreateProcess(nullptr, cmd, nullptr, nullptr, FALSE,
        CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        std::cerr << "��ɫ������ʧ��: " << GetLastError() << std::endl;
        return false;
    }

    // �ȴ����̽���
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ��ȡ�˳�����
    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cerr << "�޷���ȡ��������˳�����" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }

    // ������
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        std::cerr << "��ɫ������ʧ�ܣ��˳�����: " << exitCode << std::endl;
        return false;
    }

    std::cout << "��ɫ������ɹ�: " << outputFile << std::endl;
    return true;
}

VISIONGAL_GFX_NAMESPACE_END

