#pragma once
#include "../Core/HCore.h"
#include "HSceneInterface.h"
#include "../CoreModuleDefinitions.h"

#pragma warning(push)
#pragma warning(disable : 26439)
#include "entt.hpp"
#pragma warning(pop)

namespace Horizon
{
	struct HRelationship;
	typedef uint64 HEntityID;
	constexpr HEntityID HEntityIDNull = 0;

	struct CORE_MODULE_API HEntityInterface : public HObject
	{
		HEntityInterface() = default;
		HEntityInterface(const HEntityInterface&) = default;
		HEntityInterface& operator=(const HEntityInterface&) = default;
		HEntityInterface(HEntityInterface&&) noexcept = default;
		HEntityInterface& operator=(HEntityInterface&&) noexcept = default;
		~HEntityInterface() override = default;
	public:
		virtual size_t GetEntityID() { return m_EntityID; }
		virtual entt::entity GetEntity() { return m_BaseEntity; }
		virtual HSceneInterface* GetScene() noexcept { return m_BaseScene; }
		virtual HECS* GetWorld() { return m_BaseScene->GetWorld(); }
		virtual void* GetRelationShip();
		virtual bool IsValid() { return true; }

		template <typename T>
		T* GetComponent() {
			return GetWorld()->try_get<T>(m_BaseEntity);
		}

		template<typename T>
		bool HasComponent()
		{
			return GetWorld()->all_of<T>(m_BaseEntity);
		}

		template<typename T>
		void RemoveComponent()
		{
			GetWorld()->remove<T>(m_BaseEntity);
			return;
		}
	protected:
		entt::entity m_BaseEntity;
		size_t m_EntityID = 0;
		HSceneInterface* m_BaseScene = nullptr;
	};
}
