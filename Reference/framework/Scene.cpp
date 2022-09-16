#include "Scene.h"
#include <iostream>
#include "gl_BackEnd.h"
#include "Graphics.h"
#include "script_common.h"
#include <sstream>

Scene::Scene() :
graphics(NULL),
CurrentCamera(NULL),
focused(1),
enter(false),
tempCounter(0.f)
{
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < entities.size(); ++i)
	{
		if (entities[i] != NULL)
		{
			delete entities[i];
			entities[i] = NULL;
		}
	}

	if (graphics != NULL)
	{
		delete graphics;
		graphics = NULL;
	}
	CurrentCamera = NULL;
}

void Scene::Init(void)
{
	graphics = new Graphics();
	graphics->Init();

	Entity* floor = new Entity();
	floor->AddComponent<MeshFilter>()->Set(Asset.GetModel("QUAD"));
	floor->AddComponent<MeshRenderer>();
	floor->transform->SetScale(Vector3(20, 20, 20));
	floor->transform->SetPosition(Vector3(0, -1.f, 0));
	floor->transform->SetRotation(Quaternion(-90, Vector3(0, 1, 0)));
	floor->transform->Rotate(Quaternion(-90, Vector3(1, 0, 0)));
	floor->AddComponent<Material>()->SetManualDiffuse(Asset.GetTexture("BRICKWALL"));
	floor->GetComponent<Material>()->SetManualNormal(Asset.GetTexture("BRICKWALL_NORMAL"));
	floor->GetComponent<Material>()->tessel = 10;
	entities.push_back(floor);

	Entity* brickwall = new Entity();
	brickwall->AddComponent<MeshFilter>()->Set(Asset.GetModel("QUAD"));
	brickwall->AddComponent<MeshRenderer>();
	brickwall->transform->SetScale(Vector3(1, 1, 1));
	brickwall->transform->SetPosition(Vector3(0, 1.f, 10));
	brickwall->transform->SetRotation(Quaternion(-180, Vector3(0, 1, 0)));
	//brickwall->transform->Rotate(Quaternion(-90, Vector3(1, 0, 0)));
	brickwall->AddComponent<Material>()->SetManualDiffuse(Asset.GetTexture("BRICK2"));
	brickwall->GetComponent<Material>()->SetManualNormal(Asset.GetTexture("BRICK2_NORMAL"));
	brickwall->GetComponent<Material>()->SetManualDisp(Asset.GetTexture("BRICK2_DISP"));
	brickwall->GetComponent<Material>()->tessel = 1;
	entities.push_back(brickwall);

	for (int i = 0; i < 1; ++i)
	{
		Entity* ent = new Entity();
		ent->AddComponent<MeshFilter>()->Set(Asset.GetModel("NANOSUIT"));
		ent->AddComponent<MeshRenderer>();
		ent->transform->SetScale(Vector3(1, 1, 1));
		ent->transform->SetPosition(Vector3(0, 0, 0));
		ent->transform->SetRotation(Quaternion(-90, Vector3(1, 0, 0)));
		ent->AddComponent<Material>()->SetManualColor(Vector3(0.95f, 0.95f, 0.95f));
		entities.push_back(ent);
	}

	/*for (int i = 1; i <= 14; ++i)
	{
		std::ostringstream modelName;
		modelName << "TREE" << i;
		Entity* ent = new Entity();
		ent->AddComponent<MeshFilter>()->Set(Asset.GetModel(modelName.str()));
		ent->AddComponent<MeshRenderer>();
		ent->transform->SetScale(Vector3(1, 1, 1));
		ent->transform->SetPosition(Vector3(-10, -1, -(i * 2) + 7));
		entities.push_back(ent);
	}*/

	for (int i = 0; i < 200; ++i)
	{
		Entity* cube = new Entity();
		cube->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
		cube->AddComponent<MeshRenderer>();
		cube->transform->SetScale(Vector3(0.1f, 0.1f, 0.1f));
		cube->transform->SetPosition(Vector3(Math::RandFloatMinMax(-20, 20), Math::RandFloatMinMax(10, 30), Math::RandFloatMinMax(-20, 20)));
		cube->AddComponent<Material>()->SetManualColor(Vector3(Math::RandFloatMinMax(0, 1), Math::RandFloatMinMax(0, 1), Math::RandFloatMinMax(0, 1)));
		entities.push_back(cube);
		testEntities.push_back(cube);
	}

	Entity* cube = new Entity();
	cube->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
	cube->AddComponent<MeshRenderer>();
	cube->transform->SetScale(Vector3(1.f, 1.f, 1.f));
	cube->transform->SetPosition(Vector3(0.f, 0.0f, 0.f));
	cube->AddComponent<Material>()->SetManualColor(Vector3(1, 1, 1));
	entities.push_back(cube);

	Entity* cube2 = new Entity();
	cube2->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
	cube2->AddComponent<MeshRenderer>();
	cube2->transform->SetScale(Vector3(1.f, 1.f, 1.f));
	cube2->transform->SetPosition(Vector3(0.f, 0.0f, 5.f));
	cube2->AddComponent<Material>()->SetManualColor(Vector3(0, 0, 1));
	entities.push_back(cube2);

	Entity* ent = new Entity();
	ent->AddComponent<MeshFilter>()->Set(Asset.GetModel("BOULDER"));
	ent->AddComponent<MeshRenderer>();
	ent->transform->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	ent->transform->SetPosition(Vector3(-5.f, 0.f, 8.f));
	//ent->transform->SetRotation(Quaternion(-90, Vector3(1, 0, 0)));
	ent->AddComponent<Material>()->SetManualDiffuse(Asset.GetTexture("BOULDER"));
	ent->GetComponent<Material>()->SetManualNormal(Asset.GetTexture("BOULDER_NORMAL"));
	entities.push_back(ent);

	Entity* ent2 = new Entity();
	ent2->AddComponent<MeshFilter>()->Set(Asset.GetModel("BARREL"));
	ent2->AddComponent<MeshRenderer>();
	ent2->transform->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	ent2->transform->SetPosition(Vector3(-5.f, 0.f, 3.f));
	//ent2->transform->SetRotation(Quaternion(45, Vector3(1, 0, 0)));
	ent2->AddComponent<Material>()->SetManualDiffuse(Asset.GetTexture("BARREL"));
	ent2->GetComponent<Material>()->SetManualNormal(Asset.GetTexture("BARREL_NORMAL"));
	//ent2->GetComponent<Material>()->SetManualSpec(Asset.GetTexture("BARREL_SPECULAR"));
	entities.push_back(ent2);

	Entity* ent3 = new Entity();
	ent3->AddComponent<MeshFilter>()->Set(Asset.GetModel("CRYSTAL"));
	ent3->AddComponent<MeshRenderer>();
	ent3->transform->SetScale(Vector3(0.05f, 0.05f, 0.05f));
	ent3->transform->SetPosition(Vector3(-5.f, -1.f, -3.f));
	ent3->transform->SetRotation(Quaternion(90, Vector3(1, 0, 0)));
	ent3->AddComponent<Material>()->SetManualColor(Vector3(1, 0, 0));
	//ent3->GetComponent<Material>()->SetManualNormal(Asset.GetTexture("CRYSTAL"));
	entities.push_back(ent3);

	// Camera
	Entity* camera = new Entity();
	camera->AddComponent<FirstPersonCamera>()->CameraInit(Vector3(-30, 1, -5), Vector3(1, 0, 0), Vector3(0, 1, 0));
	entities.push_back(camera);
	CurrentCamera = (camera->GetComponent<FirstPersonCamera>());

	// Directional Light
	Entity* dLightObj = new Entity();
	dLightObj->transform->SetPosition(Vector3(-20.0f, 20.0f, -20.0f));
	dLightObj->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
	//dLightObj->GetComponent<Material>()->SetDiffuse(Asset.GetTexture("WHITE"));
	//dLightObj->GetComponent<Material>()->lighting = false;
	dLightObj->AddComponent<DirectionLight>()->Set(Vector3(0, 0, 0), Vector3(1, 1, 1), 0.05f, 1.f);
	entities.push_back(dLightObj);

	Entity* pLightObj = new Entity();
	pLightObj->transform->SetPosition(Vector3(-5.f, 1.f, -10.f));
	//pLightObj->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
	//pLightObj->GetComponent<Material>()->color = Vector3(1, 0, 1);
	//pLightObj->GetComponent<Material>()->lighting = false;
	pLightObj->AddComponent<PointLight>()->Set(Vector3(1, 0, 0), 0.05f, 5.f);
	//pLightObj->AddComponent<MeshRenderer>();
	entities.push_back(pLightObj);

	Entity* pLightObj2 = new Entity();
	pLightObj2->transform->SetPosition(Vector3(0.f, 1.f, 10.f));
	//pLightObj2->AddComponent<MeshFilter>()->Set(Asset.GetModel("CUBE"));
	//pLightObj2->GetComponent<Material>()->color = Vector3(1, 0, 1);
	//pLightObj2->GetComponent<Material>()->lighting = false;
	pLightObj2->AddComponent<PointLight>()->Set(Vector3(1, 1, 1), 0.2f, 2.f);
	//pLightObj2->AddComponent<MeshRenderer>();
	entities.push_back(pLightObj2);
}

void Scene::Run(double dt)
{
	gl_BackEnd* handle = gl_BackEnd::getInstance();

	Update(dt);

	Render();

	handle->GLSwapBuffers();
}

void Scene::Update(double dt)
{
	/*for (int i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->remove)
		{
			delete entities[i];
			entities[i] = NULL;
			--i;
			continue;
		}
	}*/
	for (int i = 0; i < testEntities.size(); ++i)
	{
		testEntities[i]->transform->Translate(Vector3(0, -dt, 0));
		if (testEntities[i]->transform->worldposition.y < 0)
		{
			testEntities[i]->GetComponent<MeshRenderer>()->Deactivate();
		}
	}
}

void Scene::Render(void)
{
	graphics->Render(CurrentCamera, entities);
}

void Scene::KeyboardCB(KEY Key, KEY_STATE action)
{
	Input.Update(Key, action);

	if (Key == KEY_ESCAPE)
	{
		exit = true;
		Debug.Log("Exit");
	}

	if (action == KEY_STATE_PRESS)
	{
		/*if (Key == KEY_Q)
		{
			delete entities[0];
			entities.erase(entities.begin());
		}*/

		if (Key == KEY_1)
		{
			if (graphics->graphicSettings.ssao)
			{
				graphics->graphicSettings.ssao = false;
			}
			else
			{
				graphics->graphicSettings.ssao = true;
			}
		}

		if (Key == KEY_2)
		{
			if (graphics->graphicSettings.shadow)
			{
				graphics->graphicSettings.shadow = false;
			}
			else
			{
				graphics->graphicSettings.shadow = true;
			}
		}

		if (Key == KEY_3)
		{
			if (graphics->graphicSettings.bloom)
			{
				graphics->graphicSettings.bloom = false;
			}
			else
			{
				graphics->graphicSettings.bloom = true;
			}
		}

		if (Key == KEY_4)
		{
			if (graphics->graphicSettings.directionalLight)
			{
				graphics->graphicSettings.directionalLight = false;
			}
			else
			{
				graphics->graphicSettings.directionalLight = true;
			}
		}

		if (Key == KEY_Q)
		{
			graphics->graphicSettings.gamma -= 0.1f;
		}

		if (Key == KEY_E)
		{
			graphics->graphicSettings.gamma += 0.1f;
		}
	}
}

void Scene::MouseCursorCB(double x, double y)
{
	//std::cout << x << " " << y << std::endl;
	if (focused && !enter)
	{
		CurrentCamera->onMouse(x, y);
	}
}

void Scene::MouseCursorEnterCB(bool enter)
{
	this->enter = enter;
	CurrentCamera->LastMousePosUpdate(App.WindowWidth() * 0.5, App.WindowHeight() * 0.5);
	//CurrentCamera->onMouse(App.WindowWidth() * 0., App.WindowHeight() * 0.5);
	//std::cout << "a" << App.WindowWidth() * 0.5f << std::endl;
}

void Scene::WindowFocusCB(int focused)
{
	this->focused = focused;
}