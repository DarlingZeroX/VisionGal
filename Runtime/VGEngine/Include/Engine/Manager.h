#pragma once
#include "../EngineConfig.h"
#include "Manager/ViewportManager.h"
#include "Manager/ShaderManager.h"
#include "Manager/AssetManager.h"
#include "Manager/SceneManager.h"

namespace VisionGal
{
    VG_ENGINE_API ViewportManager* GetViewportManager();

    VG_ENGINE_API ShaderManager* GetShaderManager();

    VG_ENGINE_API AssetManager* GetAssetManager();
	 
    VG_ENGINE_API SceneManager* GetSceneManager();
}
