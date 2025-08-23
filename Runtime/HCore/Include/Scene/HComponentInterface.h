#pragma once
#include <string>
#include "HEntityInterface.h"

namespace Horizon
{
	struct HComponentInterface : public HObject
	{
		HComponentInterface() = default;
		~HComponentInterface() override = default;

		virtual HEntityInterface* GetOwner() {return m_OwnerUIEntity;}
		virtual void SetOwner(HEntityInterface* entity) {m_OwnerUIEntity = entity;}
		virtual void Initialize() {}
	private:
		HEntityInterface* m_OwnerUIEntity;
	};
}