#include "Render/Effect.h"
#include "Graphics/OpenGL/Texture2D.h"

namespace VisionGal
{
	void FullScreenBlackEdge::SetWindowSize(int2 size)
	{
		WindowSize = size;
	}

	void FullScreenBlackEdge::SetImageSize(int2 size)
	{
		ImageSize = size;
	}

	void FullScreenBlackEdge::Calculate()
	{
		// ��ȡ���ڳߴ�
		int windowWidth, windowHeight;
		windowWidth = WindowSize.x;
		windowHeight = WindowSize.y;

		// �������ű��������ֿ�߱�
		float scaleX = (float)windowWidth / ImageSize.x;
		float scaleY = (float)windowHeight / ImageSize.y;
		float scale = std::min(scaleX, scaleY);

		// ������ʾ����ĳߴ��λ��
		int displayWidth = static_cast<int>(ImageSize.x * scale);
		int displayHeight = static_cast<int>(ImageSize.y * scale);
		int x = (windowWidth - displayWidth) / 2;
		int y = (windowHeight - displayHeight) / 2;

		// ����任��Ķ���λ��
		float xOffset = (float)x / windowWidth;
		float yOffset = (float)y / windowHeight;

		//	vertices[0] = 1.0f - xOffset * 2.0f; vertices[1] = 1.0f - yOffset * 2.0f; // ����
		//	vertices[5] = 1.0f - xOffset * 2.0f; vertices[6] = -1.0f + yOffset * 2.0f; // ����
		//	vertices[10] = -1.0f + xOffset * 2.0f; vertices[11] = -1.0f + yOffset * 2.0f; // ����
		//	vertices[15] = -1.0f + xOffset * 2.0f; vertices[16] = 1.0f - yOffset * 2.0f; // ����


		RightTop = { 1.0f - xOffset * 2.0f, 1.0f - yOffset * 2.0f };		// ����
		RightBottom = { 1.0f - xOffset * 2.0f, -1.0f + yOffset * 2.0f };	// ����
		LeftBottom = { -1.0f + xOffset * 2.0f, -1.0f + yOffset * 2.0f };	// ����
		LeftTop = { -1.0f + xOffset * 2.0f, 1.0f - yOffset * 2.0f };		// ����
	}

	void FullScreenBlackEdge::ApplyEffect(ISprite* sprite)
	{
		//auto* spritegl = sprite->GetSprite();
		//OpenGL::Texture2D* texgl = dynamic_cast<OpenGL::Texture2D*>(sprite->GetITexture()->GetITexture().get());

		//WindowSize = { VGBackend::Get()->GetWindow()->WindowWidth(), VGBackend::Get()->GetWindow()->WindowHeight() };
		//ImageSize = { 1.f , texgl->Height() };
		Calculate();

		//spritegl->SetPosition(RightTop, RightBottom, LeftBottom, LeftTop);
	}
}