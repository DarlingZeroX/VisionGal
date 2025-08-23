#include "Galgame/Components.h"

namespace VisionGal::GalGame
{
	GalGameEngineComponent::GalGameEngineComponent()
	{
	}

	std::string GalGameEngineComponent::GetComponentType() const
	{
		return "GalGameEngine";
	}

	void GalGameEngineComponentSerializer::AddActorSerializeComponent(Scene* scene, GameActor* actor, EntityID id)
	{
		auto* world = scene->GetWorld();
		GalGameEngineComponent& com = world->emplace<GalGameEngineComponent>(actor->GetEntity());
		GalGameEngineComponent& deserializeComponent = m_ComponentMap[id];

		com = deserializeComponent;
		if (deserializeComponent.__DeserializeData.HasScript)
		{
			com.script = GalGame::LuaStoryScript::LoadFromFile(deserializeComponent.__DeserializeData.m_ScriptPath);
		}

		scene->UpdateDeserializeComponent(actor, &com);
	}
}
