#pragma once
#include "../../EngineConfig.h"
#include "../../Core/Core.h"

namespace VisionGal::VGFX
{
	struct TextureDesc
	{
		int Width;
		int Height;
		int InternalFormat;
		uint Format;
		uint Type;
		void* Data;
		unsigned int DataSize;
	};

	struct ITexture
	{
	public:
		virtual ~ITexture() = default;
 
		virtual const TextureDesc& GetDesc() = 0;
		virtual void* GetShaderResourceView() = 0;
	};
}