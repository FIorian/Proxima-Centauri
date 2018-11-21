#include "MiniginPCH.h"
#include "Character.h"
#include "RenderComponent.h"
#include "HitboxComponent.h"


dae::Character::Character(const Pos& pos, const Scale& scale, float velocity,
	Direction initDirection)
	:GameObject(pos, scale)
	,m_Velocity(velocity)
	,m_currentDirection(initDirection)
{
}

void dae::Character::Initialize()
{
	//create hitboxes
	//for collision
	Rect tempRect{ m_Transform.GetPos(), m_Transform.GetScale() };
	HitboxComponent* hitbox = new HitboxComponent(tempRect);
	this->AddComponent(hitbox);
	m_HBidx = this->GetComponentVectorSize() - 1;

	//for navigation
	tempRect = Rect{ Pos{ m_Transform.GetPos().x + (m_Transform.GetScale().w / 2.f - 1.f),
		m_Transform.GetPos().y + (m_Transform.GetScale().h / 2.f - 1.f) },
		Scale{ 2.f, 2.f } };

	HitboxComponent* directionHB = new HitboxComponent(tempRect);
	this->AddComponent(directionHB);
	m_DirHBidx = this->GetComponentVectorSize() - 1;
}

void dae::Character::Update(const GameContext& gameContext)
{
	Pos pos = m_Transform.GetPos();
	Pos dirPos = pos;
	if (m_DirHBidx >= 0)
		dirPos = ((HitboxComponent*)m_pComponents[m_DirHBidx])->GetPos();

	//MOVEMENT
	switch (m_currentDirection)
	{
	case Direction::IDLE:
		break;
	case Direction::DOWN:
		//set new position
		m_Transform.SetPos(pos.x, pos.y + gameContext.deltaT * m_Velocity, pos.z);
		if (m_DirHBidx >= 0)
			((dae::HitboxComponent*)m_pComponents[m_DirHBidx])->SetPos(
				Pos{ dirPos.x, dirPos.y + gameContext.deltaT * m_Velocity, dirPos.z });
		break;
	case Direction::RIGHT:
		//set new position
		m_Transform.SetPos(pos.x + gameContext.deltaT * m_Velocity, pos.y, pos.z);
		if (m_DirHBidx >= 0)
			((dae::HitboxComponent*)m_pComponents[m_DirHBidx])->SetPos(
				Pos{ dirPos.x + gameContext.deltaT * m_Velocity, dirPos.y, dirPos.z });
		break;
	case Direction::LEFT:
		//set new position
		m_Transform.SetPos(pos.x - gameContext.deltaT * m_Velocity, pos.y, pos.z);
		if (m_DirHBidx >= 0)
			((dae::HitboxComponent*)m_pComponents[m_DirHBidx])->SetPos(
				Pos{ dirPos.x - gameContext.deltaT * m_Velocity, dirPos.y, dirPos.z });
		break;
	case Direction::UP:
		//set new position
		m_Transform.SetPos(pos.x, pos.y - gameContext.deltaT * m_Velocity, pos.z);
		if (m_DirHBidx >= 0)
			((dae::HitboxComponent*)m_pComponents[m_DirHBidx])->SetPos(
				Pos{ dirPos.x, dirPos.y - gameContext.deltaT * m_Velocity, dirPos.z });
		break;
	default:
		break;
	}

	//update render component
	if (m_RCidx >= 0)
		((dae::RenderComponent*) m_pComponents[m_RCidx])->SetPos(m_Transform.GetPos());
	if (m_HBidx >= 0)
		((dae::HitboxComponent*) m_pComponents[m_HBidx])->SetPos(m_Transform.GetPos());

}

Rect dae::Character::GetHitboxRect() const
{
	if (m_HBidx >= 0)
	{
		return ((dae::HitboxComponent*) m_pComponents[m_HBidx])->GetRect();
	}

	//if not return rect that could never be hit
	return Rect { Pos{-2.f, -2.f}, Scale{1.f, 1.f} };
}

Rect dae::Character::GetDirectionHB() const
{
	if (m_DirHBidx >= 0)
	{
		return ((dae::HitboxComponent*) m_pComponents[m_DirHBidx])->GetRect();
	}

	//if not return rect that could never be hit
	return Rect{ Pos{ -2.f, -2.f }, Scale{ 1.f, 1.f } };
}

