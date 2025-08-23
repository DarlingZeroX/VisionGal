#include "Galgame/LayeredSceneManager.h"

namespace VisionGal::GalGame
{
	LayeredSceneManager::LayeredSceneManager()
	{
		Initialize();
	}

	void LayeredSceneManager::ShowSprite(const String& layer, GameActor* actor)
	{
		//auto& sprites = m_Sprite[m_SpriteLayer[layer]];
		//
		//for (auto& sprite : sprites)
		//{
		//	if (sprite == actor)
		//	{
		//		sprite = nullptr;
		//	}
		//}
		//
		//sprites.push_back(actor);
	}

	void LayeredSceneManager::AddSprite(IGalGameSprite* sprite)
	{
		if (sprite == nullptr)
			return;

		auto& sprites = m_Sprite[m_SpriteLayer[sprite->GetResourceLayer()]];

		for (auto& sp : sprites)
		{
			if (sp == sprite)
			{
				delete sp;
				sp = nullptr;
			}
		}

		sprites.push_back(sprite);
	}

	void LayeredSceneManager::AddAudio(IGalGameAudio* audio)
	{
		if (audio == nullptr)
			return;

		if (audio->GetResourceLayer() == "Voice")
		{
			auto& layer = m_Audio[m_AudioLayer[audio->GetResourceLayer()]];
			for (auto& audio: layer)
			{
				auto* galAudio = dynamic_cast<GalAudio*>(audio);
				if (galAudio != nullptr)
				{
					galAudio->Stop();
				}
			}
		}

		m_Audio[m_AudioLayer[audio->GetResourceLayer()]].push_back(audio);
	}

	bool LayeredSceneManager::RemoveSprite(IGalGameSprite* sprite)
	{
		if (sprite == nullptr)
			return false;

		auto& sprites = m_Sprite[m_SpriteLayer[sprite->GetResourceLayer()]];
		for (auto& sp : sprites)
		{
			if (sp == sprite)
			{
				delete sp;
				sp = nullptr;
				return true;
			}
		}

		return false;
	}

	bool LayeredSceneManager::RemoveAudio(IGalGameAudio* audio)
	{
		if (audio == nullptr)
			return false;

		auto& audios = m_Audio[m_AudioLayer[audio->GetResourceLayer()]];
		for (auto& ad : audios)
		{
			if (ad == audio)
			{
				delete ad;
				ad = nullptr;
				return true;
			}
		}

		return false;
	}

	bool LayeredSceneManager::MoveSpriteToLayer(IGalGameSprite* sprite, const String& layer)
	{
		if (sprite == nullptr)
			return false;

        // 检查当前层和目标层是否存在
        if (m_SpriteLayer.find(sprite->GetResourceLayer()) == m_SpriteLayer.end() ||
        m_SpriteLayer.find(layer) == m_SpriteLayer.end())
        {
			return false;
        }

        auto& currentLayer = m_Sprite[m_SpriteLayer[sprite->GetResourceLayer()]];
        auto& targetLayer = m_Sprite[m_SpriteLayer[layer]];

		// 从当前层移除精灵
		auto it = std::find(currentLayer.begin(), currentLayer.end(), sprite);
		if (it != currentLayer.end())
		{
			currentLayer.erase(it);
		}

		// 添加到目标层
		targetLayer.push_back(sprite);
		sprite->SetResourceLayer(layer);
		return true;
	}

	void LayeredSceneManager::ClearSpriteLayer(const String& layer)
	{
		m_Sprite[m_SpriteLayer[layer]].clear();
	}

	void LayeredSceneManager::ClearSoundLayer(const String& layer)
	{
		m_Audio[m_AudioLayer[layer]].clear();
	}

	void LayeredSceneManager::ClearAllSprite()
	{
		TraverseSprite([this](IGalGameSprite* sprite)
			{
				delete sprite;
			});

		for (auto& layer : m_Sprite)
			layer.clear();
	}

	void LayeredSceneManager::ClearAllAudio()
	{
		TraverseAudio([this](IGalGameAudio* audio)
			{
				delete audio;
			});

		for (auto& audio : m_Audio)
			audio.clear();
	}

	void LayeredSceneManager::ClearAll()
	{
		ClearAllAudio();
		ClearAllSprite();
	}

	void LayeredSceneManager::TraverseSpriteLayer(const String& layer, const std::function<void(IGalGameSprite* galSprite)>& callback)
	{
		auto& sprites = m_Sprite[m_SpriteLayer[layer]];

		for (auto* sprite: sprites)
		{
			if (sprite != nullptr)
			{
				callback(sprite);
			}
		}
	}

	void LayeredSceneManager::TraverseSprite(const std::function<void(IGalGameSprite* galSprite)>& callback)
	{
		for (auto& layer : m_Sprite)
		{
			for (auto* sprite : layer)
			{
				if (sprite != nullptr)
				{
					callback(sprite);
				}
			}
		}
	}

	void LayeredSceneManager::TraverseAudioLayer(const String& layer, const std::function<void(IGalGameAudio* audio)>& callback)
	{
		auto& sounds = m_Audio[m_AudioLayer[layer]];

		for (auto* sound : sounds)
		{
			if (sound != nullptr)
			{
				callback(sound);
			}
		}
	}

	void LayeredSceneManager::TraverseAudio(const std::function<void(IGalGameAudio* audio)>& callback)
	{
		for (auto& layer : m_Audio)
		{
			for (auto* sound : layer)
			{
				if (sound != nullptr)
				{
					callback(sound);
				}
			}
		}
	}

	void LayeredSceneManager::TraverseScene(std::function<void(IGalGameResource* resource)> callback)
	{
		TraverseSprite(callback);
		TraverseAudio(callback);
	}

	void LayeredSceneManager::Initialize()
	{
		m_SpriteLayer["Background"] = 0;
		m_SpriteLayer["Scene"] = 1;
		m_SpriteLayer["SceneCharacterSpriteCurrent"] = 2;
		m_SpriteLayer["SceneCharacterSpritePrev"] = 3;

		for (auto& layer : m_SpriteLayer)
		{
			m_Sprite.emplace_back();
		}

		m_AudioLayer["BGM"] = 0;
		m_AudioLayer["Voice"] = 1;
		m_AudioLayer["Effect"] = 2;
		m_AudioLayer["System"] = 3;

		for (auto& layer : m_AudioLayer)
		{
			m_Audio.emplace_back();
		}
	}
}
