#pragma once
#include "GameObject.h"
#include "Utils.h"

namespace dae
{
	class Pickup final : public dae::GameObject
	{
	public:
		explicit Pickup(const Pos& pos, const Scale& scale);
		explicit Pickup();
		virtual ~Pickup() = default;

		virtual void Initialize();
		void Update(const GameContext& gameContext) override;

		bool IsHit(const Rect& otherHitbox);

		//mutators
		virtual void SetPos(const Pos& pos);
		virtual void SetScale(const Scale& scale);
		void SetType(PickupType type);
		virtual void SetAll(const Pos& pos, const Scale& scale, PickupType type);

		//accesors
		PickupType GetType() const { return m_Type; }

		//delete copy ctr & assignmtent opr
		Pickup(const Pickup& rhs) = delete;
		Pickup(Pickup&& rhs) = delete;
		Pickup& operator=(const Pickup& rhs) = delete;
		Pickup& operator=(Pickup&& rhs) = delete;

	private:
		//datamembers
		int m_HBidx = -1;
		PickupType m_Type = PickupType::Undefined;
	};
}
