#version 330 core

uniform sampler2D wallTexture;
uniform sampler2D faceTexture;

out vec4 FragColor;
in vec2 TexCoord;

void main() {
    FragColor = mix(texture(wallTexture, TexCoord), texture(faceTexture, TexCoord),0.2);
}
