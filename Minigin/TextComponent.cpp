#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"


dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font>& font)
	:m_NeedsUpdate(true),
	m_Text(text),
	m_Font(font)
{
}

dae::TextComponent::TextComponent()
	:m_NeedsUpdate(true),
	m_Text("")
{
	//init font
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_Font = font;
}

void dae::TextComponent::Update()
{
	//update text if needed
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255, 255, 255 };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			std::stringstream ss;
			ss << "text " << m_Text << "failed to update " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			std::stringstream ss;
			ss << "texture creation went wrong: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
	}
}

void dae::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.GetPos());
	}
}
