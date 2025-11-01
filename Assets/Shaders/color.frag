#version 330 core

out vec4 fragColor;

in vec3 Normal;
in vec3 FragPos;


void main() {
    fragColor = vec4(Normal, 1);

}