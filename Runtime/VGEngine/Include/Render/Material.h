#pragma once
#include "../EngineConfig.h"
#include "../Core/Core.h"
#include "../Graphics/OpenGL/ShaderProgram.h"

namespace VisionGal {

	class Material
	{
	public:
		Material();
		~Material() = default;

		static Ref<Material> Create();

		VGFX::IShaderProgram* GetShaderProgram();
	private:

		//Ref<OpenGL::ShaderProgram> m_ShaderProgram;

		VGFX::IShaderProgram*  m_ShaderProgram;
		//Ref<>
	};

	
}
