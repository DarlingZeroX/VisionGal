#pragma once
#include "Interface.h"
#include <memory>
#include <unordered_map>

namespace VisionGal::Editor
{
	class ComponentDrawerManager
	{
	public:
		ComponentDrawerManager() = default;
		ComponentDrawerManager(const ComponentDrawerManager&) = default;
		ComponentDrawerManager& operator=(const ComponentDrawerManager&) = default;
		ComponentDrawerManager(ComponentDrawerManager&&) noexcept = default;
		ComponentDrawerManager& operator=(ComponentDrawerManager&&) noexcept = default;
		~ComponentDrawerManager() = default;

		bool RegisterDrawer(const Ref<IComponentDrawer>& drawer);

		IComponentDrawer* GetDrawer(const String& type);

	private:
		std::unordered_map<String,Ref< IComponentDrawer >> m_Drawers;
	};
}
