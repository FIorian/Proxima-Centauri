#pragma once
#include "Component.h"
#include "Texture2D.h"
#pragma warning (push)
#pragma warning (disable: 4201)
#include <glm/detail/type_vec3.hpp>
#include "Transform.h"
#pragma warning (pop)

namespace dae
{
	class GameObject;
	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent();
		~RenderComponent();

		void Render() const;

		//Mutators
		void SetTexture(const std::string& assetFile);
		void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; }

		void SetIdx(int newIdx) { m_RendererIdx = newIdx; }

		void SetPos(float x, float y, float z);
		void SetPos(const Pos& pos) { m_Transform.SetPos(pos); }

		void SetScale(float w, float h);
		void SetScale(const Scale& scale) { m_Transform.SetScale(scale); }

		void SetAll(const std::string& assetFile, float xPos, float yPos, float zPos,
			float wScale, float hScale, GameObject* pOwner);
		void SetAll(const std::string& assetFile, const Pos& pos, const Scale& scale, GameObject* pOwner);
		void SetAllTransfrom(const Pos& pos, const Scale& scale) { m_Transform.SetAll(pos, scale); }
		void SetAllIdx(const std::string& assetFile, float xPos, float yPos, float zPos,
			float wScale, float hScale, int idx, GameObject* pOwner);
		void SetAllIdx(const std::string& assetFile, const Pos& pos, const Scale& scale, int idx,
			GameObject* pOwner);
		void SetAllTexture(std::shared_ptr<Texture2D> texture, const Pos& pos, const Scale& scale,
			GameObject* pOwner);
		void SetAllTexture(const std::string& assetFile, const Pos& pos, const Scale& scale,
			GameObject* pOwner);

		//Accesors 
		std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }
		Pos GetPos() const { return m_Transform.GetPos(); }
		Scale GetScale() const { return m_Transform.GetScale(); }
		int GetRendererIdx() const {
			if (m_RendererIdx >= 0)
				return m_RendererIdx;
			return -1;
		}
		GameObject* GetOwner()
		{
			if (m_pOwner)
				return m_pOwner;
			return nullptr;
		}

		//delete copy ctr & assignment opr
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		//datamembers
		std::shared_ptr<Texture2D> m_Texture;
		Transform m_Transform;
		int m_RendererIdx{ -1 };

		GameObject* m_pOwner;
	};
}

