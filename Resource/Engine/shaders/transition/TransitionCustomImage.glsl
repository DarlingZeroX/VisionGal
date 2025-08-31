VS{
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTexCoord;
	
	out vec2 TexCoord;
	
	void main() {
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		TexCoord = aTexCoord;
	}
}
PS{
	#version 330 core
	in vec2 TexCoord;
	out vec4 FragColor;
		
	uniform sampler2D prevScene;	// 前一场景纹理
	uniform sampler2D nextScene;	// 后一场景纹理
	uniform sampler2D transition;	// 转场纹理
	uniform float progress;			// 转场进度（0.0~1.0）
		
	void main() {
		// 从转场纹理获取控制值
		float transitionValue = texture(transition, vec2(TexCoord.x, 1 - TexCoord.y)).r;
		
		// 根据转场值和进度决定混合比例
		float mixFactor = 1.0 - smoothstep(progress - 0.1, progress + 0.1, transitionValue);

		vec4 prev = texture(prevScene, TexCoord);
		vec4 next = texture(nextScene, TexCoord);

		FragColor = mix(prev, next, mixFactor);
	}
}