#pragma once
#include "Component.h"

namespace dae
{
	class HitboxComponent final : public dae::Component
	{
	public:
		explicit HitboxComponent(const Rect& rect);
		virtual ~HitboxComponent() = default;

		bool Overlaps(const Rect& other) const;

		//Mutators
		void SetRect(const Rect& newRect) { m_Rect = newRect; }
		void SetPos(const Pos& pos)
		{
			m_Rect.x = pos.x;
			m_Rect.y = pos.y;
		}
		void SetScale(const Scale& scale)
		{
			m_Rect.w = scale.w;
			m_Rect.h = scale.h;
		}

		//Accesors
		Rect GetRect() const { return m_Rect; }
		Pos GetPos() const { return Pos{ m_Rect.x, m_Rect.y, 1.f }; }
		Scale GetScale() const { return Scale{ m_Rect.w, m_Rect.h }; }

		//delete copy ctr & assignment opr
		HitboxComponent(const HitboxComponent& rhs) = delete;
		HitboxComponent(HitboxComponent&& rhs) = delete;
		HitboxComponent& operator=(const HitboxComponent& rhs) = delete;
		HitboxComponent& operator=(HitboxComponent&& rhs) = delete;

	private:
		//Datamembers
		Rect m_Rect;
	};
}

