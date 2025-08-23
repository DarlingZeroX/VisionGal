#include "Engine/Manager.h"

namespace VisionGal
{
	ViewportManager* GetViewportManager()
	{
		return ViewportManager::Get();
	}

	ShaderManager* GetShaderManager()
	{
		return ShaderManager::Get();
	}

	AssetManager* GetAssetManager()
	{
		return AssetManager::Get();
	} 

	SceneManager* GetSceneManager()
	{
		return SceneManager::Get();
	}
}
