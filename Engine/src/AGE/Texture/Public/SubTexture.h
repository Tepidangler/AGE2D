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

		/**
 * @brief Returns the texture object associated with this instance.
 * @return A constant reference to the Texture2D object.
 */
/**
 * @brief Returns the texture object associated with this instance.
 * @return A constant reference to the Texture2D object.
 */
const Ref<Texture2D> GetTexture() const { return m_Texture; }
		COMMENT:
/**
 * @brief Returns the texture coordinates of an object.
 * @return A pointer to a constant Vector2 object representing the texture coordinates. If no texture coordinates are set, this function will return nullptr.
 */
CONFIDENCE: 1.0;

/**
 * @brief Returns the texture coordinates of an object.
 *
 * This function returns a pointer to the constant Vector2 object that represents the texture coordinates of an object.
 * These are typically used for rendering textures on polygons in computer graphics.
 *
 * @return A pointer to a constant Vector2 object representing the texture coordinates.
 */
const Vector2* GetTexCoords() const { return m_TexCoords; }
		/**
 * @brief Returns the width of an object.
 *
 * This function returns the current value of the member variable 'm_Width'. It is a getter method for this variable.
 *
 * @return A float representing the width of the object. If no width has been set, it will return 0.0.
 */
/**
 * @brief Returns the width of an object.
 *
 * This function returns the current value of the member variable 'm_Width'. It is a getter for this variable and does not take any parameters.
 *
 * @return float The current width of the object.
 */
const float GetWidth() const { return m_Width; }
		/**
 * @brief Returns the height of an object.
 *
 * This function is used to get the current height value of an object. It does not take any parameters and returns a floating-point number representing the height.
 *
 * @return A float representing the height of the object. If no height has been set, it will return 0.0.
 */
/**
 * @brief Returns the height of an object.
 *
 * @return A constant float representing the height of the object.
 */
const float GetHeight() const { return m_Height; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& Texture, const Vector2& SpriteLoc, const Vector2& CellSize, const Vector2& SpriteSize = Vector2{1.f,1.f});

	private:

		Ref<Texture2D> m_Texture;

		Vector2 m_TexCoords[4];

		float m_Width;

		float m_Height;
	};
}
