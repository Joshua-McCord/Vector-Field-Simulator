#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 projection;
uniform mat4 model;
out float dist;
out vec4 finalPos;

void main()
{
    // note that we read the multiplication from right to left
    vec4 pos = projection * (model * vec4(aPos, 1.0));
    gl_Position = pos;
    dist = length(vec4(0.0f) - pos );
    finalPos = pos;
}