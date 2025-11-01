#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out vec4 shadowFragPos;

uniform mat4 cam;
uniform mat4 transform;

void main()
{
  FragPos = vec3(transform * vec4(aPos, 1.0));
  Normal = abs(aNormal);
  TexCoord = vec2(aTexCoord.x, aTexCoord.y);

  gl_Position = cam * transform * vec4(aPos, 1.0);
}