VS{
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 projection;
    
    void main() {
        TexCoord = aTexCoord;
        gl_Position = projection * model * vec4(aPos, 1.0);
    }
}
PS{
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    
    uniform sampler2D texture1;
    uniform ivec2 flip;
    uniform vec4 color;
    
    void main() {
        vec2 coord = TexCoord;
        if(flip.x == 1)
            coord.x = 1 - coord.x;
        if(flip.y == 1)
            coord.y = 1 - coord.y;
        // 采样纹理颜色（包含纹理的Alpha值）
        vec4 texColor = texture(texture1, coord);
        
        // 将纹理颜色与顶点颜色相乘（包括Alpha值）
        vec4 finalColor = texColor * color;
        
        // 输出最终颜色（包含组合后的Alpha值）
        FragColor = finalColor;

        //FragColor = texture(texture1, coord);
    }
}
