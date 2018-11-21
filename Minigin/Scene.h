#pragma once
#include "SceneManager.h"
#include "GameObject.h"
//#include "RenderComponent.h"
//#include "Renderer.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);

	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();

		virtual void AddObject(GameObject* object);

		virtual void Update(GameContext gameContext);
		virtual void Initialize();

		//delete copy ctr & assignment opr
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		//public datamember
		std::vector <GameObject*> m_Objects{};

	private: 
		std::string m_Name{};

		static unsigned int idCounter; 
	};

}
