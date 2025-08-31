#include "Galgame/GameLua.h"
#include <string>
#include "Galgame/GalGameEngine.h"
#include "Galgame/Game.h"
#include "Galgame/GameEngineCore.h"
#include "Galgame/ArchiveSystem.h"

namespace VisionGal::GalGame
{
	
	//static bool s_DialogLocked = true;
	//static sol::coroutine* s_PlotCoroutine = nullptr;
	//
	////////////////////////////////////////////////////// Dialog
	//
	//int DialogSystemLuaInterface::Continue()
	//{
	//	if (s_PlotCoroutine == nullptr)
	//		return 0;
	//
	//	if (s_PlotCoroutine->status() == sol::call_status::ok) {
	//		s_PlotCoroutine = nullptr;
	//	}
	//
	//	if (s_PlotCoroutine == nullptr)
	//		return 0;
	//
	//	try
	//	{
	//		if (s_PlotCoroutine && s_PlotCoroutine->lua_state()) {
	//			auto result = (*s_PlotCoroutine)();
	//
	//			if (s_PlotCoroutine->error())
	//			{
	//				sol::error err = result;
	//				s_PlotCoroutine = nullptr;
	//				H_LOG_ERROR(err.what());
	//			}
	//		}
	//	}
	//	catch (const sol::error& e) {
	//		H_LOG_ERROR(e.what());
	//		s_PlotCoroutine = nullptr;
	//	}
	//
	//	return 0;
	//}

	bool DialogSystemLuaInterface::IsTypingText()
	{
		return GameEngineCore::GetCurrentEngine()->GetDialogueSystem()->IsTypingText();
	}

	void DialogSystemLuaInterface::FinishTyping()
	{
		return dynamic_cast<GalGameEngine*>(GameEngineCore::GetCurrentEngine())->GetDialogueSystem()->FinishTyping();
	}

	uint DialogSystemLuaInterface::GetDialogNumber()
	{
		DialogueSystem* ds = dynamic_cast<DialogueSystem*>( GameEngineCore::GetCurrentEngine()->GetDialogueSystem() );

		return ds->GetDialogNumber();
	}

	String DialogSystemLuaInterface::GetDialogCharacter(uint index)
	{
		DialogueSystem* ds = dynamic_cast<DialogueSystem*>(GameEngineCore::GetCurrentEngine()->GetDialogueSystem());

		return ds->GetDialogCharacter(index);
	}

	String DialogSystemLuaInterface::GetDialogText(uint index)
	{
		DialogueSystem* ds = dynamic_cast<DialogueSystem*>(GameEngineCore::GetCurrentEngine()->GetDialogueSystem());

		return ds->GetDialogText(index);
	}

	void DialogSystemLuaInterface::AutoDialogue(bool enable)
	{
		DialogueSystem* ds = dynamic_cast<DialogueSystem*>(GameEngineCore::GetCurrentEngine()->GetDialogueSystem());

		ds->AutoDialogue(enable);
	}

	void DialogSystemLuaInterface::FastForward(bool enable)
	{
		DialogueSystem* ds = dynamic_cast<DialogueSystem*>(GameEngineCore::GetCurrentEngine()->GetDialogueSystem());

		ds->FastForward(enable);
	}

	SaveArchive ArchiveSystemLuaInterface::SaveArchiveByNumber(std::string number)
	{
		ArchiveSystem* as = dynamic_cast<ArchiveSystem*>(GameEngineCore::GetCurrentEngine()->GetArchiveSystem());

		return as->SaveArchiveByNumber(number);
	}

	SaveArchive ArchiveSystemLuaInterface::GetArchiveByNumber(std::string number)
	{
		ArchiveSystem* as = dynamic_cast<ArchiveSystem*>(GameEngineCore::GetCurrentEngine()->GetArchiveSystem());

		return as->GetArchiveByNumber(number);
	}

	bool ArchiveSystemLuaInterface::HasArchiveByNumber(std::string number)
	{
		ArchiveSystem* as = dynamic_cast<ArchiveSystem*>(GameEngineCore::GetCurrentEngine()->GetArchiveSystem());

		return as->HasArchiveByNumber(number);
	}

	bool GalGameEngineLuaInterface::LoadArchive(const SaveArchive& archive)
	{
		GalGameEngine* engine = dynamic_cast<GalGameEngine*>(GameEngineCore::GetCurrentEngine());
		return engine->LoadArchive(archive);
	}

	void GalGameLuaInterface::Initialise(sol::state& lua)
	{
		sol::table galgame = lua.create_named_table("GalGame");

		// 引擎
		{
			sol::table engine = galgame.create_named("Engine");
			engine.set_function("LoadArchive", &GalGameEngineLuaInterface::LoadArchive);

			galgame.set("GetEngine", []() -> GalGameEngine*
				{
					return dynamic_cast<GalGameEngine*>(GameEngineCore::GetCurrentEngine());
				});
			galgame.set("获取引擎", []() -> GalGameEngine*
				{
					return dynamic_cast<GalGameEngine*>(GameEngineCore::GetCurrentEngine());
				});
		}

		// 对话系统
		//{
		//	sol::table dialogueSystem = galgame.create_named("DialogueSystem");
		//
		//	dialogueSystem.set_function("Continue", DialogSystemLuaInterface::Continue);
		//	dialogueSystem.set_function("IsTypingText", DialogSystemLuaInterface::IsTypingText);
		//	dialogueSystem.set_function("FinishTyping", DialogSystemLuaInterface::FinishTyping);
		//	dialogueSystem.set_function("GetDialogNumber", DialogSystemLuaInterface::GetDialogNumber);
		//	dialogueSystem.set_function("GetDialogCharacter", DialogSystemLuaInterface::GetDialogCharacter);
		//	dialogueSystem.set_function("GetDialogText", DialogSystemLuaInterface::GetDialogText);
		//	dialogueSystem.set_function("AutoDialogue", DialogSystemLuaInterface::AutoDialogue);
		//	dialogueSystem.set_function("FastForward", DialogSystemLuaInterface::FastForward);
		//}

		// 注册引擎存档类
		lua.new_usertype<DialogueSystem>("GalGameDialogueSystem",
			"ContinueDialogue", &DialogueSystem::ContinueDialogue,
			"isTypingText", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsTypingText(); }
			),
			"FinishTyping", &DialogueSystem::FinishTyping,

			"GetDialogCharacter", &DialogueSystem::GetDialogCharacter,
			"GetDialogText", &DialogueSystem::GetDialogText,
			"dialogNumber", sol::property(
				[](DialogueSystem& self) -> unsigned int { return self.GetDialogNumber(); }
			),
			"autoDialogue", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsAutoDialogue(); },
				[](DialogueSystem& self, bool value) { self.AutoDialogue(value); }
			),
			"fastForward", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsFastForward(); },
				[](DialogueSystem& self, bool value) { self.FastForward(value); }
			),
			"fastForwardDelay", sol::property(
				[](DialogueSystem& self) -> float { return self.GetFastForwardDelay(); },
				[](DialogueSystem& self, float value) { self.SetFastForwardDelay(value); }
			),

			//中文
			"继续对话", & DialogueSystem::ContinueDialogue,
			"是否正在打印对话", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsTypingText(); }
			),
			"完成打印对话", &DialogueSystem::FinishTyping,
			"对话数目", sol::property(
				[](DialogueSystem& self) -> unsigned int { return self.GetDialogNumber(); }
			),
			"获取对话人物", &DialogueSystem::GetDialogCharacter,
			"获取对话文本", &DialogueSystem::GetDialogText,
			"自动对话", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsAutoDialogue(); },
				[](DialogueSystem& self, bool value) { self.AutoDialogue(value); }
			),
			"快进", sol::property(
				[](DialogueSystem& self) -> bool { return self.IsFastForward(); },
				[](DialogueSystem& self, bool value) { self.FastForward(value); }
			),
			"快进间隔时间", sol::property(
				[](DialogueSystem& self) -> float { return self.GetFastForwardDelay(); },
				[](DialogueSystem& self, float value) { self.SetFastForwardDelay(value); }
			)
			//"跳到对话", & DialogueSystem::JumpToDialog
		);

		// 注册存档系统
		lua.new_usertype<ArchiveSystem>("GalGameArchiveSystem",
			"SaveArchiveByNumber", &ArchiveSystem::SaveArchiveByNumber,
			"GetArchiveByNumber", &ArchiveSystem::GetArchiveByNumber,
			"HasArchiveByNumber", &ArchiveSystem::HasArchiveByNumber,
			//中文
			"保存存档", &ArchiveSystem::SaveArchiveByNumber,
			"获取存档", &ArchiveSystem::GetArchiveByNumber,
			"是否存在存档", &ArchiveSystem::HasArchiveByNumber
		);

		// 注册引擎类
		lua.new_usertype<GalGameEngine>("GalGameEngine",
			"LoadArchive", &GalGameEngine::LoadArchive,
			"DialogueSystem", sol::property(
				[](GalGameEngine& self) -> DialogueSystem* { return dynamic_cast<DialogueSystem*>(self.GetDialogueSystem()); }
			),
			"ArchiveSystem", sol::property(
				[](GalGameEngine& self) -> ArchiveSystem* { return dynamic_cast<ArchiveSystem*>(self.GetArchiveSystem()); }
			),

			//中文
			"等待", sol::yielding(&GalGameEngine::Wait),
			"转场命令", &GalGameEngine::TransitionCommand,
			"自定义图片转场命令", &GalGameEngine::TransitionCommandWithCustomImage,
			"加载剧情脚本", &GalGameEngine::LoadStoryScriptOnUpdate,
			"加载存档", &GalGameEngine::LoadArchive,
			"对话系统", sol::property(
				[](GalGameEngine& self) -> DialogueSystem* { return dynamic_cast<DialogueSystem*>(self.GetDialogueSystem()); }
			),
			"存档系统", sol::property(
				[](GalGameEngine& self) -> ArchiveSystem* { return dynamic_cast<ArchiveSystem*>(self.GetArchiveSystem()); }
			),
			"创建人物", &GalGameEngine::CreateCharacter,
			"显示背景", [](GalGameEngine& self, const std::string& path) ->GalSprite* { return self.ShowSprite("Background", path); },
			"显示图片", [](GalGameEngine& self, const std::string& path) ->GalSprite* { return self.ShowSprite("Scene", path); },
			"播放背景音乐", [](GalGameEngine& self, const std::string& path) ->GalAudio* { return self.PlayAudio("BGM", path); },
			"播放效果音乐", [](GalGameEngine& self, const std::string& path) ->GalAudio* { return self.PlayAudio("Effect", path); },
			"隐藏全部人物立绘", &GalGameEngine::HideAllCharacterSprite
		);

		//// 存档系统
		//{
		//	sol::table archiveSystem = galgame.create_named("ArchiveSystem");
		//
		//	archiveSystem.set_function("SaveArchiveByNumber", ArchiveSystemLuaInterface::SaveArchiveByNumber);
		//	archiveSystem.set_function("GetArchiveByNumber", ArchiveSystemLuaInterface::GetArchiveByNumber);
		//	archiveSystem.set_function("HasArchiveByNumber", ArchiveSystemLuaInterface::HasArchiveByNumber);
		//}

		// 注册存档类
		lua.new_usertype<SaveArchive>("GalGameSaveArchive",
			sol::constructors<SaveArchive()>(),
			"isGalGameArchive", &SaveArchive::isGalGameArchive,
			"isValid", &SaveArchive::isValid,
			"version", &SaveArchive::version,
			"scriptPath", &SaveArchive::scriptPath,
			"line", &SaveArchive::line,
			"saveNumberString", &SaveArchive::saveNumberString,
			"data", &SaveArchive::date,
			"time", &SaveArchive::time,
			"dateTime", &SaveArchive::dateTime,
			"description", &SaveArchive::description
		);
	}

	/*
	void StoryScriptLuaInterface::Initialise(sol::state& lua)
	{
		// 注册引擎存档类
		//lua.new_usertype<DialogueSystem>("GalGameDialogueSystem",
		//	"isTypingText", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsTypingText(); }
		//	),
		//	"FinishTyping", &DialogueSystem::FinishTyping,
		//
		//	"GetDialogCharacter", &DialogueSystem::GetDialogCharacter,
		//	"GetDialogText", &DialogueSystem::GetDialogText,
		//	"dialogNumber", sol::property(
		//		[](DialogueSystem& self) -> unsigned int { return self.GetDialogNumber(); }
		//	),
		//	"autoDialogue", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsAutoDialogue(); },
		//		[](DialogueSystem& self, bool value) { self.AutoDialogue(value); }
		//	),
		//	"fastForward", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsFastForward(); },
		//		[](DialogueSystem& self, bool value) { self.FastForward(value); }
		//	),
		//	"fastForwardDelay", sol::property(
		//		[](DialogueSystem& self) -> float { return self.GetFastForwardDelay(); },
		//		[](DialogueSystem& self, float value) { self.SetFastForwardDelay(value); }
		//	),
		//
		//	//中文
		//	"是否正在打印对话", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsTypingText(); }
		//	),
		//	"完成打印对话", & DialogueSystem::FinishTyping,
		//	"对话数目", sol::property(
		//		[](DialogueSystem& self) -> unsigned int { return self.GetDialogNumber(); }
		//	),
		//	"获取对话人物", & DialogueSystem::GetDialogCharacter,
		//	"获取对话文本", & DialogueSystem::GetDialogText,
		//	"自动对话", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsAutoDialogue(); },
		//		[](DialogueSystem& self, bool value) { self.AutoDialogue(value); }
		//	),
		//	"快进", sol::property(
		//		[](DialogueSystem& self) -> bool { return self.IsFastForward(); },
		//		[](DialogueSystem& self, bool value) { self.FastForward(value); }
		//	),
		//	"快进间隔时间", sol::property(
		//		[](DialogueSystem& self) -> float { return self.GetFastForwardDelay(); },
		//		[](DialogueSystem& self, float value) { self.SetFastForwardDelay(value); }
		//	)
		//	//"跳到对话", & DialogueSystem::JumpToDialog
		//);
		//
		//// 注册引擎类
		//lua.new_usertype<GalGameEngine>("GalGameEngine",
		//	"LoadArchive", &GalGameEngine::LoadArchive,
		//	"DialogueSystem", sol::property(
		//		[](GalGameEngine& self) -> DialogueSystem* { return dynamic_cast<DialogueSystem*>(self.GetDialogueSystem()); }
		//	),
		//
		//	//中文
		//	"等待", sol::yielding(&GalGameEngine::Wait),
		//	"转场命令", & GalGameEngine::TransitionCommand,
		//	"加载剧情脚本", &GalGameEngine::LoadStoryScriptOnUpdate,
		//	"加载存档", &GalGameEngine::LoadArchive,
		//	"对话系统", sol::property(
		//		[](GalGameEngine& self) -> DialogueSystem* { return dynamic_cast<DialogueSystem*>(self.GetDialogueSystem()); }
		//	),
		//	"创建人物", &GalGameEngine::CreateCharacter,
		//	"显示背景", [](GalGameEngine& self, const std::string& path) { return self.ShowSprite("Background", path); },
		//	"显示图片", [](GalGameEngine& self, const std::string& path) { return self.ShowSprite("Scene", path); },
		//	"播放背景音乐", [](GalGameEngine& self, const std::string& path) { return self.PlayAudio("BGM", path); },
		//	"播放效果音乐", [](GalGameEngine& self, const std::string& path) { return self.PlayAudio("Effect", path); },
		//	"隐藏全部人物立绘", &GalGameEngine::HideAllCharacterSprite
		//);

		//lua.set_function("CreateCharacter", &StoryScriptGalGameLuaInterface::CreateCharacter);
		//lua.set_function("ShowBackground", &StoryScriptGalGameLuaInterface::ShowBackground);
		//lua.set_function("ShowImage", &StoryScriptGalGameLuaInterface::ShowImage);
		//lua.set_function("PlayBGM", &StoryScriptGalGameLuaInterface::PlayBGM);
		//lua.set_function("PlaySoundEffect", &StoryScriptGalGameLuaInterface::PlaySoundEffect);
		//
		////中文
		//lua.set_function("创建人物", &StoryScriptGalGameLuaInterface::CreateCharacter);
		//lua.set_function("显示背景", &StoryScriptGalGameLuaInterface::ShowBackground);
		//lua.set_function("显示图片", &StoryScriptGalGameLuaInterface::ShowImage);
		//lua.set_function("播放背景音乐", &StoryScriptGalGameLuaInterface::PlayBGM);
		//lua.set_function("播放效果音乐",&StoryScriptGalGameLuaInterface::PlaySoundEffect);
		//lua.set_function("隐藏全部人物立绘",&StoryScriptGalGameLuaInterface::HideAllCharacterSprite);

		lua.new_usertype<Transform>("Transform",
			sol::constructors<Transform()>()
			//"SlideDown", &Transform::SlideDown
		);
	
		lua.new_usertype<GalCharacter>("Character",
			sol::constructors<GalCharacter(const std::string&)>(),
			"Say", sol::yielding(&GalCharacter::Say),
			"name",&GalCharacter::m_Name,

			//中文
			"创建", & GalCharacter::Create,
			"说着", sol::yielding(&GalCharacter::Say),
			"语音", &GalCharacter::Voice,
			"名称", & GalCharacter::m_Name,
			"添加立绘", &GalCharacter::AddFigure,
			"显示立绘", &GalCharacter::ShowFigure,
			"隐藏立绘", &GalCharacter::HideFigure,
			"添加立绘显示回调", &GalCharacter::AddShowFigureCallback,
			"清除全部立绘显示回调", &GalCharacter::ClearShowFigureCallbacks,
			"添加立绘隐藏回调", & GalCharacter::AddHideFigureCallback,
			"清除全部立绘隐藏回调", & GalCharacter::ClearHideFigureCallbacks,
			"当前立绘",sol::property(
				[](GalCharacter& self) -> GalSprite* { return self.GetCurrentFigure(); }
			),
			"当前语音", sol::property(
				[](GalCharacter& self) -> GalAudio* { return self.GetCurrentVoice(); }
			)
		);

		lua.new_usertype<GalSprite>("Sprite",
			//sol::constructors<Background(const std::string&)>(),
			"Show", &GalSprite::Show,
			"With", sol::overload(
				static_cast<GalSprite * (GalSprite::*)(Transform)>(&GalSprite::With),
				static_cast<GalSprite * (GalSprite::*)(const std::string&)>(&GalSprite::With)
			),
			"Cut", &GalSprite::Cut,
			"SetScale",&GalSprite::SetScale,
			"scaleWidth", sol::property(
				[](GalSprite& self) -> float { return self.GetScaleWidth(); },
				[](GalSprite& self, float value) { self.SetScaleWidth(value); }
			),
			"scaleHeight", sol::property(
				[](GalSprite& self) -> float { return self.GetScaleHeight(); },
				[](GalSprite& self, float value) { self.SetScaleHeight(value); }
			),
			"AlignBottom", &GalSprite::AlignBottom,

			//中文
			"随着", sol::overload(
				static_cast<GalSprite * (GalSprite::*)(Transform)>(&GalSprite::With),
				static_cast<GalSprite * (GalSprite::*)(const std::string&)>(&GalSprite::With)
			),
			"转场", & GalSprite::Cut,
			"设置缩放", & GalSprite::SetScale,
			"设置位置偏移X", & GalSprite::SetPosOffsetX,
			"设置位置偏移Y", & GalSprite::SetPosOffsetY,
			"设置位置X", & GalSprite::SetPosX,
			"设置位置Y", & GalSprite::SetPosY,
			"设置缩放", & GalSprite::SetScale,
			"位置X", sol::property(
				[](GalSprite& self) -> float { return self.GetPosX(); },
				[](GalSprite& self, float value) { self.SetPosX(value); }
			),
			"位置Y", sol::property(
				[](GalSprite& self) -> float { return self.GetPosY(); },
				[](GalSprite& self, float value) { self.SetPosY(value); }
			),
			"宽度缩放", sol::property(
				[](GalSprite& self) -> float { return self.GetScaleWidth(); },
				[](GalSprite& self, float value) { self.SetScaleWidth(value); }
			),
			"高度缩放", sol::property(
				[](GalSprite& self) -> float { return self.GetScaleHeight(); },
				[](GalSprite& self, float value) { self.SetScaleHeight(value); }
			),
			"底部对齐", & GalSprite::AlignBottom,

			//属性
			"path", & GalSprite::m_Path,
			"路径", & GalSprite::m_Path
		);

		lua.new_usertype<GalAudio>("Audio",
			"设置循环播放",&GalAudio::SetLoop,
			"停止播放",&GalAudio::Stop,
			"是否正在播放",&GalAudio::IsPlayingAudio,
			"是否循环播放",&GalAudio::IsLooping,
			"设置音量",&GalAudio::SetVolume,
			"获取音量",&GalAudio::GetVolume,
			"随着",&GalAudio::With,

			"路径", &GalAudio::m_Path
		);
	}
	*/
}

