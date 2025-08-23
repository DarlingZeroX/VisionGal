#pragma once
#include "../Config.h"
#include <HCore/Include/Core/HLocalization.h>

namespace VisionGal::Editor
{
	VG_EDITOR_FRAMEWORK_API bool EditorLoadLanguage(const std::string& code);

	class VG_EDITOR_FRAMEWORK_API EditorText
	{
	public:
		EditorText(const std::string& title);
		EditorText(const std::string& title, const std::string& icon);
		EditorText(const std::string& title, const std::string& icon, const std::string& id);
		EditorText(const EditorText&) = default;
		EditorText& operator=(const EditorText&) = default;
		EditorText(EditorText&&) noexcept = default;
		EditorText& operator=(EditorText&&) noexcept = default;
		~EditorText() = default;

		const std::string& GetText();
		const char* c_str();
	private:
		std::string m_Text;
	};
}