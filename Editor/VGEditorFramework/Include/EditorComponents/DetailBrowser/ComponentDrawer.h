#pragma once
#include "Interface.h"
#include <VGEngine/Include/Galgame/Components.h>
#include <VGEngine/Include/Scene/Components.h>

namespace VisionGal::Editor
{
	struct TransformComponentDrawer : public IComponentDrawer
	{
		~TransformComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;
	};

	struct CameraComponentDrawer : public IComponentDrawer
	{
		~CameraComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;
	};

	struct SpriteRendererComponentDrawer: public IComponentDrawer
	{
		~SpriteRendererComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void SpriteBeginDropTarget(SpriteRendererComponent* com);
	};

	struct ScriptComponentDrawer: public IComponentDrawer
	{
		~ScriptComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void ScriptBeginDropTarget(IScript* script, IScriptVariable& var);
	};

	struct RmlUIDocumentComponentDrawer : public IComponentDrawer
	{
		~RmlUIDocumentComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void DocumentBeginDropTarget(RmlUIDocumentComponent* com);
	};

	struct AudioSourceComponentDrawer : public IComponentDrawer
	{
		~AudioSourceComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void AudioSourceBeginDropTarget(AudioSourceComponent* com);
	};

	struct VideoPlayerComponentDrawer : public IComponentDrawer
	{
		~VideoPlayerComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void VideoPlayerBeginDropTarget(VideoPlayerComponent* com);
	};

	struct GalGameEngineComponentDrawer: public IComponentDrawer
	{
		~GalGameEngineComponentDrawer() override = default;

		void OnGUI(IEntity* entity) override;
		const String GetBindType() const override;

		void ScriptBeginDropTarget(GalGame::GalGameEngineComponent* com);
	};
}