#include "Galgame/Game.h"
#include "Galgame/GalGameEngine.h"
#include "Galgame/GameEngineCore.h"
#include "Galgame/SpriteTransformScript.h"
#include "Galgame/SpriteTransformScriptManager.h"
#include "Audio/AudioTransformScriptManager.h"
#include "Render/TransitionManager.h"

namespace VisionGal::GalGame
{
	Transform::Transform()
	{
	}

	GalSprite::GalSprite(const std::string& layer, const std::string& path)
		:m_Layer(layer),
		m_Path(path)
	{
		
	} 

	GalSprite::~GalSprite()
	{
		if (m_Actor == nullptr)
			return;

		auto* scene = dynamic_cast<Scene*>(m_Actor->GetScene());

		if (scene != nullptr)
		{
			scene->RemoveEntity(m_Actor->GetEntityID());
		}
	}

	const std::string& GalSprite::GetResourcePath()
	{
		return m_Path;
	}

	GameActor* GalSprite::GetResourceActor()
	{
		return m_Actor;
	}

	const std::string& GalSprite::GetResourceLayer()
	{
		return m_Layer;
	}

	void GalSprite::SetResourceLayer(const std::string& layer)
	{
		m_Layer = layer;
	}

	GalSprite* GalSprite::Show()
	{
		return this;
	}

	GalSprite* GalSprite::With(Transform transform)
	{
		return this;
	}

	GalSprite* GalSprite::With(const std::string& transform)
	{
		SpriteTransformScriptManager::StartSpriteTransformWithCommand(m_Actor, transform);

		return this;
	}

	GalSprite* GalSprite::SetPosX(float offset)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->location.x = offset;
			transform->is_dirty = true;
		}

		return this;
	}

	GalSprite* GalSprite::SetPosY(float offset)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->location.y = offset;
			transform->is_dirty = true;
		}

		return this;
	}

	float GalSprite::GetPosX()
	{
		if (auto* transform = GetTransformComponent())
		{
			return transform->location.x;
		}

		return 0.f;
	}

	float GalSprite::GetPosY()
	{
		if (auto* transform = GetTransformComponent())
		{
			return transform->location.y;
		}

		return 0.f;
	}

	GalSprite* GalSprite::SetPosOffsetX(float offset)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->location.x += offset;
			transform->is_dirty = true;
		}

		return this;
	}

	GalSprite* GalSprite::SetPosOffsetY(float offset)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->location.y += offset;
			transform->is_dirty = true;
		}

		return this;
	}

	GalSprite* GalSprite::SetScale(float scale)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->scale = float3(scale, scale, scale);
			transform->is_dirty = true;
		}

		return this;
	}

	GalSprite* GalSprite::SetScaleWidth(float scale)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->scale.x = scale;
			transform->is_dirty = true;
		}

		return this;
	}

	GalSprite* GalSprite::SetScaleHeight(float scale)
	{
		if (auto* transform = GetTransformComponent())
		{
			transform->scale.y = scale;
			transform->is_dirty = true;
		}

		return this;
	}

	float GalSprite::GetScaleWidth()
	{
		if (auto* transform = GetTransformComponent())
		{
			return transform->scale.x;
		}

		return 1.0f;
	}

	float GalSprite::GetScaleHeight()
	{
		if (auto* transform = GetTransformComponent())
		{
			return transform->scale.y;
		}

		return 1.0f;
	}

	GalSprite* GalSprite::AlignBottom()
	{
		if (GetResourceActor())
		{
			auto* actor = GetResourceActor();
			auto* sr = actor->GetComponent<SpriteRendererComponent>();

			if (sr)
			{
				auto* tex = sr->sprite->GetTexture2D();
				return AlignBottomWithTexture(tex);
			}
		}

		return this;
	}

	GalSprite* GalSprite::AlignBottomWithTexture(Texture2D* tex)
	{
		if (tex == nullptr)
			return this;

		if (auto* transform = GetTransformComponent())
		{
			float yOffset = GameEngineCore::GetSpriteYOffset(tex->Height() * transform->scale.y);
			transform->location.y = yOffset;
			transform->is_dirty = true;
		}

		return this;
	}

	TransformComponent* GalSprite::GetTransformComponent()
	{
		if (GetResourceActor())
		{
			return GetResourceActor()->GetComponent<TransformComponent>();
		}

		return nullptr;
	}

	void GalSprite::Cut(const std::string& cmd)
	{
		if (GameEngineCore::GetCurrentEngine()->GetDialogueSystem()->IsFastForward())
		{
			return;
		}

		TransitionManager::GetInstance()->StartTransitionWithCommand("Background", cmd);
		//if (auto transition = TransitionManager::CreateTransitionWithCommand(cmd))
		//{
		//	transition->SetLayer("Background");
		//	transition->Start();
		//	GameEngineCore::GetCurrentEngine()->SceneTransition(transition);
		//}
	}

	GalAudio::GalAudio(const std::string& layer, const std::string& path)
	{
		m_Layer = layer;
		m_Path = path;
		GameEngineCore::GetCurrentEngine()->PreLoadResource(path);
	}

	GalAudio::~GalAudio()
	{
		if (m_Actor == nullptr)
			return;

		auto* scene = dynamic_cast<Scene*>(m_Actor->GetScene());
		auto* audioSource = m_Actor->GetComponent<AudioSourceComponent>();

		if (audioSource != nullptr)
		{
			audioSource->Stop();
		}

		if (scene != nullptr)
		{
			scene->RemoveEntity(m_Actor->GetEntityID());
		}
	}

	const std::string& GalAudio::GetResourcePath()
	{
		return m_Path;
	}

	GameActor* GalAudio::GetResourceActor()
	{
		return m_Actor;
	}

	const std::string& GalAudio::GetResourceLayer()
	{
		return m_Layer;
	}

	void GalAudio::SetResourceLayer(const std::string& layer)
	{
		m_Layer = layer;
	}

	GalAudio* GalAudio::SetLoop(bool enable)
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			com->SetLoop(enable);
		}

		return this;
	}

	GalAudio* GalAudio::Stop()
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			com->Stop();
		}

		return this;
	}

	bool GalAudio::IsPlayingAudio()
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			return com->IsPlayingAudio();
		}

		return false;
	}

	bool GalAudio::IsLooping()
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			return com->IsLooping();
		}

		return false;
	}

	GalAudio* GalAudio::SetVolume(float v)
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			com->SetVolume(v);
		}

		return this;
	}

	float GalAudio::GetVolume()
	{
		auto* com = GetResourceActor()->GetComponent<AudioSourceComponent>();
		if (com)
		{
			return com->GetVolume();
		}

		return 0.f;
	}

	GalAudio* GalAudio::With(const std::string& transform)
	{
		AudioTransformScriptManager::StartAudioTransformWithCommand(m_Actor, transform);

		return nullptr;
	}

	GalCharacter::GalCharacter(const std::string& name)
	{
		this->m_Name = name;
	}

	GalCharacter GalCharacter::Create(const std::string& name)
	{
		return GalCharacter(name);
	}

	void GalCharacter::Say(const std::string& text)
	{
		GameEngineCore::GetCurrentEngine()->GetDialogueSystem()->CharacterSay(m_Name,text);
	}

	GalAudio* GalCharacter::Voice(const std::string& path)
	{
		if (GameEngineCore::GetCurrentEngine()->GetDialogueSystem()->IsFastForward())
		{
			return nullptr;
		}

		auto* engine = GameEngineCore::GetCurrentEngine();

		auto* voice = engine->PlayAudio("Voice", path);

		if (voice == nullptr)
			return nullptr;

		// 删除最后的声音
		if (m_LastState.Voice != nullptr)
		{
			m_LastState.Voice->Stop();
			engine->RemoveAudio(m_LastState.Voice);
		}

		// 停止当前声音
		if (m_CurrentState.Voice)
		{
			m_CurrentState.Voice->Stop();
		}

		// 保存到最后的声音状态
		m_LastState.Voice = m_CurrentState.Voice;

		// 保存当前声音状态
		m_CurrentState.Voice = voice;

		return voice;
	}

	GalAudio* GalCharacter::GetCurrentVoice()
	{
		return m_CurrentState.Voice;
	}

	void GalCharacter::AddFigure(const String& state, const String& spritePath)
	{
		m_CharacterSpriteStates[state] = spritePath;
	}

	GalSprite* GalCharacter::ShowFigure(const String& state)
	{
		auto* engine = GameEngineCore::GetCurrentEngine();

		// 隐藏当前立绘
		HideFigure();

		// 查找人物立绘状态
		auto result = m_CharacterSpriteStates.find(state);
		if (result != m_CharacterSpriteStates.end())
		{
			// 显示立绘
			auto& path = result->second;
			//auto* sprite = engine->ShowSprite("Scene", path);
			auto* sprite = engine->ShowSprite("SceneCharacterSpriteCurrent", path);

			if (sprite == nullptr)
				return nullptr;

			// 调用显示回调
			for (auto& callback:m_ShowFigureCallbacks)
			{
				sol::protected_function_result res = callback(sprite);
				if (!res.valid()) {
					sol::error err = res;
					H_LOG_ERROR("%s", err.what());
				}
			}

			// 复制立绘X位置
			if (m_CurrentState.Sprite)
			{
				sprite->SetPosX(m_CurrentState.Sprite->GetPosX());
			}

			// 删除最后的立绘
			if (m_LastState.Sprite != nullptr)
			{
				engine->RemoveSprite(m_LastState.Sprite);
			}

			// 保存到最后的立绘状态
			m_LastState.State = m_CurrentState.State;
			m_LastState.Sprite = m_CurrentState.Sprite;
			m_LastState.IsHide = m_CurrentState.IsHide;

			// 将上一个立绘移动到前一层
			engine->GetLayeredSceneManager()->MoveSpriteToLayer(m_LastState.Sprite, "SceneCharacterSpritePrev");

			// 保存当前显示状态
			m_CurrentState.State = state;
			m_CurrentState.Sprite = sprite;
			m_CurrentState.IsHide = false;
			return sprite;
		}

		return nullptr;
	}

	void GalCharacter::HideFigure()
	{
		if (m_CurrentState.IsHide == true)
		{
			return;
		}

		if (m_CurrentState.Sprite != nullptr && m_CurrentState.IsHide == false)
		{
			// 调用隐藏回调
			for (auto& callback : m_HideFigureCallbacks)
			{
				sol::protected_function_result res = callback(m_CurrentState.Sprite);
				if (!res.valid()) {
					sol::error err = res;
					H_LOG_ERROR("%s", err.what());
				}

			}

			m_CurrentState.IsHide = true;
		}
	}

	GalSprite* GalCharacter::GetCurrentFigure()
	{
		return m_CurrentState.Sprite;
	}

	void GalCharacter::AddShowFigureCallback(sol::function callback)
	{
		m_ShowFigureCallbacks.push_back(callback);
	}

	void GalCharacter::AddHideFigureCallback(sol::function callback)
	{
		m_HideFigureCallbacks.push_back(callback);
	}

	void GalCharacter::ClearShowFigureCallbacks()
	{
		m_ShowFigureCallbacks.clear();
	}

	void GalCharacter::ClearHideFigureCallbacks()
	{
		m_HideFigureCallbacks.clear();
	}
}

