#pragma once
#include "Camera/Public/Camera.h"
#include "Camera/Public/EditorCamera.h"
#include "Render/Public/RenderAPI.h"
#include "Scene//Public/Components.h"
#include "Texture/Public/Texture.h"
#include "Texture/Public/SubTexture.h"
#include "Render/Public/Font.h"


namespace AGE
{
	class Renderer2D
	{
	public:

		static void Init();

		static void Shutdown();

		static void BeginScene(const Camera& Camera,  const Matrix4D& Transform);
		static void BeginScene(const EditorCamera& Camera);

		static void EndScene();

		static void Flush();

		//Primitives

		//Quads
		static void DrawQuad(const QuadProperties Props);
		static void DrawQuad(const Ref<Texture2D>& Texture, const QuadProperties Props);
		static void DrawQuad(const Ref<SubTexture2D>& Subtexture, const QuadProperties Props);

		//Circles
		static void DrawCircle(const Matrix4D& Transform, const Vector4& Color, float Thickness = 1.f, float Fade = .005f, int EntityID = -1);

		static void DrawLine(const Vector3& Pos0, const Vector3& Pos1, const Vector4& Color, int EntityID = -1);
		static void DrawRect(const Vector3& Position, const Vector2& Size, const Vector4& Color, int EntityID = -1);
		static void DrawRect(const Matrix4D& Transform, const Vector4& Color, int EntityID = -1);

		static void DrawSprite(SpriteRendererComponent& SRC);
		static void DrawTile(const SpriteRendererComponent& SRC);
		static void DrawString(const StringProperties& Props);

		static void DrawTileMapLayers(TileMapRendererComponent& TMRC, tmx_map* Map, std::vector<tmx_layer*> layers);

		static Statistics GetStats();

		static float GetLineWidth();
		static void SetLineWidth(float Width);

	private:
		static void DrawTileMapLayer(TileMapRendererComponent& TMRC, tmx_map* Map, tmx_layer* layer, int Depth);


		friend class AGEVideo;
	};
}