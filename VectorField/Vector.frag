#version 330 core
out vec4 FragColor;
  
in float dist;  // Maybe Use Later
in vec4 finalPos;

void main()
{
    //FragColor = vec4(abs(finalPos.x/10.0f), abs(finalPos.y/10.0f), finalPos.z, 1.0f);
    FragColor = vec4(1.0f);
} 