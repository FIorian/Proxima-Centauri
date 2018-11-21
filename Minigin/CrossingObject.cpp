#include "MiniginPCH.h"
#include "CrossingObject.h"
#include "HitboxComponent.h"
#include "Renderer.h"

dae::CrossingObject::CrossingObject(const Pos& pos, const Scale& scale,
	Direction restrictedDir1, Direction restrictedDir2)
	:GameObject(pos, scale)
	,m_RestrictedDir1(restrictedDir1)
	,m_RestrictedDir2(restrictedDir2)
{
	HitboxComponent* hitBox = new HitboxComponent(Rect{ pos, scale });
	this->AddComponent(hitBox);
	m_HBidx = this->GetComponentVectorSize() - 1;

	RenderComponent* texture = Renderer::GetInstance().AddComponent("crossing.png",
		m_Transform.GetPos(), m_Transform.GetScale(), this);
	this->AddComponent(texture, true);
}

bool dae::CrossingObject::IsHit(Character& character)
{
	//redirect steering
	if (((HitboxComponent*)m_pComponents[m_HBidx])->Overlaps(character.GetDirectionHB()))
	{
		if (m_RestrictedDir1 == character.GetCurrentDirection() ||
			m_RestrictedDir2 == character.GetCurrentDirection())
		{
			character.SetCurrentDirection(Direction::IDLE);
		}

		if (m_RestrictedDir1 == character.GetRequestedDirection() ||
			m_RestrictedDir2 == character.GetRequestedDirection())
		{
			return true;
		}

		character.SetDirection();		
		return true;
	}

	return false;
}
