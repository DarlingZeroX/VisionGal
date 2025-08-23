#include "Lua/SceneLuaInterface.h"		

#include "Engine/Manager.h"
#include "Scene/GameActor.h"
#include "Scene/Components.h"

namespace VisionGal
{
	namespace Lua
	{

		sol::object GameActorGetComponentByType(GameActor* self, const String& type, sol::this_state  lua)
		{
			// 显式转换为具体类型
			if (type == "Transform") {
				return sol::make_object(lua, self->GetComponent<TransformComponent>());
			}
			if (type == "SpriteRenderer") {
				return sol::make_object(lua, self->GetComponent<SpriteRendererComponent>());
			}
			if (type == "VideoPlayer") {
				return sol::make_object(lua, self->GetComponent<VideoPlayerComponent>());
			}

			return sol::nil;
		}
	}

	void SceneLuaInterface::Initialize(sol::state& lua)
	{
		lua.new_usertype<int2>("int2",
			sol::constructors<int2()>(),
			"x", &int2::x,
			"y", &int2::y
		);

		lua.new_usertype<float2>("float2",
			sol::constructors<float2()>(),
			"x", &float2::x,
			"y", &float2::y,
			"r", &float2::x,
			"g", &float2::y
		);

		lua.new_usertype<float3>("float3",
			sol::constructors<float3()>(),
			"x", &float3::x,
			"y", &float3::y,
			"z", &float3::z,
			"r", &float3::x,
			"g", &float3::y,
			"b", &float3::z
		);

		lua.new_usertype<float4>("float4",
			sol::constructors<float4()>(),
			"x", &float4::x,
			"y", &float4::y,
			"z", &float4::z,
			"w", &float4::w,
			"r", &float4::x,
			"g", &float4::y,
			"b", &float4::z,
			"a", &float4::w
		);

		lua.new_usertype<quaternion>("quaternion",
			sol::constructors<quaternion()>(),
			"x", &quaternion::x,
			"y", &quaternion::y,
			"z", &quaternion::z,
			"w", &quaternion::w
		);

		lua.new_usertype<IComponent>("IComponent");

		// 绑定 TransformComponent
		lua.new_usertype<TransformComponent>("TransformComponent",
			sol::bases<IComponent>(),
			sol::constructors<TransformComponent()>(),
			// 指定 location 为可读写属性
			"location", sol::property(
				[](TransformComponent& self) -> float3& { return self.location; },
				[](TransformComponent& self, const float3& value) { self.location = value; self.is_dirty = true; }
			),
			// 指定 rotation 为可读写属性
			"rotation", sol::property(
				[](TransformComponent& self) -> quaternion& { return self.rotation; },
				[](TransformComponent& self, const float3& value) { self.rotation = value; self.is_dirty = true; }
			),
			// 指定 scale 为可读写属性
			"scale", sol::property(
				[](TransformComponent& self) -> float3& { return self.scale; },
				[](TransformComponent& self, const float3& value) { self.scale = value; self.is_dirty = true; }
			),
			"visible", &TransformComponent::visible
		);

		// 绑定 SpriteRendererComponent
		lua.new_usertype<SpriteRendererComponent>("SpriteRendererComponent",
			sol::bases<IComponent>(),
			sol::constructors<SpriteRendererComponent()>(),
			"color", &SpriteRendererComponent::color,
			"flip", &SpriteRendererComponent::flip
		);

		// 绑定 VideoPlayerComponent
		lua.new_usertype<VideoPlayerComponent>("VideoPlayerComponent",
			sol::bases<IComponent>(),
			sol::constructors<VideoPlayerComponent()>(),
			"playOnAwake", &VideoPlayerComponent::playOnAwake,
			"loop", &VideoPlayerComponent::loop,
			"waitForFirstFrame", &VideoPlayerComponent::waitForFirstFrame,
			"Play", &VideoPlayerComponent::Play,
			"Stop", &VideoPlayerComponent::Stop
		);
		// 绑定 AudioSourceComponent
		lua.new_usertype<AudioSourceComponent>("AudioSourceComponent",
			sol::bases<IComponent>(),
			sol::constructors<AudioSourceComponent()>(),
			//"clip", &AudioSourceComponent::clip,
			"volume", &AudioSourceComponent::volume,
			//"pitch", &AudioSourceComponent::pitch,
			"Play", &AudioSourceComponent::Play,
			"Stop", &AudioSourceComponent::Stop
		);

		lua.new_usertype<GameActor>("GameActor",
			sol::constructors<GameActor()>(),
			"label", sol::property(
				[](GameActor& self) -> std::string { return self.GetLabel(); },
				[](GameActor& self, const std::string& value) { self.SetLabel(value); }
			),
			"visible", sol::property(
				[](GameActor& self) -> bool { return self.GetVisible(); },
				[](GameActor& self, bool value) { self.SetVisible(value); }
			),
			"GetComponent", &Lua::GameActorGetComponentByType,
			"AddComponent", &GameActor::AddComponentByType
		);

		lua.new_usertype<SceneManager>("SceneManagerClass",
			"LoadScene", &SceneManager::LoadScene
		);

		lua["SceneManager"] = sol::make_object(lua, SceneManager::Get());
	}

}


