#pragma once
#include <glm/glm.hpp>

#include "Texture/Public/Texture.h"
#include "Math/Public/MathStructures.h"


namespace AGE
{
	class SubTexture2D
	{
	public:

		SubTexture2D(const Ref<Texture2D>& Texture, const Vector2& Min, const Vector2& Max);
		SubTexture2D(void* Data);

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const Vector2* GetTexCoords() const { return m_TexCoords; }
		const float GetWidth() const { return m_Width; }
		const float GetHeight() const { return m_Height; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& Texture, const Vector2& SpriteLoc, const Vector2& CellSize, const Vector2& SpriteSize = Vector2{1.f,1.f});

	private:

		Ref<Texture2D> m_Texture;

		Vector2 m_TexCoords[4];

		float m_Width;

		float m_Height;
	};
}
