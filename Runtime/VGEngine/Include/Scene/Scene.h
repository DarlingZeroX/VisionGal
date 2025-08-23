#pragma once
#include "../Interface/SceneInterface.h"
#include <memory>
#include <unordered_map>
#include <HCore/Include/Core/HRandom.h>
#include <HCore/Include/Scene/HBaseComponent.h>
#include <HCore/Include/Event/HEventDelegate.h>

namespace VisionGal
{
	class VG_ENGINE_API Scene: public IScene
	{
	public:
		Scene();
		Scene(const Scene&) = default;
		Scene& operator=(const Scene&) = default;
		Scene(Scene&&) noexcept = default;
		Scene& operator=(Scene&&) noexcept = default;
		~Scene() override = default;

		//Horizon::HEventDelegate<const Horizon::HUISceneEvent&> OnSceneEvent;
		GameActor* CreateActor(IEntity* parent = nullptr) override;

		template<typename T, class = typename std::enable_if<std::is_base_of<IComponent, T>::value>::type>
		T* AddEntityComponent(IEntity* entity)
		{
			T& com = GetWorld()->emplace<T>(entity->GetEntity());

			AddEntityComponent(entity, &com);

			return &com;
		}
		void AddEntityComponent(IEntity* entity, IComponent* component) override;
		 
		// 通过 IScene 继承
		IEntity* GetEntity(EntityID entityID) override;
		bool RemoveEntity(EntityID entityID) override;
		bool ExistEntity(EntityID entityID) override;
		Horizon::HECS* GetWorld() override;

		void Update();
		GameActor* GetSceneActor();

		GameActor* CreateDeserializeActor(const SceneDeserializeEntity& entity);
		void UpdateDeserializeComponent(IEntity* entity, IComponent* component);
		void UpdateDeserializeActorRelationship();
	private:

		EntityID NewEntityID();
		ComponentID NewComponentID();
		void SetEntityBaseData(IEntity* entity, EntityID id, EntityID parentID, const std::string& lable);
		void CreateSceneActor();
		std::string GetNewLabel(IEntity* hObj);
	private:
		std::unordered_map<EntityID, std::shared_ptr<GameActor>> m_IDEntityMap;
		std::unordered_set<ComponentID> m_EntityComponentID;
		ECS m_Registry;

		std::shared_ptr<GameActor> m_SceneActor;
		std::string m_SceneName = "Scene";
	};
}
