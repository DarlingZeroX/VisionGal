///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016-2021, Intel Corporation
//
// SPDX-License-Identifier: MIT
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Author(s):  Filip Strugar (filip.strugar@intel.com)	
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../CoreModuleDefinitions.h"

#include "../Core/HCore.h"
#include "HStream.h"
#include "HFileHeaders.h"
#include "HMemoryStream.h"
#include "../Core/HStringTools.h"

#include <filesystem>

#include <map>

namespace Horizon
{
#ifdef DeleteFile
#undef DeleteFile
#endif
#ifdef MoveFile
#undef MoveFile
#endif
#ifdef FindFiles
#undef FindFiles
#endif

#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif

	class HMemoryBuffer;

	using fsPath = std::filesystem::path;

	struct HFileFilterItem
	{
		std::wstring Name;
		std::wstring Spec;
	};

	//CORE_MODULE_API
	namespace  HFileSystem
	{
		//public:
		struct EmbeddedFileData
		{
			string                              Name;
			std::shared_ptr<HMemoryStream>     MemStream;
			int64                               TimeStamp;

			EmbeddedFileData() : Name(""), MemStream(NULL), TimeStamp(0) { }
			EmbeddedFileData(const string& name, const std::shared_ptr<HMemoryStream>& memStream, const int64& timeStamp)
				: Name(name), MemStream(memStream), TimeStamp(timeStamp) { }

			bool                                HasContents() { return MemStream != NULL; }
		};

		// As the name says
		inline bool ExistsFile(const fsPath& path)
		{
			return std::filesystem::exists(path);
		}

		inline bool	RemoveFile(const fsPath& path)
		{
			return std::filesystem::remove(path);
		}

		inline bool	DirectoryEmpty(const fsPath& path)
		{
			return std::filesystem::is_empty(path);
		}

		inline bool	RemoveDirectory(const fsPath& path)
		{
			return std::filesystem::remove(path);
		}

		inline bool	IsDirectory(const fsPath& path)
		{
			return std::filesystem::is_directory(path);
		}

		inline bool	IsCharacterFile(const fsPath& path)
		{
			return 	std::filesystem::is_character_file(path);
		}

		inline void	ResizeFile(const fsPath& path, size_t newSize)
		{
			return 	std::filesystem::resize_file(path, newSize);
		}

		inline void	MoveFile(const fsPath& oldPath, const fsPath& newPath)
		{
			std::filesystem::rename(oldPath, newPath);
		}

		inline bool	ExistsDirectory(const fsPath& path)
		{
			return std::filesystem::exists(path);
		}

		inline bool	CreateDirectory(const fsPath& path)
		{
			return std::filesystem::create_directory(path);
		}

		inline bool CreateDirectoryWhenNoExist(const fsPath& path)
		{
			if (!ExistsDirectory(path))
			{
				return CreateDirectory(path);
			}

			return true;
		}

		inline void			Copy(const fsPath& from, const fsPath& to)
		{
			std::filesystem::copy(from, to);
		}

		inline fsPath		Relative(const fsPath& path, const fsPath& base)
		{
			return std::filesystem::relative(path, base);
		}

		inline void			CopyFile(const fsPath& from, const fsPath& to)
		{
			std::filesystem::copy_file(from, to);
		}

		inline uintmax_t	GetFileSize(const fsPath& path)
		{
			return std::filesystem::file_size(path);
		}

		inline void			GetCurrentPath(fsPath& path)
		{
			return std::filesystem::current_path(path);
		}

		CORE_MODULE_API fsPath RelativePath(const fsPath& path, const fsPath& base);

		CORE_MODULE_API inline bool	CreateNullFile(const fsPath& path);

		//private:
		//static std::map<string, EmbeddedFileData> s_EmbeddedFiles;

		// Converts to lowercase, removes all duplicated "\\" or "//" and converts all '/' to '\'
		// (used to enable simple string-based path comparison, etc)
		// Note: it ignores first double "\\\\" because it could be a network path
		CORE_MODULE_API fsPath                            CleanupPath(const fsPath& inputPath, bool convertToLowercase, bool useBackslash = true);
		//static string                             CleanupPath(const string& inputPath, bool convertToLowercase, bool useBackslash = true)
		//{
		//	return HStringTools::SimpleNarrow(CleanupPath(HStringTools::SimpleWiden(inputPath), convertToLowercase, useBackslash));
		//}

		// tries to find the file using GetWorkingDirectory as root, then GetExecutableDirectory and then finally using system default; if file is found, returns full path; if not, returns empty string
		CORE_MODULE_API wstring                            FindLocalFile(const wstring& fileName);

		// SplitPath is in vaFileTools::SplitPath

		//static bool                               EnsureDirectoryExists(const wchar_t* path);
		//static bool                               EnsureDirectoryExists(const wstring& path) { return EnsureDirectoryExists(path.c_str()); }
		//static bool                               EnsureDirectoryExists(const string& path) {
		//	return EnsureDirectoryExists(HStringTools::SimpleWiden(path));
		//}
		//      // Just loads the whole file into a buffer
		//      // (this should be deleted)
		//      static std::shared_ptr<vaMemoryBuffer> LoadFileToMemoryBuffer( const wchar_t * fileName );

			  // Just loads the whole file into a buffer; TODO: rename and unify naming with ReadBuffer to ReadBinary/WriteBinary
		//CORE_MODULE_API std::shared_ptr<HMemoryStream>    LoadMemoryStream(const pfsPath& fileName);

		//CORE_MODULE_API string                             ReadText(const pfsPath& fileName);

		//CORE_MODULE_API wstring                            GetAbsolutePath(const wstring& path);
		//CORE_MODULE_API string                             GetAbsolutePath(const string& path) { return HStringTools::SimpleNarrow(GetAbsolutePath(HStringTools::SimpleWiden(path))); }

		CORE_MODULE_API std::vector<fsPath>               FindExtension(const fsPath& startDirectory, const std::string& extName, bool recursive);

		// Wildcards allowed!
		//CORE_MODULE_API std::vector<wstring>               FindFiles(const wstring& startDirectory, const wstring& searchName, bool recursive);
		//CORE_MODULE_API std::vector<wstring>               FindDirectories(const wstring& startDirectory);

		//CORE_MODULE_API std::vector<string>                FindFiles(const string& startDirectory, const string& searchName, bool recursive);
		//CORE_MODULE_API std::vector<string>                FindDirectories(const string& startDirectory);

		CORE_MODULE_API fsPath							   OpenFileDialog(const fsPath& defaultPath, std::vector<HFileFilterItem> filter);
		CORE_MODULE_API fsPath							   SaveFileDialog(const fsPath& defaultName, const fsPath& defaultPath, std::vector<HFileFilterItem> filters = {});
		CORE_MODULE_API fsPath							   SelectFolderDialog(const fsPath& defaultPath);

		CORE_MODULE_API void							   OpenSystemExplorerFolder(const fsPath& folderPath);

		CORE_MODULE_API bool							   ReadTextFromFile(const fsPath& path, std::string& text);
		CORE_MODULE_API bool							   WriteTextToFile(const fsPath& path, const std::string& text);

		CORE_MODULE_API void                               SplitPath(const string& inFullPath, string* outDirectory, string* outFileName, string* outFileExt);
		CORE_MODULE_API void                               SplitPath(const wstring& inFullPath, wstring* outDirectory, wstring* outFileName, wstring* outFileExt);

		CORE_MODULE_API bool                               PathHasDirectory(const string& inFullPath);

		CORE_MODULE_API wstring                            FixExtension(const wstring& path, const wstring& ext);
		CORE_MODULE_API string                             FixExtension(const string& path, const string& ext);

		CORE_MODULE_API string                             SplitPathExt(const string& inFullPath);
		CORE_MODULE_API wstring                            SplitPathExt(const wstring& inFullPath);

		CORE_MODULE_API std::string						   ToWindowsPath(const std::string& path);
		CORE_MODULE_API	std::string						   ToUnixPath(const std::string& path);

		CORE_MODULE_API	bool							   IsSubPath(const fsPath& base, const fsPath& target);
	};
}
