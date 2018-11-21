#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"


dae::RenderComponent::RenderComponent()
	:Component()
	,m_pOwner(nullptr)
{
}

dae::RenderComponent::~RenderComponent() = default;

void dae::RenderComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_Texture,
		m_Transform.GetPos(), m_Transform.GetScale());
}

void dae::RenderComponent::SetTexture(const std::string & assetFile)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(assetFile);
}

void dae::RenderComponent::SetPos(float x, float y, float z)
{
	m_Transform.SetPos(x, y, z);
}

void dae::RenderComponent::SetScale(float w, float h)
{
	m_Transform.SetScale(w, h);
}

void dae::RenderComponent::SetAll(const std::string & assetFile, float xPos, float yPos, float zPos, 
	float wScale, float hScale, GameObject* pOwner)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(assetFile);
	m_Transform.SetPos(xPos, yPos, zPos);
	m_Transform.SetScale(wScale, hScale);
	m_pOwner = pOwner;
}

void dae::RenderComponent::SetAll(const std::string& assetFile, const Pos& pos, const Scale& scale,
	GameObject* pOwner)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(assetFile);
	m_Transform.SetPos(pos);
	m_Transform.SetAll(pos, scale);
	m_pOwner = pOwner;
}

void dae::RenderComponent::SetAllIdx(const std::string & assetFile, 
	float xPos, float yPos, float zPos, float wScale, float hScale,
	int idx, GameObject* pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetFile);
	m_Transform.SetPos(xPos, yPos, zPos);
	m_Transform.SetScale(wScale, hScale);
	m_RendererIdx = idx;
	m_pOwner = pOwner;
}

void dae::RenderComponent::SetAllIdx(const std::string& assetFile,
	const Pos & pos, const Scale & scale, int idx, GameObject* pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetFile);
	m_Transform.SetAll(pos, scale);
	m_RendererIdx = idx;
	m_pOwner = pOwner;
}

void dae::RenderComponent::SetAllTexture(std::shared_ptr<Texture2D> texture, const Pos & pos, const Scale & scale,
	GameObject* pOwner)
{
	m_Texture = texture;
	m_Transform.SetAll(pos, scale);
	m_pOwner = pOwner;
}

void dae::RenderComponent::SetAllTexture(const std::string & assetFile, const Pos & pos, const Scale & scale,
	GameObject* pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetFile);
	m_Transform.SetAll(pos, scale);
	m_pOwner = pOwner;
}
