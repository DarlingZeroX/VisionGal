VS{
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    
    out vec2 TexCoord;
    
    void main() {
        TexCoord = aTexCoord;
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
}
PS{
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    
    uniform sampler2D renderTex;
    uniform sampler2D uiTex;
    
    void main() {
        vec4 renderResult = texture(renderTex, TexCoord);
        vec4 uiResult = texture(uiTex, TexCoord);

        //FragColor = renderResult * uiResult;
        //FragColor = mix(renderResult, uiResult, uiResult.a);

        // 计算最终颜色（考虑两个源的Alpha）
        vec3 finalRGB = uiResult.rgb * uiResult.a + 
                        renderResult.rgb * renderResult.a * (1.0 - uiResult.a);
        
        // 计算最终Alpha
        float finalAlpha = uiResult.a + renderResult.a * (1.0 - uiResult.a);
        
        // 输出最终颜色
        //FragColor = vec4(finalRGB / finalAlpha, finalAlpha);
        
        // 如果担心除零问题，可以添加安全检查
        FragColor = finalAlpha > 0.0 ? vec4(finalRGB / finalAlpha, finalAlpha) : vec4(0.0);
    }
}