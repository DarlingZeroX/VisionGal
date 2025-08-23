#include "../Core/Core.h"
#include "../Interface/GameInterface.h"

namespace VisionGal {

	class AudioTransformScriptManager
	{
	public:
		static AudioTransformScriptManager* GetInstance();

		static Ref<ITransformScript> CreateAudioTransformWithCommand(GameActor* actor, const String& cmd);

		static bool StartAudioTransformWithCommand(GameActor* actor, const String& cmd);
		static bool StartAudioTransform(GameActor* actor, const Ref<ITransformScript>& script);
	};

}