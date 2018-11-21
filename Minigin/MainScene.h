#pragma once
#include "Scene.h"
#include "TextComponent.h"

namespace dae
{

	class MainScene final : public Scene
	{
	public:
		explicit MainScene();
		virtual ~MainScene() = default;

		void Initialize() override;
		void Update(GameContext gameContext) override;

		//delete copy ctr & assignment opr
		MainScene(const MainScene& rhs) = delete;
		MainScene(MainScene&& rhs) = delete;
		MainScene& operator=(const MainScene& rhs) = delete;
		MainScene& operator=(MainScene&& rhs) = delete;

	private:
		size_t m_CharacterHitCheckBoundary = 6;
		TextComponent* m_pFpsCounter = nullptr;
	};
}
