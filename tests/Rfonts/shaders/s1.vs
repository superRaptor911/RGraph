#version 330 core
layout (location = 0) in vec2 vertex;
out vec2 TexCoords;

uniform mat4 proj;
uniform mat4 model;

void main()
{
    gl_Position = proj * model * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.xy;
}
