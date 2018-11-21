#pragma once
#include "Transform.h"
#include "Component.h"
#include "RenderComponent.h"

namespace dae
{
	class GameObject
	{
	public:
		explicit GameObject(const Pos& pos, const Scale& scale);
		~GameObject();

		virtual void Initialize() = 0;
		virtual void Update(const GameContext& gameContext) = 0;

		//other
		virtual void RemoveRC();
		void AddComponent(Component* newComponent, bool isRenderComponent = false);
		void SetRenderComponent(dae::RenderComponent* newRC);

		//mutators
		virtual void SetPosition(float x, float y, float z) { m_Transform.SetPos(x, y, z); }
		virtual void SetPos(const Pos& pos) { m_Transform.SetPos(pos); }
		virtual void SetScale(float w, float h) { m_Transform.SetScale(w, h); }
		virtual void SetScale(const Scale& scale) { m_Transform.SetScale(scale); }

		virtual void SetAll(const Pos& pos, const Scale& scale) { m_Transform.SetAll(pos, scale); }

		//accesors
		virtual Transform GetTransform() const { return m_Transform; }
		virtual Pos GetPos() const { return m_Transform.GetPos(); }
		virtual Scale GetScale() const { return m_Transform.GetScale(); }
		int GetComponentVectorSize() const { return int(m_pComponents.size()); }

		//delete copy ctr & assignment opr
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		//data members
		Transform m_Transform;
		std::vector<Component*> m_pComponents;
		int m_RCidx{ -1 }; //render component
		int m_TextIdx{ -1 };
	};
}
