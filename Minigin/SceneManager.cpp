#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(GameContext gameContext)
{
	m_Scenes[m_ActiveScene]->Update(gameContext);
}

void dae::SceneManager::SetActiveScene(UINT sceneIdx)
{
	if (sceneIdx >= m_Scenes.size())
	{
		return;
	}
	m_ActiveScene = sceneIdx;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
}
