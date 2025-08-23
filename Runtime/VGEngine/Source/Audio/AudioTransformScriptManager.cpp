#include "Audio/AudioTransformScriptManager.h"
#include "Scene/Components.h"
#include "Audio/AudioTransformScript.h"

namespace VisionGal {

	AudioTransformScriptManager* AudioTransformScriptManager::GetInstance()
	{
		static AudioTransformScriptManager s_Manager;
		return &s_Manager;
	}

	Ref<ITransformScript> AudioTransformScriptManager::CreateAudioTransformWithCommand(GameActor* actor, const String& cmd)
	{
		if (actor == nullptr)
			return nullptr;

		std::istringstream iss(cmd);
		auto* audioSource = actor->GetComponent<AudioSourceComponent>();

		if (audioSource == nullptr)
			return nullptr;

		std::string command;       // 如 "slidedown"
		float duration = 1.0f;     // 如 1.0
		std::string transition;    // 可选，如 "easein"

		iss >> command;
		iss >> duration;
		iss >> transition;

		{
			H_LOG_INFO("Audio Command: %s, Duration: %f, Transition: %s", command.c_str(), duration, transition.c_str());
		}

		if (command == "fade_in" || command == "淡入")
		{
			auto transform = CreateRef<AudioFadeInOutTransformScript>(AudioFadeInOutTransformScript::Direction::In);
			transform->SetInVolume(audioSource->volume);
			transform->SetDuration(duration);
			return transform;
		}

		if (command == "fade_out" || command == "淡出")
		{
			auto transform = CreateRef<AudioFadeInOutTransformScript>(AudioFadeInOutTransformScript::Direction::Out);
			transform->SetOutVolume(audioSource->volume);
			transform->SetDuration(duration);
			return transform;
		}

		H_LOG_WARN("Unknown Command: %s", cmd.c_str());

		return nullptr;
	}

	bool AudioTransformScriptManager::StartAudioTransformWithCommand(GameActor* actor, const String& cmd)
	{
		auto script = CreateAudioTransformWithCommand(actor, cmd);

		if (script != nullptr)
		{
			//开启变换
			script->Start();

			return StartAudioTransform(actor, script);
		}

		return false;
	}

	bool AudioTransformScriptManager::StartAudioTransform(GameActor* actor, const Ref<ITransformScript>& script)
	{
		if (actor == nullptr)
			return false;

		if (script == nullptr)
			return false;

		auto* com = actor->GetComponent<TransformScriptComponent>();

		if (com == nullptr)
		{
			com = actor->AddComponent<TransformScriptComponent>();
		}

		com->scripts.push_back(script);

		return true;
	}

}
