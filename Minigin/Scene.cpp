#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) 
	: m_Name{ name }
{
}

dae::Scene::~Scene()
{
	for (GameObject* go : m_Objects)
	{
		delete go;
		go = nullptr;
	}
	m_Objects.clear();
}

void dae::Scene::AddObject(GameObject* object)
{
	//add object to scene
	m_Objects.push_back(object);
}

void dae::Scene::Update(GameContext gameContext)
{
	//update game objects
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(gameContext);
	}
}

void dae::Scene::Initialize()
{
	//initialize all objects in scene
	for (GameObject* go : m_Objects)
	{
		go->Initialize();
	}
}

