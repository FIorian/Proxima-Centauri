#pragma once
#include "Component.h"

namespace dae
{
	class ScoreComponent final : public Component
	{
	public:
		explicit ScoreComponent() = default;
		virtual ~ScoreComponent() = default;

		int AddScore(int score) { return (m_Score += score); }

		//accesors
		int GetScore() const { return m_Score; }

		//delete copy ctr & assignment opr
		ScoreComponent(const ScoreComponent& rhs) = delete;
		ScoreComponent(ScoreComponent&& rhs) = delete;
		ScoreComponent& operator=(const ScoreComponent& rhs) = delete;
		ScoreComponent& operator=(ScoreComponent&& rhs) = delete;

	private:
		//Datamembers
		int m_Score = 0;
	};
}

