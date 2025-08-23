#pragma once
#include "entt.hpp"

namespace Horizon
{
	using HECS = entt::registry;

	struct HSceneInterface
	{
		virtual ~HSceneInterface() = default;

		virtual HECS* GetWorld() = 0;

		virtual void Update() {};
	};


}