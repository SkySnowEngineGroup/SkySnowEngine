#include "Application.h"
namespace Nuwa
{
	namespace Engine
	{
		Application::Application(const char* name, const char* description)
			: m_Name(name)
			, m_Description(description)
		{

		}
		Application::~Application()
		{

		}

		int RunApplication(Application* app, int argc, const char* const* argv)
		{
			app->Init(argc,argv, DEFAUT_WADTH, DEFAUT_HEIGHT);

			while (app->Update())
			{
				//break;
			}
			return app->ShutDown();
		}
	}
}
