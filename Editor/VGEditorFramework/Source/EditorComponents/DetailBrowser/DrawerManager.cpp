#include "EditorComponents/DetailBrowser/DrawerManager.h"

namespace VisionGal::Editor
{

	class EmptyComponentDrawer : public IComponentDrawer
	{
	public:
		void OnGUI(IEntity* entity) override
		{
		}
		const String GetBindType() const override
		{
			return "";
		}
	};

	bool ComponentDrawerManager::RegisterDrawer(const Ref<IComponentDrawer>& drawer)
	{
		m_Drawers[drawer->GetBindType()] = drawer;

		return true;
	}

	IComponentDrawer* ComponentDrawerManager::GetDrawer(const String& type)
	{
		static EmptyComponentDrawer s_EmptyDrawer;

		if (m_Drawers.find(type) != m_Drawers.end())
		{
			return m_Drawers[type].get();
		}

		return &s_EmptyDrawer;
	}
}
