#pragma once
#include "../../Core/Core.h"
#include "../../Graphics/Interface/VGFX.h"

namespace VisionGal
{
    class ShaderManager
    {
    public:
        enum class ShaderBlockType {
            None,
            VS,
            PS
        };

        ShaderManager();
        ~ShaderManager() = default;
        ShaderManager(const ShaderManager&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;
        ShaderManager(ShaderManager&&) noexcept = default;
        ShaderManager& operator=(ShaderManager&&) noexcept = default;

        static ShaderManager* Get();
        VGFX::IShaderProgram* GetBuiltinProgram(const String& name);
    private:
        std::string Trim(const std::string& s);
        void ExtractShaders(const std::string& source, std::string& vs, std::string& ps);
        void Initialize();
        void AddBuiltInShader(const std::string& name, const std::string& path = "");
    private:
        std::unordered_map<std::string, Ref<VGFX::IShaderProgram>> m_BuiltinProgram;
    };
}
