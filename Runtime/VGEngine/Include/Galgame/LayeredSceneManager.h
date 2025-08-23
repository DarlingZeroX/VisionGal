#pragma once
#include "Interface.h"
#include "../EngineConfig.h"
#include "../Scene/Scene.h"
#include "../Render/Core.h"
#include <deque>
#include "Game.h"

namespace VisionGal::GalGame
{
	class VG_ENGINE_API LayeredSceneManager: public ILayeredSceneManager
	{
	public:
		LayeredSceneManager();
		~LayeredSceneManager() override = default;
		LayeredSceneManager(const LayeredSceneManager&) = delete;
		LayeredSceneManager& operator=(const LayeredSceneManager&) = delete;
		LayeredSceneManager(LayeredSceneManager&&) noexcept = default;
		LayeredSceneManager& operator=(LayeredSceneManager&&) noexcept = default;

		//void SetBackgroundImage(const String& path);
		//GameActor* ShowImage(const String& path);

		void ShowSprite(const String& layer, GameActor* actor) override;
		void AddSprite(IGalGameSprite* sprite) override;
		void AddAudio(IGalGameAudio* audio) override;

		bool RemoveSprite(IGalGameSprite* sprite) override;
		bool RemoveAudio(IGalGameAudio* audio) override;

		bool MoveSpriteToLayer(IGalGameSprite* sprite, const String& layer) override;

		void ClearSpriteLayer(const String& layer) override;
		void ClearSoundLayer(const String& layer) override;
		void ClearAllSprite() override;
		void ClearAllAudio() override;
		void ClearAll() override;

		void TraverseSpriteLayer(const String& layer, const std::function<void(IGalGameSprite* sprite)>& callback) override;
		void TraverseSprite(const std::function<void(IGalGameSprite* sprite)>& callback) override;
		void TraverseAudioLayer(const String& layer, const std::function<void(IGalGameAudio* audio)>& callback) override;
		void TraverseAudio(const std::function<void(IGalGameAudio* audio)>& callback) override;
		void TraverseScene(std::function<void(IGalGameResource* actor)> callback) override;
	public:
		//void Initialize(Scene* scene);
		//void OnRender();
		//void OnUpdate();
		void Initialize();
	private:
		std::deque<std::vector<IGalGameSprite*>>  m_Sprite;
		std::vector<std::vector<IGalGameAudio*>> m_Audio;

		std::unordered_map<String, int> m_SpriteLayer;
		std::unordered_map<String, int> m_AudioLayer;
	};


}
