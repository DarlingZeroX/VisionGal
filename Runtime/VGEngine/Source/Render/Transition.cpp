#include "Render/Transition.h"
#include "Engine/Manager.h"
#include "Render/Renderer.h"
#include "Graphics/Interface/VGFX.h"

namespace VisionGal
{
	SceneTransitionBase::SceneTransitionBase()
	{
		m_Layer = "Screen";
		m_FullQuad = FullScreenQuad::Create();
	}

	void SceneTransitionBase::Start()
	{
		m_IsBegin = true;
		m_Helper = CreateRef<TransitionHelper>(m_Duration);
	}

	void SceneTransitionBase::Finish()
	{
		m_IsBegin = false;
		m_Helper->Finish();
	}

	bool SceneTransitionBase::IsFinish()
	{
		return m_Helper->IsFinished();
	}

	float SceneTransitionBase::GetProgress() const noexcept
	{
		return m_Helper->Progress();
	}

	void SceneTransitionBase::Transition()
	{
		//ImGui::ShowDemoWindow();

		if (m_FramePrev == nullptr)
			return;

		if (m_FrameNext == nullptr)
			return;

		if (m_IsBegin == false)
			return;

		if (m_Helper->IsFinished())
		{
			Finish();
			return;
		}

		m_Helper->Update();

		// 转场渲染
		OnRenderTransition();

		VGFX::RenderMesh(m_FullQuad->GetMesh());

		// 恢复到纹理单元0（关键！）
		VGFX::BindTexture(0);
	}

	void SceneTransitionBase::SetPrevFrame(VGFX::ITexture* texture)
	{
		m_FramePrev = texture;
	}

	void SceneTransitionBase::SetNextFrame(VGFX::ITexture* texture)
	{
		m_FrameNext = texture;
	}

	void SceneTransitionBase::SetLayer(const String& layer)
	{
		m_Layer = layer;
	}

	const String& SceneTransitionBase::GetLayer()
	{
		return m_Layer;
	}

	void SceneTransitionBase::SetDuration(float duration)
	{
		m_Duration = std::max(duration, 0.f);
	}

	VGFX::ITexture* SceneTransitionBase::GetPrevFrame()
	{
		return m_FramePrev;
	}

	VGFX::ITexture* SceneTransitionBase::GetNextFrame()
	{
		return m_FrameNext; 
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////	DissolveSceneTransition
	/////////////////////////////////////////////////////////////////////////////////////

	DissolveSceneTransition::DissolveSceneTransition()
	{
		m_ShaderProgram = ShaderManager::Get()->GetBuiltinProgram("SceneFade");
	}

	void DissolveSceneTransition::OnRenderTransition()
	{
		VGFX::UseProgram(m_ShaderProgram);
		VGFX::SetUniformInt("fadeType", 0); // Dissolve
		VGFX::SetTexture(0, "prevScene", GetPrevFrame());
		VGFX::SetTexture(1, "nextScene", GetNextFrame());
		VGFX::SetUniformFloat("progress", GetProgress());
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////	FadeSceneTransition
	/////////////////////////////////////////////////////////////////////////////////////

	FadeSceneTransition::FadeSceneTransition(FadeType type)
	{
		m_FadeType = type;
		m_ShaderProgram = ShaderManager::Get()->GetBuiltinProgram("SceneFade");
	}
	void FadeSceneTransition::OnRenderTransition()
	{
		VGFX::UseProgram(m_ShaderProgram);

		switch (m_FadeType)
		{
		case FadeType::FadeIn:
			VGFX::SetUniformInt("fadeType", 1); // Fade In
			break;
		case FadeType::FadeOut:
			VGFX::SetUniformInt("fadeType", 2); // Fade Out
			break;
		}

		VGFX::SetTexture(0, "prevScene", GetPrevFrame());
		VGFX::SetTexture(1, "nextScene", GetNextFrame());

		VGFX::SetUniformFloat("progress", GetProgress());
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////	CustomImageSceneTransition
	/////////////////////////////////////////////////////////////////////////////////////

	Ref<OpenGL::ShaderProgram> CustomImageSceneTransition::s_ShaderProgram = nullptr;

	CustomImageSceneTransition::CustomImageSceneTransition()
	{

	}

	void CustomImageSceneTransition::CompileShader()
	{
		if (s_ShaderProgram != nullptr)
			return;

		// 顶点着色器
		const char* vertexShader = R"(
		        #version 330 core
		        layout (location = 0) in vec3 aPos;
		        layout (location = 1) in vec2 aTexCoord;
		        
		        out vec2 TexCoord;
		        
		        void main() {
		            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		            TexCoord = aTexCoord;
		        }
		    )";

		// 片段着色器
		const char* fragmentShader = R"(
			    #version 330 core
			    in vec2 TexCoord;
			    out vec4 FragColor;
			        
			    uniform sampler2D prevScene;	// 前一场景纹理
				uniform sampler2D nextScene;	// 后一场景纹理
				uniform sampler2D transition;	// 转场纹理
				uniform float progress;			// 转场进度（0.0~1.0）
			        
			    void main() {
				    // 从转场纹理获取控制值
				    float transitionValue = texture(transition, TexCoord).r;
				    
				    // 根据转场值和进度决定混合比例
				    float mixFactor = 1.0f - smoothstep(progress - 0.1, progress + 0.1, transitionValue);

			        vec4 prev = texture(prevScene, TexCoord);
					vec4 next = texture(nextScene, TexCoord);

					FragColor = mix(prev, next, mixFactor);
			    }
		    )";

		auto vs = OpenGL::CreateShader(GL_VERTEX_SHADER, vertexShader);
		auto ps = OpenGL::CreateShader(GL_FRAGMENT_SHADER, fragmentShader);


		std::vector<OpenGL::Shader*> shaders;
		shaders.push_back(vs.get());
		shaders.push_back(ps.get());

		s_ShaderProgram = OpenGL::ShaderProgram::Create(shaders);
	}

	void CustomImageSceneTransition::OnRenderTransition()
	{
		//s_ShaderProgram->Bind();
		//
		//VGFX::SetTexture(0, GetPrevFrame());
		//s_ShaderProgram->SetInt("prevScene", 0);
		//
		//VGFX::SetTexture(1, GetNextFrame());
		//s_ShaderProgram->SetInt("nextScene", 1);
		//
		//VGFX::SetTexture(1, m_TransitionTexture->GetITexture().get());
		//s_ShaderProgram->SetInt("transition", 2);
		//
		//s_ShaderProgram->SetFloat("progress", GetProgress());
	}

	void CustomImageSceneTransition::SetTransitionImage(const Ref<Texture2D>& texture)
	{
		m_TransitionTexture = texture;
	}
}
