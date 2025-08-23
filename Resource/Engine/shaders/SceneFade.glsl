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
    uniform float progress;			// 转场进度（0.0~1.0）
    uniform int fadeType;    

    void main() {
        vec4 prev = texture(prevScene, TexCoord);
        vec4 next = texture(nextScene, TexCoord);

        // 淡入淡出
        if(fadeType == 0)
        {

        }
        // 淡入
        else if(fadeType == 1)
        {
            prev = vec4(0.0, 0.0, 0.0, 1.0);
        }
        // 淡出
        else if(fadeType == 2)
        {
            next = vec4(0.0, 0.0, 0.0, 1.0);
        }

        FragColor = mix(prev, next, progress);
    }
}