#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out vec4 shadowFragPos;

uniform mat4 cameraMat;
uniform mat4 transform;

uniform mat4 shadowView;

void main()
{
    FragPos = vec3(transform * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(transform))) * aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    shadowFragPos = shadowView * vec4(FragPos, 1.0);

    gl_Position = cameraMat * transform * vec4(aPos, 1.0);
}