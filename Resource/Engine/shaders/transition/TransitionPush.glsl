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

	uniform sampler2D prevScene;    // 上一帧
	uniform sampler2D nextScene;    // 下一帧
	uniform float progress;    // 转场进度 [0.0 ~ 1.0]
	uniform vec2 direction;    // 推入方向 (±1,0) 或 (0,±1)

	void main()
	{
		vec2 uv = TexCoord;

		// 将 progress 投影到方向上
		vec2 offsetA = -direction * progress;        // A 往反方向推出
		vec2 offsetB = direction * (1.0 - progress); // B 从对应方向推入

		// 计算偏移后的 UV
		vec2 uvA = uv + offsetA;
		vec2 uvB = uv + offsetB;

		vec4 color = vec4(0.0);

		// 如果在范围内，采样 A
		if (uvA.x >= 0.0 && uvA.x <= 1.0 &&
			uvA.y >= 0.0 && uvA.y <= 1.0)
		{
			color = texture(prevScene, uvA);
		}

		// 如果在范围内，采样 B 覆盖 A
		if (uvB.x >= 0.0 && uvB.x <= 1.0 &&
			uvB.y >= 0.0 && uvB.y <= 1.0)
		{
			color = texture(nextScene, uvB);
		}

		FragColor = color;
	}

}