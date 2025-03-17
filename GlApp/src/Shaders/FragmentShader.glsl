#version 460 core

in vec3 ourColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 0.0);
}