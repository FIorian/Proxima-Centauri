#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);
		void AddScene(std::shared_ptr<Scene> scene);

		void Update(GameContext gameContext);
		void SetActiveScene(UINT sceneIdx);

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		UINT m_ActiveScene{};
	};

}
