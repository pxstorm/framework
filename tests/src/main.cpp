#include <iostream>
#include "pxs/graphics/shader_builder.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    /* Graphic initialization */
    pxs::ShaderBuilder sb;
    sb.attach("../resources/shaders/basic.vs", pxs::Shader::Vertex);
    sb.attach("../resources/shaders/basic.fs", pxs::Shader::Fragment);
    pxs::Shader::ptr shader = sb.build();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}