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
    
    uniform sampler2D texture1;
    
    void main() {
        FragColor = texture(texture1, TexCoord);
    }
}