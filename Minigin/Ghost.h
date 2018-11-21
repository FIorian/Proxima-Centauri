#pragma once
#include "Character.h"

namespace dae
{
	class Ghost final : public Character
	{
	public:
		explicit Ghost(const Pos& pos, const Scale& scale, float velocity, 
			Direction initDirection, bool playerControlled = false);
		virtual ~Ghost() = default;

		void Initialize() override { Character::Initialize(); }
		void Update(const GameContext& gameContext) override;
		
		void Pickup(PickupType type) override { UNREFERENCED_PARAMETER(type); }

		void SetPlayerControlled(bool on)
		{
			m_PlayerControlled = on;
			if (m_RCidx >= 0)
			{
				if (on)
				{
					((dae::RenderComponent*) m_pComponents[m_RCidx])->SetTexture("PCghost.png");
				}
				else {
					((dae::RenderComponent*) m_pComponents[m_RCidx])->SetTexture("ghost.png");
				}
			}				
		}

		//delete copy ctr & assingment opr
		Ghost(const Ghost& rhs) = delete;
		Ghost(Ghost&& ths) = delete;
		Ghost& operator=(const Ghost& rhs) = delete;
		Ghost& operator=(Ghost&& rhs) = delete;

	private:
		float m_Acctime{ 0.f };
		float m_DirectionSwapCD{ 0.2f };

		bool m_PlayerControlled;
	};
}
