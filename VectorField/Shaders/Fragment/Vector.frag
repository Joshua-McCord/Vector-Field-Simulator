#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
  

void main()
{
    FragColor = vec4(ourColor, 1.0);
    //FragColor = vec4(0.8f, 0.3f, 0.196f, 1.0f);
} 