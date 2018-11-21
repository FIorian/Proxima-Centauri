#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"

dae::GameObject::GameObject(const Pos& pos, const Scale& scale)
	:m_Transform(pos, scale)
{	
}

dae::GameObject::~GameObject()
{
	//delete game object resources
	if (m_pComponents.size() > 0)
	{
		for (size_t i = 0; i < m_pComponents.size(); i++)
		{
			if (i != m_RCidx && i != m_TextIdx)
			{
				delete m_pComponents[i];
				m_pComponents[i] = nullptr;
			}
		}
	}
	m_pComponents.clear();
}

void dae::GameObject::RemoveRC()
{
	if (m_RCidx >= 0)
	{
		dae::Renderer::GetInstance().RemoveComponent(
			((dae::RenderComponent*)m_pComponents[m_RCidx])->GetRendererIdx());
	}
}

void dae::GameObject::AddComponent(Component* newComponent,
	bool isRenderComponent)
{
	m_pComponents.push_back(newComponent);
	if (isRenderComponent)
	{
		m_RCidx = int(m_pComponents.size() - 1);
	}
}

void dae::GameObject::SetRenderComponent(dae::RenderComponent* newRC)
{
	if (m_RCidx >= 0)
	{
		m_pComponents.at(m_RCidx) = newRC;
	}
}

