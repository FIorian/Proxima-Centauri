#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Character.h"

namespace dae
{
	class CrossingObject final : public GameObject
	{
	public:
		explicit CrossingObject(const Pos& pos, const Scale& scale,
			Direction restrictedDir1 = Direction::IDLE, 
			Direction restrictedDir2 = Direction::IDLE);
		virtual ~CrossingObject() = default;

		void Initialize() override {}
		void Update(const GameContext& gameContext) override { UNREFERENCED_PARAMETER(gameContext); }
		bool IsHit(Character& character);

		//delete copy ctr & assignment opr
		CrossingObject(const CrossingObject& rhs) = delete;
		CrossingObject(CrossingObject&& rhs) = delete;
		CrossingObject& operator=(const CrossingObject& rhs) = delete;
		CrossingObject& operator=(CrossingObject&& rhs) = delete;

	private:
		Direction m_RestrictedDir1;
		Direction m_RestrictedDir2;
		int m_HBidx{ -1 };
	};
}

