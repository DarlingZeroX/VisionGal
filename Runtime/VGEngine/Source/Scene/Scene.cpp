#include "Scene/Scene.h"
#include "Scene/Components.h"
#include <HCore/Include/Scene/HSceneHierachy.h>
#include "Core/EventBus.h"

namespace VisionGal
{
	constexpr EntityID ConstHUISceneActor = 0;

	class SceneActor : public GameActor
	{
	public:
		SceneActor() = default;
		SceneActor(const SceneActor&) = default;
		SceneActor& operator=(const SceneActor&) = default;
		SceneActor(SceneActor&&) noexcept = default;
		SceneActor& operator=(SceneActor&&) noexcept = default;
		~SceneActor() override = default;

		void Initialize(IScene* scene) override {  };
	};

	void Scene::Update()
	{
	}


	Horizon::HECS* Scene::GetWorld()
	{
		return &m_Registry;
	}

	GameActor* Scene::GetSceneActor()
	{
		return m_SceneActor.get();
	}


	EntityID Scene::NewEntityID()
	{
		srand(std::clock());

		Horizon::HRandom randEngine;
		randEngine.Seed(rand());

		auto result = randEngine.NextUINT64();

		while (m_IDEntityMap.find(result) != m_IDEntityMap.end())
		{
			result = randEngine.NextUINT64();
		}

		return result;
	}

	ComponentID Scene::NewComponentID()
	{
		srand(std::clock());

		Horizon::HRandom randEngine;
		randEngine.Seed(rand());

		auto result = randEngine.NextUINT64();

		while (m_EntityComponentID.contains(result))
		{
			result = randEngine.NextUINT64();
		}

		return result;
	}

	void Scene::SetEntityBaseData(IEntity* entity, EntityID id, EntityID parentID, const std::string& lable)
	{
		entity->SetEntityID(id); 
		entity->SetBaseScene(this);

		// Entity data
		auto& data = m_Registry.emplace_or_replace<Horizon::HEntityObjectData>(entity->GetEntity());
		auto& relationship = m_Registry.emplace_or_replace<Horizon::HRelationship>(entity->GetEntity());
		data.ID = id;
		data.Entity = entity;
		relationship.Label = lable;
		relationship.ParentID = parentID;
	}

	GameActor* Scene::CreateDeserializeActor(const SceneDeserializeEntity& deEntity)
	{
		if (deEntity.ID == ConstHUISceneActor)
			return GetSceneActor();

		auto entity = CreateRef<GameActor>();
		entity->SetBaseEntity(this->GetWorld()->create());

		{
			SetEntityBaseData(entity.get(), deEntity.ID, deEntity.Parent, deEntity.Label);
			m_IDEntityMap[deEntity.ID] = entity;
		}

		return entity.get();
	}

	void Scene::UpdateDeserializeComponent(IEntity* entity, IComponent* component)
	{
		m_EntityComponentID.insert(component->EntityComID);
		component->SetOwner(entity);
	}

	void Scene::UpdateDeserializeActorRelationship()
	{
		auto view = GetWorld()->view<Horizon::HEntityObjectData, Horizon::HRelationship>();

		view.each([&, this](Horizon::HEntityObjectData& data, Horizon::HRelationship& relationship)
			{
				if (data.ID == ConstHUISceneActor)
					return;

				Horizon::HHierarchy::SetParent(
					m_Registry,
					*data.Entity,
					m_IDEntityMap[relationship.ParentID].get()
				);

			});
	}

	GameActor* Scene::CreateActor(IEntity* parent)
	{
		auto entity = CreateRef<GameActor>();
		entity->SetBaseEntity(this->GetWorld()->create());

		{
			auto ID = NewEntityID();
			IEntity* realParent = parent == nullptr ? m_SceneActor.get() : parent;

			SetEntityBaseData(entity.get(), ID, realParent->GetEntityID(), GetNewLabel(entity.get()));
			Horizon::HHierarchy::SetParent(m_Registry, *entity, realParent);

			m_IDEntityMap[ID] = entity;				//map entity id to entity object
		}

		entity->Initialize(this);
		entity->AddComponent<TransformComponent>();

		// �¼�
		SceneEvent evt;
		evt.EventType = SceneEventType::EntityCreating;
		evt.Entity = entity.get();
		EngineEventBus::Get().OnSceneEvent.Invoke(evt);

		return entity.get();
	}

	void Scene::CreateSceneActor()
	{
		m_SceneActor = CreateRef<SceneActor>();
		m_SceneActor->Initialize(this);
		m_SceneActor->SetEntityID(ConstHUISceneActor);
		m_SceneActor->SetBaseEntity(this->GetWorld()->create());
		m_SceneActor->SetBaseScene(this);

		auto& relationship = m_Registry.emplace<Horizon::HRelationship>(m_SceneActor->GetEntity());

		auto& object = m_Registry.emplace<Horizon::HEntityObjectData>(m_SceneActor->GetEntity());
		object.Entity = m_SceneActor.get();
		object.ID = ConstHUISceneActor;
		relationship.Label = m_SceneName;

		m_IDEntityMap[ConstHUISceneActor] = m_SceneActor;
	}

	std::string Scene::GetNewLabel(IEntity* hObj)
	{
		return std::string("New Label");
	}

	Scene::Scene()
	{
		CreateSceneActor();
	}

	void Scene::AddEntityComponent(IEntity* entity, IComponent* component)
	{
		uint64 comID = NewComponentID();

		Horizon::HEntityObjectData* entt_obj = entity->GetComponent<Horizon::HEntityObjectData>();
		entt_obj->ComponentTypes.push_back(component->GetComponentType());
		entt_obj->ComponentIDs.push_back(comID);

		component->SetOwner(entity);
		component->EntityComID = comID;
		component->Initialize();

		m_EntityComponentID.insert(comID);
	}

	IEntity* Scene::GetEntity(EntityID entityID)
	{
		if (auto result = m_IDEntityMap.find(entityID); result != m_IDEntityMap.end())
		{
			return result->second.get();
		}
		return nullptr;
	}

	bool Scene::RemoveEntity(EntityID entityID)
	{
		if (auto result = m_IDEntityMap.find(entityID); result != m_IDEntityMap.end())
		{
			GameActor& entity = *result->second.get();
			auto& relation = *entity.GetComponent<Horizon::HRelationship>();

			Horizon::HHierarchy::DisconnectParent(m_Registry, entity, relation);

			m_Registry.destroy(entity.GetEntity());

			// �¼�
			SceneEvent evt;
			evt.EventType = SceneEventType::EntityRemoved;
			evt.Entity = &entity;
			evt.EntityID = entity.GetEntityID();
			EngineEventBus::Get().OnSceneEvent.Invoke(evt);

			m_IDEntityMap.erase(entityID);

			return 0;
		}

		return 0;
	}

	bool Scene::ExistEntity(EntityID entityID)
	{
		return m_IDEntityMap.find(entityID) != m_IDEntityMap.end();
	}

}
