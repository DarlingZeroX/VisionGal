#include "../Core/Core.h"
#include "../Interface/RenderInterface.h"
#include <HCore/Include/Event/HEventDelegate.h>

namespace VisionGal {

	////////////////		Transition Event
	enum class TransitionEventType
	{
		None = 0,
		TransitionCreated,
	};

	struct TransitionEvent
	{
		TransitionEventType EventType = TransitionEventType::None;
		String Layer;
		ISceneTransition* Transition;
	};

	class TransitionManager
	{
	public:
		static TransitionManager* GetInstance();

		static Ref<ISceneTransition> CreateTransitionWithCommand(const String& cmd);
		bool StartTransitionWithCommand(const String& layer, const String& cmd);
		void StartTransition(const Ref<ISceneTransition>& transition);
		void Update();
		ISceneTransition* GetLayerTransition(const String& layer);
		void LayerTransition(const String& layer, const Ref<VGFX::ITexture>& prevFrame, const Ref<VGFX::ITexture>& nextFrame);

		Horizon::HEventDelegate<const TransitionEvent&> OnTransitionEvent;
	private:
		std::unordered_map<String, std::queue<Ref<ISceneTransition>> > m_Transitions;
	};

}