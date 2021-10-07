#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Simulator.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

static void mouse_callback(GLFWwindow* window, int button, int action, int mods);

Simulator Sim(1000, 1000);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Research Project", NULL, NULL);
    if (window == NULL) {
        std::cout << "Window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Failed" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1000, 1000);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    Sim.init();


    while (!glfwWindowShouldClose(window)) {


        // check and call events and swap the buffers
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Process Input
        Sim.ProcessInput(deltaTime);

        // Update Simulation
        Sim.Update(deltaTime);


        // Render Simulation
        Sim.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Sim.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Sim.Keys[key] = false;
    }
}


static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);

        Sim.ProcessMouseInput(x, y);
    }
}