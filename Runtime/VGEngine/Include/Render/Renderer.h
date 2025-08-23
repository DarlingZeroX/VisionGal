#pragma once
#include "Camera.h"
#include "../EngineConfig.h"
#include "../Core/Core.h"
#include "../Scene/Scene.h"
#include "../Scene/Components.h"

namespace VisionGal 
{
	class SpriteRendererHandler
	{
	public:
		SpriteRendererHandler();
		~SpriteRendererHandler() = default;

		void Render(std::vector<GameActor*>& sprites, ICamera* camera);

		void Render(GameActor* sprite, ICamera* camera);
	};

	struct FullScreenRendererHandler
	{
		void Render(FullScreenRendererComponent* renderer);
	};
}
