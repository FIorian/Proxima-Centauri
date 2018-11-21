#pragma once
#include "Singleton.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, const Pos& pos) const;
		void RenderTexture(const Texture2D& texture, const Pos& pos, const Scale& scale) const;

		//rendercomponents
		void MakePool(int nrOfComponents);
		RenderComponent* AddComponent(const std::string& assetFile, float xPos, float yPos, float zPos,
			float wScale, float hScale, GameObject* owner = nullptr);
		RenderComponent* AddComponent(const std::string& assetFile, const Pos& pos, const Scale& scale,
			GameObject* owner = nullptr);
		void ClearRenderer()
		{
			m_ActiveBoundary = 0;
			m_TextBoundary = 0;
			m_pLastOwner = nullptr;
		}
		void RemoveComponent(int idx);

		//text components
		void MakeTextPool(int nrOfComponents);
		TextComponent* AddText(std::string text, const Pos& pos);

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

	private:
		RenderComponent* m_pComponentPool = nullptr;
		GameObject* m_pLastOwner = nullptr;

		TextComponent* m_pTextPool = nullptr;
		int m_NrofText = 0;

		int m_NrComponetns = 0;
		size_t m_ActiveBoundary = 0;
		size_t m_TextBoundary = 0;
	};
}

