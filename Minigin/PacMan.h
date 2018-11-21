#pragma once
#include "Character.h"

namespace dae
{
	class PacMan final : public dae::Character
	{
	public:
		explicit PacMan(const Pos& pos, const Scale& scale, float velocity);
		virtual ~PacMan() = default;

		void Initialize() override;
		void Update(const GameContext& gameContext) override;

		void Pickup(PickupType type) override;

		bool GetIsSuper() const { return m_IsSuper; }

		//delete copy ctr & assingment opr
		PacMan(const PacMan& rhs) = delete;
		PacMan(PacMan&& rhs) = delete;
		PacMan& operator=(const PacMan& rhs) = delete;
		PacMan& operator=(PacMan&& rhs) = delete;

	private:
		//datamembers
		//int m_ScoreIdx{ -1 };
		int m_Score{ 0 };

		bool m_IsSuper{ false };
		float m_AccTime{ 0.f };
		float m_SuperCD{ 5.f };
	};
}
