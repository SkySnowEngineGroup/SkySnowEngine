//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include <stdlib.h>
#include <iostream>
#include "nw_renderpipeline.h"
#include "Application.h"
#include "LogAssert.h"
#include "OSPlatform.h"
#include "Thread.h"
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
        , m_TestThread(nullptr)
        , m_TestThread_quit(false)
	{
        NUWALOGI("Application is name:%s", name);
        NUWALOGI("Application description info:%s", description);
	}

    static void* TriangleThreadTest(void* data)
    {
        Triangle* worker = (Triangle*)data;
        worker->Run();
        return nullptr;
    }

    void Run()
    {
        while (!m_TestThread_quit)
        {
            NUWALOGI("PThread is Running.");
        }
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
        NUWALOGI("Info LogAssert width:%d", width);
        NUWAWARNING("Warning LogAssert width:%d", width);
        NUWAERROR("Error LogAssert width:%d", width);

        m_TestThread = new Nuwa::Thread();
        m_TestThread->SetName("Test_Thread.");
        m_TestThread->Run(TriangleThreadTest,this);

        if (m_TestThread)
        {
            m_TestThread_quit = true;
            m_TestThread->Stop();
            //delete m_TestThread;
            //m_TestThread = nullptr;
        }
	}
	int ShutDown()
	{
        NUWALOGI("Application ShutDown.");
        glfwTerminate();
 
		return 0;
	}
	bool Update()
	{
        processInput(m_Window);
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        GRI->GRIClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    Nuwa::Thread* m_TestThread;
    bool m_TestThread_quit;
};

NUWA_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&MacOS."
);
