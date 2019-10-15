#version 330 core

out vec4 FragColor;

in vec3 color;

void main() {
    FragColor = vec4(0.8, 0.5, 0.2, 1.0);
    FragColor = vec4(color, 1.0);
}
