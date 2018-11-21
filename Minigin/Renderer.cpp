#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "ResourceManager.h"
//#include "GameObject.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
	/*| SDL_RENDERER_PRESENTVSYNC*/); // toggle V-sync
	if (mRenderer == nullptr) {
		std::stringstream ss; ss << "SDL_CreateRenderer Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	//Render texture components
	if (m_pComponentPool != nullptr && m_ActiveBoundary != 0)
	{
		//limit rendering to active boundary
		for (size_t i = 0; i < m_ActiveBoundary; i++)
		{
			RenderTexture(*m_pComponentPool[i].GetTexture(), m_pComponentPool[i].GetPos(),
				m_pComponentPool[i].GetScale()); 
		}
	}

	//text pool
	if (m_pTextPool != nullptr)
	{
		for (size_t i = 0; i < m_TextBoundary; i++)
		{
			RenderTexture(*m_pTextPool[i].GetTexture(), 
				m_pTextPool[i].GetPos());
		}
	}
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}

	//delete render component pool
	delete[] m_pComponentPool;
	m_pComponentPool = nullptr;

	//delete text component pool
	delete[] m_pTextPool;
	m_pTextPool = nullptr;
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const Pos& pos) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const Pos& pos,
	const Scale& scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(scale.w);
	dst.h = static_cast<int>(scale.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::MakePool(int nrOfComponents)
{
	//dont make pool if one already exists
	if (m_pComponentPool == nullptr)
	{
		m_pComponentPool = new RenderComponent[nrOfComponents];
		m_NrComponetns = nrOfComponents;
	}
}

dae::RenderComponent* dae::Renderer::AddComponent(const std::string & assetFile, float xPos, float yPos, 
	float zPos,	float wScale, float hScale, GameObject* owner)
{
	if (m_pComponentPool != nullptr)
	{
		m_pComponentPool[m_ActiveBoundary].SetAllIdx(assetFile, xPos, yPos, zPos, 
			wScale, hScale, int(m_ActiveBoundary), owner);
		m_ActiveBoundary++;
		if (owner != nullptr)
			m_pLastOwner = owner;

		return &m_pComponentPool[m_ActiveBoundary - 1];
	}
	
	//@ME: THERE IS NO CONSOLE SO THIS SHOULD BE REDONE WITH PROPER EXEPTION THROWING
	std::cout << "Trying to add component to empty render pool, returning nullptr" << std::endl;
	return nullptr;
}

dae::RenderComponent* dae::Renderer::AddComponent(const std::string& assetFile, 
	const Pos& pos, const Scale& scale, GameObject* owner)
{
	if (m_pComponentPool != nullptr)
	{
		//rather than creating a new component we fill the next component in our pool and move up the active boundary
		m_pComponentPool[m_ActiveBoundary].SetAllIdx(assetFile, pos, scale, int(m_ActiveBoundary), owner);
		m_ActiveBoundary++;

		//we need the last owner for removing components
		if (owner != nullptr)
			m_pLastOwner = owner;

		//we return a pointer to the render component to the game object that wants to use it
		return &m_pComponentPool[m_ActiveBoundary - 1];
	}
	
	return nullptr;
}

//^
//@ME: THERE IS NO CONSOLE SO THIS SHOULD BE REDONE WITH PROPER EXEPTION THROWING
//std::cout << "Trying to add component to empty render pool, returning nullptr" << std::endl;

void dae::Renderer::RemoveComponent(int idx)
{
	//if the component we want to remove is the last component in the active portion of our pool 
	//we just move back the boundary
	if (idx == m_ActiveBoundary - 1 && m_pComponentPool != nullptr)
	{
		m_ActiveBoundary--;
		return;
	}
	
	if (m_ActiveBoundary > 0 && m_pComponentPool != nullptr
		&& idx < m_ActiveBoundary)
	{
		//if not we put all information of the last one in the active portion of our pool 
		//within the component we want to remove from rendering
		m_pComponentPool[idx].SetAllTexture(m_pComponentPool[m_ActiveBoundary - 1].GetTexture() ,
			m_pComponentPool[m_ActiveBoundary - 1].GetPos(),
			m_pComponentPool[m_ActiveBoundary - 1].GetScale(), nullptr);

		//now we make the pointer of that last component point to its new render component
		m_pLastOwner->SetRenderComponent(&m_pComponentPool[idx]);
		//and decrease our active component boundary
		m_ActiveBoundary--;
		//adjust the new last owner
		GameObject* tempOwner = m_pComponentPool[m_ActiveBoundary - 1].GetOwner();
		if (tempOwner){ m_pLastOwner = tempOwner; }
		
	}
}

void dae::Renderer::MakeTextPool(int nrOfComponents)
{
	if (m_pTextPool == nullptr)
	{
		m_pTextPool = new TextComponent[nrOfComponents];
		m_NrofText = nrOfComponents;
	}
}

dae::TextComponent * dae::Renderer::AddText(std::string text, const Pos & pos)
{
	if (m_TextBoundary < m_NrofText)
	{
		m_pTextPool[m_TextBoundary].SetText(text);
		m_pTextPool[m_TextBoundary].SetPos(pos);
		//	m_pTextPool[m_TextBoundary].Update();
		m_TextBoundary++;
		return &m_pTextPool[m_TextBoundary - 1];
	}
	return nullptr;
}
