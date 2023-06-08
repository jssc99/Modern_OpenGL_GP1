#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 fragPos;
out vec3 normal;

uniform mat4 model;
uniform mat4 VP;

void main()
{
    fragPos = vec3(model * vec4(aPos, 1.f));
    normal = mat3(transpose(inverse(model))) * aNormal;   
    texCoord = aTexCoord;

	gl_Position = VP * vec4(fragPos, 1.f);
}