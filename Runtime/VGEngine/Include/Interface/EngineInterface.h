#pragma once
#include "../Core/Core.h"
#include <SDL3/SDL.h>

namespace VisionGal
{
	struct IEngineApplicationLayer
	{
		virtual ~IEngineApplicationLayer() = default;

		virtual void OnLayerInitialize() = 0;
		virtual void OnLayerRender() = 0;
		virtual void OnLayerUpdate(float delta) = 0;
	};

	struct IEngineApplication
	{
		virtual ~IEngineApplication() = default;

		virtual void AddApplicationLayer(IEngineApplicationLayer* layer) = 0;
		virtual void OnApplicationUpdate(float deltaTime) = 0;
		virtual int ProcessEvent(const SDL_Event& event) = 0;
		virtual void MakeCurrentRenderContext() = 0;
	};

	struct IUISystem
	{
		virtual ~IUISystem() = default;

		//virtual void* LoadUIFile(const String& path) = 0;
		//virtual bool ShowUI(void* ui) = 0;
		virtual void* GetContext() = 0;
	};


}