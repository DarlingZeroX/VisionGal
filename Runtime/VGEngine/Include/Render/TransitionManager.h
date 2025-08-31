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

		/// 通过转场命令创建转场对象
		static Ref<ISceneTransition> CreateTransitionWithCommand(const String& cmd);
		static Ref<ISceneTransition> CreateCustomImageTransitionWithCommand(const String& imagePath, const String& cmd);

		bool StartTransitionWithCommand(const String& layer, const String& cmd);
		bool StartCustomImageTransitionWithCommand(const String& layer, const String& imagePath, const String& cmd);

		void StartTransition(const Ref<ISceneTransition>& transition);
		void Update();
		ISceneTransition* GetLayerTransition(const String& layer);
		void LayerTransition(const String& layer, const Ref<VGFX::ITexture>& prevFrame, const Ref<VGFX::ITexture>& nextFrame);

		Horizon::HEventDelegate<const TransitionEvent&> OnTransitionEvent;
	private:
		std::unordered_map<String, std::queue<Ref<ISceneTransition>> > m_Transitions;
	};

}