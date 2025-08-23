#include "../Core/Core.h"
#include "../Interface/GameInterface.h"

namespace VisionGal::GalGame {

	class SpriteTransformScriptManager
	{
	public:
		static SpriteTransformScriptManager* GetInstance();

		static Ref<ITransformScript> CreateSpriteTransformWithCommand(GameActor* actor, const String& cmd);

		static bool StartSpriteTransformWithCommand(GameActor* actor, const String& cmd);
		static bool StartSpriteTransform(GameActor* actor, const Ref<ITransformScript>& script);

		//void Update(IScene* scene);
	};

}