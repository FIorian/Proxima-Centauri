#include "MiniginPCH.h"
#include "MainScene.h"
#include "TestObject.h"
#include "Renderer.h"
#include "PacMan.h"
#include "InputManager.h"
#include "Loader.h"
#include "Ghost.h"
#include "Utils.h"
#include "PickupManager.h"

dae::MainScene::MainScene()
	:dae::Scene("MainScene")
{
}

void dae::MainScene::Initialize()
{
	//fps counter
	m_pFpsCounter = Renderer::GetInstance().AddText("", Pos{ 746.f, 10.f });

	//background
	TestObject* backGroundObj = new TestObject();
	dae::RenderComponent* background =
		Renderer::GetInstance().AddComponent("level.jpg", 0.f, 0.f, 0.f, 736.f, 813.f,
			backGroundObj);
	backGroundObj->AddComponent(background, true);
	this->AddObject(backGroundObj);

	//main character
	dae::PacMan* pacman = new dae::PacMan(Pos{ 50.f, 360.f }, Scale{ 40.f, 40.f }, 100.0f);
	dae::InputManager::GetInstance().SetPacman(pacman);
	this->AddObject(pacman);

	//initialize and add ghosts
	dae::Ghost* ghost1 = new dae::Ghost(Pos{ 640.f, 200.f }, Scale{ 40.f, 40.f }, 100.f, 
		Direction::LEFT);
	this->AddObject(ghost1);

	//set second player if needed
	InputManager::GetInstance().SetGhost(ghost1);
	//InputManager::GetInstance().SetTwoPlayers(true);

	dae::Ghost* ghost2 = new dae::Ghost(Pos{ 60.f, 200.f }, Scale{ 40.f, 40.f }, 100.f, 
		Direction::RIGHT);
	this->AddObject(ghost2);

	dae::Ghost* ghost3 = new dae::Ghost(Pos{ 640.f, 600.f }, Scale{ 40.f, 40.f }, 100.f, 
		Direction::LEFT);
	this->AddObject(ghost3);

	dae::Ghost* ghost4 = new dae::Ghost(Pos{ 60.f, 600.f }, Scale{ 40.f, 40.f }, 100.f, 
		Direction::RIGHT);
	this->AddObject(ghost4);

	//level
	Loader::GetInstance().LoadLevel("Level.csv");

	//init
	Scene::Initialize(); 
}

void dae::MainScene::Update(GameContext gameContext)
{
	//fps counter
	if (m_pFpsCounter != nullptr)
	{
		m_pFpsCounter->SetText("FPS: " + std::to_string(int(1.f / gameContext.deltaT)));
		m_pFpsCounter->Update();
	}

	//update main scene
	Scene::Update(gameContext);

	//hit detections with ghosts
	for (size_t i = 2; i < m_CharacterHitCheckBoundary; i++)
	{
		if (dae::isOverlapping(((dae::Character*)m_Objects[i])->GetHitboxRect(), //ghosts
			((dae::Character*)m_Objects[1])->GetHitboxRect())) //pacman
		{
			//if packman is super remove ghost
			if (((dae::PacMan*)m_Objects[1])->GetIsSuper())
			{
				m_Objects[i]->RemoveRC();

				delete m_Objects[i];
				m_Objects[i] = nullptr;

				m_Objects.erase(m_Objects.begin() + i);
				m_CharacterHitCheckBoundary--;
				
				return;
			}

			//else reset game
			for (GameObject* go : m_Objects)
			{
				delete go;
				go = nullptr;
			}
			m_Objects.clear();
			Renderer::GetInstance().ClearRenderer();
			PickupManager::GetInstance().ClearPickups();

			Initialize();
		}
	}
}
