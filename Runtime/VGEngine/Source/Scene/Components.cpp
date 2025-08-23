#include "Scene/Components.h"
#include <HCore/Include/Math/GLM/ext/matrix_transform.hpp>
#include "Engine/Manager.h"
#include "HCore/Include/Math/GLM/gtc/quaternion.hpp"

namespace VisionGal
{
	TransformComponent::TransformComponent()
	{
		location = float3(0.0f);
		rotation = float3(0.0f);
		scale = float3(1.0f);
		model = glm::mat4(1.0f);
		is_dirty = false;
		visible = true;
	}

	std::string TransformComponent::GetComponentType() const
	{
		return std::string("Transform");
	}

	void TransformComponent::Update()
	{
		if (is_dirty)
		{
			// 构建缩放矩阵
			model = glm::scale(glm::identity<matrix4x4>(), scale);  // 缩放

			// 从四元数构建旋转矩阵
			model = model * glm::mat4_cast( rotation);

			// 旋转（注意顺序：ZYX）
			//model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));  // 绕Z轴
			//model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));  // 绕Y轴
			//model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));  // 绕X轴

			// 构建平移矩阵
			model = glm::translate(model, location);  // 位移
		}

		is_dirty = false;
	}

	SpriteRendererComponent::SpriteRendererComponent()
	{
		color = float4(1.0f, 1.0f, 1.0f, 1.0f);
		flip = int2(0, 0);
		material = CreateRef<Material>();
		sprite = nullptr;
	}

	std::string SpriteRendererComponent::GetComponentType() const
	{
		return std::string("SpriteRenderer");;
	}

	FullScreenRendererComponent::FullScreenRendererComponent()
	{
		image = FullScreenQuad::Create();
		shader = ShaderManager::Get()->GetBuiltinProgram("FullScreenQuad");
	}

	std::string FullScreenRendererComponent::GetComponentType() const
	{
		return std::string("FullScreenRenderer");
	}

	ScriptComponent::ScriptComponent()
	{

	}

	std::string ScriptComponent::GetComponentType() const
	{
		return std::string("Script");
	}

	CameraComponent::CameraComponent()
	{
		camera = nullptr;
	}

	std::string CameraComponent::GetComponentType() const
	{
		return std::string("Camera");
	}

	VideoPlayerComponent::VideoPlayerComponent()
	{
		videoPlayer = CreateRef<VideoPlayer>();
	}

	std::string VideoPlayerComponent::GetComponentType() const
	{
		return "VideoPlayer";
	}

	bool VideoPlayerComponent::Play()
	{
		if (videoClip)
		{
			videoPlayer->Open(videoClip);
			videoPlayer->Play();
			return true;
		}

		return false;
	}

	void VideoPlayerComponent::Stop()
	{
		if (videoClip)
		{
			videoPlayer->Stop();
		}
	}

	void VideoPlayerComponent::Update()
	{
		if (videoClip)
		{
			videoPlayer->Update();
		}
	}

	AudioSourceComponent::AudioSourceComponent()
	{
		audioPlayer = CreateRef<AudioPlayer>();
	}

	std::string AudioSourceComponent::GetComponentType() const
	{
		return "AudioSourceComponent";
	}

	bool AudioSourceComponent::Play()
	{
		if (audioClip)
		{
			audioPlayer->OpenAudioClip(audioClip);
			audioPlayer->SetLoop(loop);
			audioPlayer->SetVolume(volume);
			return audioPlayer->Play();
		}

		return false;
	}

	void AudioSourceComponent::Stop()
	{
		audioPlayer->Stop();
	}

	void AudioSourceComponent::Update()
	{
	}

	void AudioSourceComponent::SetVolume()
	{
		audioPlayer->SetVolume(volume);
	}

	void AudioSourceComponent::SetVolume(float volume)
	{
		this->volume = volume;
		SetVolume();
	}

	float AudioSourceComponent::GetVolume() const
	{
		return audioPlayer->GetVolume();
	}

	void AudioSourceComponent::SetLoop(bool enable)
	{
		audioPlayer->SetLoop(enable);
	}

	bool AudioSourceComponent::IsPlayingAudio() const
	{
		return audioPlayer->IsPlayingAudio();
	}

	bool AudioSourceComponent::IsLooping() const
	{
		return audioPlayer->IsLooping();
	}

	RmlUIDocumentComponent::RmlUIDocumentComponent()
	{
	}

	std::string RmlUIDocumentComponent::GetComponentType() const
	{
		return "RmlUIDocumentComponent";
	}

	std::string TransformScriptComponent::GetComponentType() const
	{
		return "TransformScript";
	}
}
