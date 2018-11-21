#pragma once

namespace dae
{
	class Component
	{
	public:
		explicit Component() = default;
		virtual ~Component() = default;

		//delete copy ctr & assignment opr
		Component(const Component& rhs) = delete;
		Component(Component&& rhs) = delete;
		Component& operator=(const Component& rhs) = delete;
		Component& operator=(Component&& rhs) = delete;
	};
}
