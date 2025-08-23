#pragma once
#include "GalGameEngineInterface.h"
#include "../Core/Core.h"

namespace VisionGal::GalGame
{
	struct VG_ENGINE_API GameEngineCore
	{
		static void SetDesignSize(float2 size);
		static float2 GetDesignSize();

		static float GetSpriteYOffset(float size_y);
		static float GetSpriteXOffset(float size_x);

		static IGalGameEngine* GetCurrentEngine();
		static void SetCurrentEngine(IGalGameEngine* engine);
		//static GamePipeline* GetCurrentPipeline();
		//static void SetCurrentPipeline(GamePipeline* pipeline);
	};
}