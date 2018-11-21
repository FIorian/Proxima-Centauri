#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "Component.h"
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
	public:
		explicit Transform()
			:m_Position(Pos{0.f, 0.f, 0.f})
			,m_Scale(Scale{1.f, 1.f})
		{}
		explicit Transform(const Pos& pos, const Scale& scale)
			:m_Position(pos)
			,m_Scale(scale)
		{}
		~Transform(){}

		//mutators
		void SetPos(float x, float y, float z)
		{
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}
		void SetPos(const Pos& pos) { m_Position = pos; }

		void SetScale(float w, float h)
		{
			m_Scale.w = w;
			m_Scale.h = h;
		}
		void SetScale(const Scale& scale) { m_Scale = scale; }

		void SetAll(const Pos& pos, const Scale& scale)
		{
			m_Position = pos;
			m_Scale = scale;
		}

		//accessors
		Pos GetPos() const { return m_Position; }
		Scale GetScale() const { return m_Scale; }

	private:
		//glm::vec3 m_Position{0.f, 0.f, 0.f};
		Pos m_Position;
		Scale m_Scale;
	};
}
