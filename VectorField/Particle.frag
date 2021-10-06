#version 330 core
out vec4 FragColor;
  
in float dist;  // Maybe Use Later
in vec4 finalPos;

void main()
{
    FragColor = vec4(0.8f, 0.3f, 0.196f, 1.0f);
} 