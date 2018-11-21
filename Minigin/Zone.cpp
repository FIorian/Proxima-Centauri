#include "MiniginPCH.h"
#include "Zone.h"

dae::Zone::Zone(const Rect& rect)
	:m_Rect(rect)
{
}

dae::Zone::~Zone()
{
	delete[] m_pPickupPool;
	m_pPickupPool = nullptr;
}

void dae::Zone::MakePool(int nrPickups)
{
	//create pickup pool
	if (m_pPickupPool == nullptr)
	{
		m_pPickupPool = new Pickup[nrPickups];
		m_NrPickups = nrPickups;
	}
}

void dae::Zone::AddPickup(const Pos& pos, const Scale& scale, PickupType type)
{
	//add pickup to pool
	if (m_pPickupPool != nullptr && m_ActiveBoundary < m_NrPickups)
	{
		m_pPickupPool[m_ActiveBoundary].SetAll(pos, scale, type);
		m_pPickupPool[m_ActiveBoundary].Initialize();
		m_ActiveBoundary++;
	}
}

void dae::Zone::HitCheck(Character& character)
{
	//hit detection pickups
	for (size_t i = 0; i < m_ActiveBoundary; i++)
	{
		if (m_pPickupPool[i].IsHit(character.GetHitboxRect()))
		{
			character.Pickup(m_pPickupPool[i].GetType());
			RemovePickup(i);
		}
	}
}

void dae::Zone::RemovePickup(size_t idx)
{
	//remove pickup object
	if (idx == m_ActiveBoundary - 1 && m_pPickupPool != nullptr)
	{
		m_ActiveBoundary--;
		return;
	}
	if (m_ActiveBoundary > 0 && m_pPickupPool != nullptr
		&& idx < m_ActiveBoundary)
	{
		m_pPickupPool[idx].SetAll(m_pPickupPool[m_ActiveBoundary - 1].GetPos(),
			m_pPickupPool[m_ActiveBoundary - 1].GetScale(),
			m_pPickupPool[m_ActiveBoundary - 1].GetType());
		m_ActiveBoundary--;
	}
}
