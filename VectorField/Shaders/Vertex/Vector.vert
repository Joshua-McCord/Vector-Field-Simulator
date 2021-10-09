#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1


uniform mat4 projection;
uniform mat4 model;

out vec3 ourColor;

void main()
{
    // note that we read the multiplication from right to left
    vec4 pos = projection * (model * vec4(aPos, 1.0));
    gl_Position = pos;
    ourColor = aColor;
}