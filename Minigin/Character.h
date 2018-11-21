#pragma once
#include "GameObject.h"
#include "Utils.h"

namespace dae
{
	//enum class PickupType;

	class Character : public dae::GameObject
	{
	public:
		explicit Character(const Pos& pos, const Scale& scale, float velocity,
			Direction initDirection);
		virtual ~Character() = default;

		virtual void Initialize();
		virtual void Update(const GameContext& gameContext);

		virtual void Pickup(PickupType type) = 0;

		void SetDirection() { m_currentDirection = m_RequestedDirection; }

		//accesors
		Rect GetHitboxRect() const;
		Rect GetDirectionHB() const;
		Direction GetCurrentDirection() const { return m_currentDirection; }
		Direction GetRequestedDirection() const { return m_RequestedDirection; }

		//mutators
		void SetCurrentDirection(Direction newDirection) { m_currentDirection = newDirection; }
		void SetRequestedDirection(Direction newDirection) { m_RequestedDirection = newDirection; }

		//delete copy ctr & assignment opr
		Character(const Character& rhs) = delete;
		Character(Character&& rhs) = delete;
		Character& operator=(const Character& rhs) = delete;
		Character& operator=(Character&& rhs) = delete;

	private:
		Direction m_currentDirection = Direction::RIGHT;
		Direction m_RequestedDirection = Direction::IDLE;
		float m_Velocity;
		int m_HBidx{ -1 };
		int m_DirHBidx{ -1 };
	};
}
