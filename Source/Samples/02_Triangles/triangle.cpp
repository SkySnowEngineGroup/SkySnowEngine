//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "Application.h"
#include "LogAssert.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
using namespace SkySnow;
class Triangle : public SkySnow::Application
{
public:
	Triangle(const char* name, const char* description)
		: Application(name, description)
        , _Scene(nullptr)
	{
	}
	~Triangle()
	{
        Delete_Object(_Scene);
	}

	bool Init(int32_t argc, const char* const* _argv, uint32_t width, uint32_t height)
	{
        _Scene = GetSceneManager().CreateScene("Test");
        TransformComponent* rootTrans = _Scene->SetupRootTransform();

		GameObject* go = _Scene->AddRootToScene();

//        CameraComponent* cameraCom = go->AddComponent<CameraComponent>();
        TransformComponent* transCom = go->AddComponent<TransformComponent>();
        RenderComponent* renderCom = go->AddComponent<RenderComponent>();

        _Scene->SetEnable(true);
		return true;
	}

private:
    Scene* _Scene;
};

SkySnow_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&MacOS."
);
