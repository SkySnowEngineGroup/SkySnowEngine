#include <stdlib.h>
#include <iostream>
#include "nw_renderpipeline.h"

class Triangle
{

};
//glfw callbacks
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//int main()
//{
//	glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    
//    GLFWwindow* window = glfwCreateWindow(800, 600, "NuwaTriangle", NULL, NULL);
//    if(window == NULL)
//    {
//        std::cout<< "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    gladLoadGL(glfwGetProcAddress);
//    glfwSwapInterval(1);
//    //register callbacks
//    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glViewport(0, 0, 800, 600);
//
//    while(!glfwWindowShouldClose(window))
//    {
//        //render 
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//	return 0;
//}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}