﻿#include "pch.h"
#include "File/HJsonTypeHandler.h"

namespace Horizon
{
	HJsonTypeHandlerManager::HJsonTypeHandlerManager()
	{
		m_TypeHandler[&typeid(std::string)] = std::make_unique<HJsonTypeHandlerString>();

		m_TypeHandler[&typeid(uint32)] = std::make_unique<HJsonTypeHandlerUInt32>();
		m_TypeHandler[&typeid(int32)] = std::make_unique<HJsonTypeHandlerInt32>();

		m_TypeHandler[&typeid(uint16)] = m_TypeHandler[&typeid(uint32)];
		m_TypeHandler[&typeid(int16)] = m_TypeHandler[&typeid(int32)];

		m_TypeHandler[&typeid(uint8)] = m_TypeHandler[&typeid(uint32)];
		m_TypeHandler[&typeid(int8)] = m_TypeHandler[&typeid(int32)];

		m_TypeHandler[&typeid(int64)] = std::make_unique<HJsonTypeHandlerInt64>();
		m_TypeHandler[&typeid(uint64)] = std::make_unique<HJsonTypeHandlerUInt64>();
		m_TypeHandler[&typeid(float)] = std::make_unique<HJsonTypeHandlerFloat>();
		m_TypeHandler[&typeid(double)] = std::make_unique<HJsonTypeHandlerDouble>();
		m_TypeHandler[&typeid(bool)] = std::make_unique<HJsonTypeHandlerBool>();
		m_TypeHandler[&typeid(float2)] = std::make_unique<HJsonTypeHandlerVector2>();
		m_TypeHandler[&typeid(float3)] = std::make_unique<HJsonTypeHandlerVector3>();
		m_TypeHandler[&typeid(float4)] = std::make_unique<HJsonTypeHandlerVector4>();

	}

	HJsonTypeHandlerManager& HJsonTypeHandlerManager::Instance()
	{
		static HJsonTypeHandlerManager instance;
		return instance;
	}

	HJsonTypeHandler* HJsonTypeHandlerManager::TryGetHandler(const type_info* info)
	{
		if (auto res = m_TypeHandler.find(info); res != m_TypeHandler.end())
		{
			return res->second.get();
		}

		return nullptr;
	}
}
