/* ----------------------------------------------------------------------------
** Copyright (c) 2022 code2x, All Rights Reserved.
**
** HTimer.h
** --------------------------------------------------------------------------*/

#pragma once
#include "../Core/HCoreTypes.h"
#include "../CoreModuleDefinitions.h"

namespace Horizon
{
	class CORE_MODULE_API HTimer
	{
	public:
		HTimer();
		HTimer(const HTimer&) = default;
		HTimer& operator=(const HTimer&) = default;
		~HTimer() = default;
	public:
		float TotalTime() const;
		float DeltaTime() const;

		// ����Ϣѭ��֮ǰ����
		void Reset();

		// ��ÿһ֡��ʱ�����
		void Tick();

		// Query current time, and calculate the delta time.
		void BeginTick();

		// Update the previous time to current time.
		void EndTick();

		// ��ȡ����ͣ��ʱ�����
		void Start();

		// ����ͣ��ʱ�����
		void Stop();
	private:
		double m_SecondsPerCount;
		double m_DeltaTime;

		uint64 m_BaseTime;
		uint64 m_PausedTime;
		uint64 m_StopTime;
		uint64 m_PrevTime;
		uint64 m_CurrTime;

		bool m_Stopped;
	};
}