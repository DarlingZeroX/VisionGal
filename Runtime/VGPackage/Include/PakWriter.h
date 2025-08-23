#pragma once
#include "Config.h"
#include "PakFormat.h"
#include <vector>
#include <fstream>
#include <filesystem>

namespace VisionGal {

	struct VG_PACKAGE_API PakFileWriter {

		PakFileWriter() = default;
		~PakFileWriter() = default;

		std::ofstream m_OutFile;
		PakHeader m_Header;
		std::vector<PakEntry> m_Entries;
		std::filesystem::path m_BasePath;

		//PackageFileWriter(const std::string& outPakPath, const std::string& aesKeyHex);
		//~PackageFileWriter();
		//

		bool WritePakFile(const std::vector<std::filesystem::path>& files, const std::filesystem::path& outPakPath,
			const std::string& aesKeyHex);

		bool WriteDirectoryToPakFile(const std::filesystem::path& InDirectoryPath, const std::filesystem::path& outPakPath,
			const std::string& aesKeyHex);
	private:
		void WriteHeader();
		void WriteFiles(const std::vector<std::filesystem::path>& files);
		void WriteEntries();
		//bool WriteEntry(const PackageEntry& entry, const std::string& filePath);
		void Finalize(uint64_t indexOffset);
	};
}
