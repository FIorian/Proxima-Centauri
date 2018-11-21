#include "MiniginPCH.h"
#include "Pickup.h"
#include "HitboxComponent.h"
#include "Renderer.h"

dae::Pickup::Pickup(const Pos& pos, const Scale& scale)
	:GameObject(pos, scale)
{
}

dae::Pickup::Pickup()
	:GameObject(Pos{ 0.f, 0.f, 0.f }, Scale{ 1.f, 1.f })
{
}

void dae::Pickup::Initialize()
{
	//create hitbox
	const Rect tempRect{ m_Transform.GetPos(), m_Transform.GetScale() };
	HitboxComponent* hitbox = new HitboxComponent(tempRect);
	this->AddComponent(hitbox);

	m_HBidx = this->GetComponentVectorSize() - 1;
}

void dae::Pickup::Update(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

bool dae::Pickup::IsHit(const Rect& otherHitbox)
{
	//hit detection
	if (m_HBidx >= 0 &&
		((dae::HitboxComponent*) m_pComponents[m_HBidx])->Overlaps(otherHitbox))
	{
		//remove pickup from renderer pool
		Renderer::GetInstance().RemoveComponent(
			((dae::RenderComponent*) m_pComponents[m_RCidx])->GetRendererIdx());
		return true;
	}	
	return false;
}

void dae::Pickup::SetPos(const Pos& pos)
{
	GameObject::SetPos(pos);
	if (m_HBidx >= 0)
	{
		((dae::HitboxComponent*) m_pComponents[m_HBidx])->SetPos(pos);
	}
}

void dae::Pickup::SetScale(const Scale& scale)
{
	GameObject::SetScale(scale);
	if (m_HBidx >= 0)
	{
		((dae::HitboxComponent*) m_pComponents[m_HBidx])->SetScale(scale);
	}
}

void dae::Pickup::SetType(PickupType type)
{
	//determine pickuptype

	m_Type = type;

	switch (type)
	{
	case PickupType::Undefined:
		return;
	case PickupType::Candy:
	{
		if (m_RCidx >= 0)
		{
			((RenderComponent*)m_pComponents[m_RCidx])->SetTexture("candy.png");
			return;
		}
		RenderComponent*  texture = Renderer::GetInstance().AddComponent("candy.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
		break;
	}
	case PickupType::Pill:
	{
		if (m_RCidx >= 0)
		{
			((RenderComponent*)m_pComponents[m_RCidx])->SetTexture("capsule.png");
			return;
		}
		RenderComponent* texture = Renderer::GetInstance().AddComponent("capsule.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
		break;
	}
	default:
		break;
	}
}

void dae::Pickup::SetAll(const Pos& pos, const Scale& scale, PickupType type)
{
	//GEOMETRY
	GameObject::SetAll(pos, scale);
	if (m_HBidx >= 0)
	{
		Rect tempRect{ pos, scale };
		((dae::HitboxComponent*) m_pComponents[m_HBidx])->SetRect(tempRect);
	}

	//TEXTURE
	m_Type = type;

	switch (type)
	{
	case PickupType::Undefined:
		return;
	case PickupType::Candy:
	{
		if (m_RCidx >= 0)
		{
			((RenderComponent*)m_pComponents[m_RCidx])->SetAllTexture("candy.png", 
				m_Transform.GetPos(), m_Transform.GetScale(), this);
			return;
		}
		RenderComponent*  texture = Renderer::GetInstance().AddComponent("candy.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
		break;
	}
	case PickupType::Pill:
	{
		if (m_RCidx >= 0)
		{
			((RenderComponent*)m_pComponents[m_RCidx])->SetAllTexture("capsule.png",
				m_Transform.GetPos(), m_Transform.GetScale(), this);
			return;
		}
		RenderComponent* texture = Renderer::GetInstance().AddComponent("capsule.png",
			m_Transform.GetPos(), m_Transform.GetScale(), this);
		this->AddComponent(texture, true);
		break;
	}
	default:
		break;
	}
}
