#include "PakCrc32.h"

namespace VisionGal {

	uint32_t crc_table[256];

	uint32_t PakCrc32::CalcCRC32(const std::vector<uint8_t>& data)
	{
		static bool initialized = false;
		if (!initialized) {
			InitCrc32Table();
			initialized = true;
		}

		uint32_t crc = 0xFFFFFFFF;
		for (auto b : data)
			crc = (crc >> 8) ^ crc_table[(crc ^ b) & 0xFF];
		return crc ^ 0xFFFFFFFF;
	}

	void PakCrc32::InitCrc32Table()
	{
		for (uint32_t i = 0; i < 256; ++i) {
			uint32_t crc = i;
			for (int j = 0; j < 8; ++j)
				crc = (crc >> 1) ^ (0xEDB88320 & (-static_cast<int>(crc & 1)));
			crc_table[i] = crc;
		}
	}
}
