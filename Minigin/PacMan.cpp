#include "MiniginPCH.h"
#include "PacMan.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "PickupManager.h"
#include "ScoreComponent.h"
#include "ResourceManager.h"

dae::PacMan::PacMan(const Pos& pos, const Scale& scale, float velocity)
	:Character(pos, scale, velocity, Direction::RIGHT)
{
	//texture
	dae::RenderComponent* texture = dae::Renderer::GetInstance().AddComponent("PacMan.png",
		m_Transform.GetPos(), m_Transform.GetScale(), this);

	this->AddComponent(texture, true);

	//text
	TextComponent* text = Renderer::GetInstance().AddText("Score: " + std::to_string(m_Score),
		Pos{ 746.f, 100.f });

	this->AddComponent(text);
	m_TextIdx = this->GetComponentVectorSize() - 1;
}

void dae::PacMan::Initialize()
{
	Character::Initialize();

	((TextComponent*)m_pComponents[m_TextIdx])->Update();
}

void dae::PacMan::Update(const GameContext & gameContext)
{
	Character::Update(gameContext);

	PickupManager::GetInstance().HitCheck(*this);
	PickupManager::GetInstance().NavCheck(*this);

	if (m_IsSuper)
	{
		m_AccTime += gameContext.deltaT;
		if (m_AccTime >= m_SuperCD)
		{
			m_AccTime = 0;
			m_IsSuper = false;
		}
	}
}

void dae::PacMan::Pickup(PickupType type)
{
	switch (type)
	{
	case PickupType::Undefined:
		break;
	case PickupType::Candy:
	{
		if (m_TextIdx >= 0)
		{	
			m_Score += 10;
			((TextComponent*)m_pComponents[m_TextIdx])->SetText("Score: " +
				std::to_string(m_Score));
			((TextComponent*)m_pComponents[m_TextIdx])->Update();
		}
		break;
	}
	case PickupType::Pill:
		m_IsSuper = true;
		break;
	default:
		break;
	}
}
