#include "MiniginPCH.h"
#include "HitboxComponent.h"


dae::HitboxComponent::HitboxComponent(const Rect& rect)
	:m_Rect(rect)
{
}

bool dae::HitboxComponent::Overlaps(const Rect & other) const
{
	if ((m_Rect.x + m_Rect.w) < other.x ||
		(other.x + other.w) < m_Rect.x)
		return false;

	if ((m_Rect.y + m_Rect.h) < other.y ||
		(other.y + other.h) < m_Rect.y)
		return false;

	return true;
}
