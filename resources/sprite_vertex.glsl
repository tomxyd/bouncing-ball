#version 330 core
layout (location = 0) in vec3 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(vertex, 1.0);
    TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}