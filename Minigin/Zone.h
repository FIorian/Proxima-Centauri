#pragma once
#include "Pickup.h"
#include "Character.h"

namespace dae
{
	class Zone
	{
	public:
		explicit Zone(const Rect& rect);
		~Zone();

		void MakePool(int nrPickups);
		void AddPickup(const Pos& pos, const Scale& scale, PickupType type);

		void HitCheck(Character& character);

		void ClearZone() { m_ActiveBoundary = 0; }

		//accesors
		Rect GetRect() const { return m_Rect; }

		Zone(const Zone& rhs) = delete;
		Zone(Zone&& rhs) = delete;
		Zone& operator=(const Zone& rhs) = delete;
		Zone& operator=(Zone&& rhs) = delete;

	private:
		//data members
		//pickups
		Pickup* m_pPickupPool = nullptr;
		int m_NrPickups = 0;
		size_t m_ActiveBoundary = 0;

		//std::vector<std::unique_ptr<Pickup>> m_pPickups;

		//zone
		const Rect m_Rect;

		//member functions
		void RemovePickup(size_t idx);
	};
}
