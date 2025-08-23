#pragma once
#include "../EngineConfig.h"
#include "../Interface/GameInterface.h"
#include "../Interface/SceneInterface.h"

namespace VisionGal
{
    struct IGameActorFactory
    {
        virtual ~IGameActorFactory() = default;

        virtual GameActor* CreateActor(IScene* scene, const String& type, IEntity* parent = nullptr) = 0;
    };

    class GameActorFactory: public IGameActorFactory
    {
    public:
        GameActorFactory();
        ~GameActorFactory() override = default;
        GameActorFactory(const GameActorFactory&) = delete;
        GameActorFactory& operator=(const GameActorFactory&) = delete;
        GameActorFactory(GameActorFactory&&) noexcept = default;
        GameActorFactory& operator=(GameActorFactory&&) noexcept = default;

        GameActor* CreateActor(IScene* scene, const String& type, IEntity* parent = nullptr) override;

        std::vector<String>& GetActorTypeList();
    private:
        std::vector<String> m_ActorTypeList;
    };

	VG_ENGINE_API GameActorFactory* GetGameActorFactory();
}
