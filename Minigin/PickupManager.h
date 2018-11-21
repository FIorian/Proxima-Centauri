#pragma once
#include "Singleton.h"
#include "Zone.h"
#include "CrossingObject.h"

namespace dae
{
	class Character;

	class PickupManager final : public dae::Singleton<PickupManager>
	{
	public:
		void HitCheck(Character& character);
		void NavCheck(Character& character);
		void AddZone(std::shared_ptr<Zone> zone) { m_pZones.push_back(zone); }
		void AddPickup(const Pos& pos, const Scale& scale, PickupType type);
		void AddCrossing(std::shared_ptr<CrossingObject> crossing) { m_pCrossings.push_back(crossing); }

		void ClearPickups();

	private:
		//data members
		std::vector<std::shared_ptr<Zone>> m_pZones;
		std::vector<std::shared_ptr<CrossingObject>> m_pCrossings;
	};
}
