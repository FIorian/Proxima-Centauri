#include "MiniginPCH.h"
#include "PickupManager.h"
#include "Character.h"
#include "Utils.h"

void dae::PickupManager::HitCheck(Character& character)
{
	//hit detection pickups
	for (std::shared_ptr<Zone> zone : m_pZones)
		zone->HitCheck(character);
}

void dae::PickupManager::NavCheck(Character& character)
{
	//hit detection navigation objects
	for (std::shared_ptr<CrossingObject> crossing : m_pCrossings)
	{
		if (crossing->IsHit(character))
			return;
	}
}

void dae::PickupManager::AddPickup(const Pos & pos, const Scale & scale, PickupType type)
{
	//add hitbox to the correct zone
	Rect tempHitBox{ pos, scale };
	for (std::shared_ptr<Zone> z : m_pZones)
	{
		if (isOverlapping(z->GetRect(), tempHitBox))
		{
			z->AddPickup(pos, scale, type);
			return;
		}
	}
}

void dae::PickupManager::ClearPickups()
{
	//clear pickups
	for (std::shared_ptr<Zone> z : m_pZones)
	{
		z->ClearZone();
	}
	m_pZones.clear();
	m_pCrossings.clear();
}
