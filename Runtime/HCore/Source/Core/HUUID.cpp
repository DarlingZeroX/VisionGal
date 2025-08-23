#include "pch.h"
#include "Core/HUUID.h"
#include "Core/HRandom.h"

namespace Horizon
{
	static HRandom s_random(std::clock());


	HUUID::HUUID()
		:UUID(0)
	{
		s_random.Seed(std::clock());
	}

	HUUID::HUUID(uint64 uuid)
		:UUID(uuid)
	{
	}

	HUUID HUUID::NewUUID()
	{
		s_random.Seed(std::clock());
		return HUUID(s_random.NextUINT64());
	}

	void HUUID::Invalid()
	{
		UUID = 0;
	}
}
