#include "GFX.h"
#pragma once

#include <string>
#include <vector>

VISIONGAL_GFX_NAMESPACE_BEGIN

class ShaderCompiler {
public:
    ShaderCompiler();
    ShaderCompiler(const std::string& shadercPath, const std::string& bgfxIncludePath)
        : m_shadercPath(shadercPath)
        , m_bgfxIncludePath(bgfxIncludePath) {
    }

    bool CompileVertexShader(const std::string& inputFile, const std::string& outputFile,
        const std::string& platform = "windows",
        const std::string& profile = "vs_3_3") {
        return CompileIfNeeded(inputFile, outputFile, platform, profile, "vertex");
    }

    bool CompileFragmentShader(const std::string& inputFile, const std::string& outputFile,
        const std::string& platform = "windows",
        const std::string& profile = "ps_3_3") {
        return CompileIfNeeded(inputFile, outputFile, platform, profile, "fragment");
    }

private:
    // 检查文件是否需要重新编译
    bool NeedsCompilation(const std::string& inputFile, const std::string& outputFile);

    // 只编译修改过的着色器
    bool CompileIfNeeded(const std::string& inputFile, const std::string& outputFile,
        const std::string& platform, const std::string& profile,
        const std::string& type);

    bool CompileShader(const std::string& inputFile, const std::string& outputFile,
        const std::string& platform, const std::string& profile,
        const std::string& type);

private:
    std::string m_shadercPath;
    std::string m_bgfxIncludePath;
};


VISIONGAL_GFX_NAMESPACE_END