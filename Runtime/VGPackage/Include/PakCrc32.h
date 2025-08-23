#pragma once
#include <vector>
#include <cstdint>

namespace VisionGal {

	struct PakCrc32 {
		static uint32_t CalcCRC32(const std::vector<uint8_t>& data);
	private:
		 static void InitCrc32Table();
	};


}
