#include "Render/Camera.h"
#include "HCore/include/Math/GLM/ext/matrix_clip_space.hpp"

namespace VisionGal
{
	//Letterbox2DCamera::Letterbox2DCamera()
	//{
	//	int width = VGBackend::Get()->GetWindow()->WindowWidth();
	//	int height = VGBackend::Get()->GetWindow()->WindowHeight();
    //
	//	OnScreenSizeChange(width, height);
	//}

	Letterbox2DCamera::Letterbox2DCamera(int width, int height)
	{
        OnViewportSizeChange(width, height);
	}

	const matrix4x4& Letterbox2DCamera::GetMatrix()
	{
		return m_Projection;
	}

    /**
	 * �������ö��
	 */
    //enum class AspectRatioPolicy {
    //    FitVisible,       // ���ֿɼ��ԣ������кڱߣ�
    //    FillVisible,      // �����Ļ�����ܲü���Ե��
    //    Stretch,          // ���죨���Կ�߱ȣ�
    //    ExpandBackground  // ��չ��������������Ļ>��ƣ�
    //};

	void Letterbox2DCamera::OnViewportSizeChange(int width, int height)
	{
		m_Width = width;
		m_Height = height;

		//m_Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

        float designWidth = 1920;
        float designHeight = 1080;
        float actualWidth = m_Width;
        float actualHeight = m_Height;

        // ������ƿ�߱���ʵ�ʿ�߱�
        float designAspect = designWidth / designHeight;
        float actualAspect = actualWidth / actualHeight;
        
        // ��ʼ�߼����귶Χ������Ʒֱ���Ϊ��׼��
       m_Left = -designWidth / 2.0f;
       m_Right = designWidth / 2.0f;
       m_Bottom = -designHeight / 2.0f;
       m_Top = designHeight / 2.0f;

        bool screen_small = (designWidth >= actualWidth) && (designHeight >= actualHeight);

        if (actualAspect > designAspect) {
            // ʵ����Ļ�����̶���ֱ��Χ������ˮƽ��Χ
            float scale = designAspect / actualAspect;

            // ��ʾ����ĻС���߼��ߴ�Ҫ��Ϊ����
            if (screen_small)
                scale = 1.0f / scale;

            m_Left *= scale;
            m_Right *= scale;
        }
        else {
            // ʵ����Ļ���ߣ��̶�ˮƽ��Χ�����Ŵ�ֱ��Χ
            float scale = actualAspect / designAspect;

            // ��ʾ����ĻС���߼��ߴ�Ҫ��Ϊ����
            if (screen_small)
                scale = 1.0f / scale;

            m_Bottom *= scale;
            m_Top *= scale;
        }

        // ��������ͶӰ����
        m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -10000.0f, 10000.0f);
	}
}
