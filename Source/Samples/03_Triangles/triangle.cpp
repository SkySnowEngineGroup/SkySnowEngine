#include <stdlib.h>
#include <iostream>
#include "nw_renderpipeline.h"
#include "Application.h"
//glfw callbacks
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
class Triangle : public Nuwa::Engine::Application
{
public:
	Triangle(const char* name, const char* description)
		: Application(name, description)
	{

	}

	void Init(int32_t argc, const char* const* _argv, uint32_t width, uint32_t height)
	{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
        m_Window = glfwCreateWindow(800, 600, "NuwaTriangle", NULL, NULL);
        if(m_Window == NULL)
        {
            std::cout<< "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return ;
        }
        glfwMakeContextCurrent(m_Window);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);
        //register callbacks
        //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glViewport(0, 0, 800, 600);
	}
	int ShutDown()
	{
        glfwTerminate();
		return 0;
	}
	bool Update()
	{
        processInput(m_Window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glfwSwapBuffers(m_Window);
        glfwPollEvents();
		return !glfwWindowShouldClose(m_Window);
	}
    void processInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
private:
    GLFWwindow* m_Window;
};

NUWA_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&IOS."
);
