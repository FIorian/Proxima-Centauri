#include "MiniginPCH.h"
#include "Ghost.h"
#include "Renderer.h"
#include "PickupManager.h"
#include <ctime>
#include "Utils.h"

dae::Ghost::Ghost(const Pos& pos, const Scale& scale, float velocity,
	Direction initDirection, bool playerControlled)
	:Character(pos, scale, velocity, initDirection),
	m_PlayerControlled(playerControlled)
{
	//texture 
	if (playerControlled)
	{
		dae::RenderComponent* texture = dae::Renderer::GetInstance().AddComponent("PCghost.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
	}
	else
	{
		dae::RenderComponent* texture = dae::Renderer::GetInstance().AddComponent("ghost.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
	}
}

void dae::Ghost::Update(const GameContext& gameContext)
{
	if (m_PlayerControlled)
	{
		Character::Update(gameContext);
		PickupManager::GetInstance().NavCheck(*this);
	}
	else
	{
		//pick random direction to go when hitting corner object
		//AI will rule the world
		srand(unsigned int(time(nullptr)));
		Character::Update(gameContext);

		PickupManager::GetInstance().NavCheck(*this);

		//timer
		m_Acctime += gameContext.deltaT;
		if (m_Acctime >= m_DirectionSwapCD)
		{
			m_Acctime = 0;
			int i = rand() % 4 + 1;
			this->SetRequestedDirection(static_cast<Direction>(i));
		}
	}
}
