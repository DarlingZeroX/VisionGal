#include "Render/Renderer.h"

#include "Resource/Texture2D.h"
#include "Render/Material.h"
#include "Render/Sprite.h"
#include "Scene/Components.h"

#include "Graphics/OpenGL/Core.h"

namespace VisionGal
{
	SpriteRendererHandler::SpriteRendererHandler()
	{

	}

	void SpriteRendererHandler::Render(std::vector<GameActor*>& sprites, ICamera* camera)
	{
		for (auto& obj : sprites)
		{
			Render(obj, camera);
		}
	}
	void SpriteRendererHandler::Render(GameActor* actor, ICamera* camera)
	{
		TransformComponent* transform = actor->GetComponent<TransformComponent>();
		SpriteRendererComponent* spriteRenderer = actor->GetComponent<SpriteRendererComponent>();

		// �����ɫ͸������Ⱦ
		if (spriteRenderer->color.a == 0.f)
			return; 

		auto* tex = spriteRenderer->sprite->GetITexture();
		auto* program = spriteRenderer->material->GetShaderProgram();

		VGFX::UseProgram(program);
		VGFX::SetTexture(0, "texture1", tex);
		VGFX::SetUniformFloat4("color", spriteRenderer->color);
		VGFX::SetUniformInt2("flip", spriteRenderer->flip);
		VGFX::SetUniformMatrix4("model", transform->model);
		VGFX::SetUniformMatrix4("projection", camera->GetMatrix());
		VGFX::RenderMesh(spriteRenderer->sprite->GetMesh());
	}

	void FullScreenRendererHandler::Render(FullScreenRendererComponent* renderer)
	{
		VGFX::ITexture* tex = renderer->image->GetTexture();
		auto* program = renderer->shader;

		VGFX::UseProgram(program);
		VGFX::SetTexture(0,"texture1", tex);
		VGFX::RenderMesh(renderer->image->GetMesh());
	}
}
