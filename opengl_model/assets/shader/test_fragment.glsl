#version 330 core

uniform sampler2D ourTexture;

out vec4 FragColor;
in vec2 TexCoord;

void main() {
    FragColor = texture(ourTexture, TexCoord);
}
