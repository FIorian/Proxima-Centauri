#pragma once
#include "Component.h"
#include <string>
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(const std::string& text, std::shared_ptr<dae::Font>& font);
		explicit TextComponent();
		virtual ~TextComponent() = default;

		void Update();
		void Render() const;

		//Mutators
		void SetText(const std::string& text) { m_Text = text; }
		void SetFont(std::shared_ptr<dae::Font> font) { m_Font = font; }

		void SetPos(const Pos& pos) { m_Transform.SetPos(pos.x, pos.y, pos.z); }
		void SetScale(const Scale& scale) { m_Transform.SetScale(scale.w, scale.h); }
		void SetAll(const Pos& pos, const Scale& scale)
		{
			m_Transform.SetPos(pos.x, pos.y, pos.z);
			m_Transform.SetScale(scale.w, scale.h);
		}

		//Accesors
		std::string GetText() const { return m_Text; }
		std::shared_ptr<dae::Texture2D> GetTexture() const { return m_Texture; }
		Pos GetPos() const { return m_Transform.GetPos(); }
		Scale GetScale() const { return m_Transform.GetScale(); }

		//delete copy ctr & assignment opr
		TextComponent(const TextComponent& rhs) = delete;
		TextComponent(TextComponent&& rhs) = delete;
		TextComponent& operator=(const TextComponent& rhs) = delete;
		TextComponent& operator=(TextComponent&& rhs) = delete;

	private:
		//Data members
		std::string m_Text;
		dae::Transform m_Transform;
		std::shared_ptr<dae::Font> m_Font;
		std::shared_ptr<dae::Texture2D> m_Texture;

		bool m_NeedsUpdate;
	};
}

