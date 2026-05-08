#include "AGEpch.hpp"

#include "Render/Public/Renderer2D.h"
#include "Render/Public/RenderCommand.h"
#include "Render/Public/VertexArray.h"
#include "Render/Public/Shader.h"
#include "Scene/Public/Entity.h"
#include "Platform/OpenGL/Public/OpenGLShader.h"
#include "Platform/OpenGL/Public/OpenGLTexture.h"
#include "Utils/Public/WindowsUtils.h"
#include "Sprite/Public/SpriteAPI.h"
#include <glm/gtc/matrix_transform.hpp>
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include "Render/Public/MSDFData.h"
#include <rttr/registration>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/registration>
#include "Render/Public/MSDFData.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <rttr/registration>
#include "Render/Public/MSDFData.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
RTTR_REGISTRATION
{
	rttr::registration::method("Draw String", &AGE::Renderer2D::DrawString);
}

namespace AGE
{

	/**
 * @brief Initializes the Renderer2D object.
 * 
 * This function is used to initialize the Renderer2D object, setting it up for rendering operations. It does not take any parameters and returns void.
 */
void Renderer2D::Init()
	{

	}
		

	/**
 * @brief Shuts down the Renderer2D instance.
 * 
 * This function is used to clean up any resources that were allocated during initialization of the Renderer2D instance, such as freeing GPU memory or closing open graphics contexts. It also resets all internal state so a new call to Initialize() will start with an empty slate.
 *
 * @return void
 */
void Renderer2D::Shutdown()
	{

	}
	
	/** 
 * @brief Begins a 2D scene with the specified camera and transformation.
 * 
 * This function starts a new batch for rendering 2D objects, using the provided camera and transformation matrix. The camera is used to calculate the view-projection matrix that will be applied during rendering.
 * 
 * @param Camera A const reference to the camera object representing the current scene's viewpoint.
 * @param Transform A const reference to a Matrix4D object representing any additional transformations to apply to this batch of objects.
 */
void Renderer2D::BeginScene(const Camera& Camera, const Matrix4D& Transform)
	{
		AGE_PROFILE_FUNCTION();
		RenderCommand::s_GraphicsPipeline->StartBatch2D();
	}
	/**
 * @brief Begin a 2D scene with the given camera.
 *
 * This function begins a new 2D scene using the provided EditorCamera. It calculates the World View Projection Matrix (WVPM) based on the camera's projection, view matrix and world matrix. The WVPM is then set as the CameraUniformBuffer data. Finally, it starts a batch for rendering 2D objects.
 *
 * @param Camera The EditorCamera to use for this scene.
 */
void Renderer2D::BeginScene(const EditorCamera& Camera)
	{
		AGE_PROFILE_FUNCTION();

		Matrix4D WVPM = (Camera.GetProjection() * Camera.GetViewMatrix()) * Camera.GetWorldMatrix();
		RenderCommand::s_GraphicsPipeline->GetData().CameraUniformBuffer->SetData(&WVPM, sizeof(Renderer2DData::CameraData));
		RenderCommand::s_GraphicsPipeline->StartBatch2D();
	}
	/** 
 * @brief This function is used to end the current scene rendering in a 2D context.
 * It calls the Flush2D method of the currently active GraphicsPipeline object, which should handle any remaining rendering tasks for this frame.
 * 
 * @return void
 */
void Renderer2D::EndScene()
	{
		AGE_PROFILE_FUNCTION();

		RenderCommand::s_GraphicsPipeline->Flush2D();
	}
	/** 
 * @brief This function flushes the 2D rendering pipeline.
 * 
 * The RenderCommand class' s_GraphicsPipeline member is accessed and its Flush2D() method is called to flush all pending draw calls in the 2D graphics pipeline.
 * 
 * @return void No return value.
 */
void Renderer2D::Flush()
	{
		RenderCommand::s_GraphicsPipeline->Flush2D();		
	}

	/**
 * @brief Draw a quadrilateral with the specified properties.
 * 
 * This function draws a quadrilateral on the screen using the provided QuadProperties object. The quad is drawn in the current graphics pipeline and its vertices are added to the vertex buffer if there's enough space. If not, it calls `NextBatch2D` to start a new batch.
 * 
 * @param Props A structure containing properties of the quadrilateral such as color, size, transformation matrix, texture coordinates, tiling factor and entity ID.
 */
void Renderer2D::DrawQuad(const QuadProperties Props)
	{
		if (RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			RenderCommand::s_GraphicsPipeline->NextBatch2D();
		}
		RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Quad"]->CreateQuad(RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr, Props.Color, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, Props.Size, Props.Transform, Props.TextureCoords, Props.TilingFactor, 0, Props.EntityID);
		RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount += 6;

		RenderCommand::s_GraphicsPipeline->GetData().Stats.QuadCount++;
	}
	
void Renderer2D::DrawQuad(const Ref<Texture2D>& Texture, const QuadProperties Props)
	{
		if (RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			RenderCommand::s_GraphicsPipeline->NextBatch2D();
		}
		float TextureIndex = 0.f;
	
		if (Texture != nullptr)
		{
			for (uint32_t i = 0; i < RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex; i++)
			{
				if (*RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[i].get() == *Texture.get())
				{
					TextureIndex = (float)i;
					break;
				}
			}
	
			if (TextureIndex == 0.f)
			{
				TextureIndex = (float)RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex] = Texture;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex++;
	
			}
		}
		RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Quad"]->CreateQuad(RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr, Props.TintColor, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, Props.Size, Props.Transform, Props.TextureCoords, Props.TilingFactor, TextureIndex, Props.EntityID);
		RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount += 6;
		RenderCommand::s_GraphicsPipeline->GetData().Stats.QuadCount++;
	}
	
void Renderer2D::DrawQuad(const Ref<SubTexture2D>& Subtexture, const QuadProperties Props)
	{
		if (RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			RenderCommand::s_GraphicsPipeline->NextBatch2D();
		}
		const Ref<Texture2D> texture = Subtexture->GetTexture();
		float TextureIndex = 0.f;

		if (texture != nullptr)
		{
			for (uint32_t i = 1; i < RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex; i++)
			{
				if (*RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[i].get() == *texture.get())
				{
					TextureIndex = (float)i;
					break;
				}
			}

			if (TextureIndex == 0.f)
			{
				TextureIndex = (float)RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex] = texture;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex++;

			}
		}
		RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Quad"]->CreateQuad(RenderCommand::s_GraphicsPipeline->GetData().QuadVertexBufferPtr, Props.TintColor, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, Props.Size, Props.Transform, Props.TextureCoords, Props.TilingFactor, TextureIndex, Props.EntityID);
		RenderCommand::s_GraphicsPipeline->GetData().QuadIndexCount += 6;
		RenderCommand::s_GraphicsPipeline->GetData().Stats.QuadCount++;
	}
	/**
 * @brief Draw a circle on the screen using the provided parameters.
 * 
 * This function is used to draw a circle on the screen with the given transform, color, thickness, fade and entity ID. The function first checks if there are enough indices in the buffer for another circle. If not, it calls `NextBatch()` to create a new batch. Then, it creates a circle using the provided parameters and increments the index count and circle count stats.
 * 
 * @param Transform The transformation matrix of the circle.
 * @param Color The color of the circle.
 * @param Thickness The thickness of the circle's outline.
 * @param Fade The fade value for the circle.
 * @param EntityID The ID of the entity associated with the circle.
 */
void Renderer2D::DrawCircle(const Matrix4D& Transform, const Vector4& Color, float Thickness, float Fade, int EntityID)
	{
		AGE_PROFILE_FUNCTION();

		//TODO:: Implement for circles
		//if (RenderCommand::s_GraphicsPipeline->GetData().CircleIndexCount >= Renderer2DData::MaxIndexCount)
		//{
		//	NextBatch();
		//}


		RenderCommand::s_GraphicsPipeline->GetData().CircleVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Circle"]->CreateCircle(RenderCommand::s_GraphicsPipeline->GetData().CircleVertexBufferPtr, Transform, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, Color, Thickness, Fade, EntityID);
		
		RenderCommand::s_GraphicsPipeline->GetData().CircleIndexCount += 6;
		RenderCommand::s_GraphicsPipeline->GetData().Stats.CircleCount++;
	}

	/**
 * @brief Draw a line in the 3D scene.
 * 
 * This function is used to draw a line segment in the 3D scene with a specified color and positions. The line is drawn between two points, Pos0 and Pos1. The color of the line can be customized by passing a Vector4 representing the RGBA values. The EntityID parameter allows for identification of which entity (if any) this line corresponds to.
 * 
 * @param Pos0 A constant reference to a Vector3 representing the start point of the line segment.
 * @param Pos1 A constant reference to a Vector3 representing the end point of the line segment.
 * @param Color A constant reference to a Vector4 representing the RGBA color values for the line.
 * @param EntityID An integer value that represents the ID of the entity associated with this line (if any).
 * 
 * @return void
 */
void Renderer2D::DrawLine(const Vector3& Pos0, const Vector3& Pos1, const Vector4& Color, int EntityID)
	{
		RenderCommand::s_GraphicsPipeline->GetData().LineVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Line"]->CreateLine(RenderCommand::s_GraphicsPipeline->GetData().LineVertexBufferPtr, Color, Pos0, Pos1, EntityID);

		RenderCommand::s_GraphicsPipeline->GetData().LineVertexCount += 2;
	}

	/**
 * @brief Draws a 2D rectangle on the screen.
 * 
 * This function takes in a position, size and color to draw a rectangle on the screen. The rectangle is defined by four lines - two horizontal and two vertical.
 * 
 * @param Position The center of the rectangle.
 * @param Size The width and height of the rectangle.
 * @param Color The color of the rectangle.
 * @param EntityID An identifier for the entity associated with this rectangle.
 * 
 * @return void
 */
void Renderer2D::DrawRect(const Vector3& Position, const Vector2& Size, const Vector4& Color, int EntityID)
	{
		Vector3 p0 = Vector3(Position.x - Size.x * .5f, Position.y - Size.y * .5f, Position.z);
		Vector3 p1 = Vector3(Position.x + Size.x * .5f, Position.y - Size.y * .5f, Position.z);
		Vector3 p2 = Vector3(Position.x + Size.x * .5f, Position.y + Size.y * .5f, Position.z);
		Vector3 p3 = Vector3(Position.x - Size.x * .5f, Position.y + Size.y * .5f, Position.z);

		DrawLine(p0,p1 , Color);
		DrawLine(p1,p2 , Color);
		DrawLine(p2,p3 , Color);
		DrawLine(p3,p0 , Color);
	}

	/**
 * @brief Draws a 2D rectangle using lines.
 *
 * This function takes in a transformation matrix, color and entity ID as parameters to draw a 2D rectangle on the screen. The transformation matrix is used to transform the vertices of the rectangle into world space. The color specifies the color of the rectangle and the entity ID can be used for further processing or identification of the drawn object.
 *
 * @param Transform A constant reference to a Matrix4D object representing the transformation matrix.
 * @param Color A constant reference to a Vector4 object representing the color of the rectangle.
 * @param EntityID An integer representing the entity ID of the drawn object.
 *
 * @return void
 */
void Renderer2D::DrawRect(const Matrix4D& Transform, const Vector4& Color, int EntityID)
	{
		Vector3 LineVertices[4];
		for (int i = 0; i < 4; i++)
		{
			LineVertices[i] = Transform * RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions[i];
		}

		DrawLine(LineVertices[0], LineVertices[1], Color);
		DrawLine(LineVertices[1], LineVertices[2], Color);
		DrawLine(LineVertices[2], LineVertices[3], Color);
		DrawLine(LineVertices[3], LineVertices[0], Color);

	}

	/**
 * @brief Draws a 2D sprite based on the SpriteRendererComponent provided.
 * 
 * The function checks if there is a texture or animation textures in the component and draws accordingly. If neither are present, it draws a quad with no texture.
 * 
 * @param SRC Reference to the SpriteRendererComponent that contains all necessary information for drawing the sprite.
 */
void Renderer2D::DrawSprite(SpriteRendererComponent& SRC)
	{
		if (SRC.Texture)
		{
			DrawQuad(SRC.Texture, SRC.QuadProps);
		}

		if (SRC.AnimTextures.size() > 0)
		{
			SRC.AnimInstance.SetCurrentTexture(SRC.MovementStatus);
			SpriteSheetUtils::SetTexCoords(SRC.AnimInstance.GetCurrentTexture(), SRC.QuadProps, false);
			DrawQuad(SRC.AnimInstance.GetCurrentTexture(), SRC.QuadProps);
		}

		if (SRC.AnimTextures.size() == 0 && !SRC.Texture && !SRC.SubTexture)
		{
			DrawQuad(SRC.QuadProps);
		}

		if (SRC.SubTexture)
		{
			SpriteSheetUtils::SetTexCoords(SRC.SubTexture, SRC.QuadProps, false);
			DrawQuad(SRC.SubTexture, SRC.QuadProps);
		}
	}
	"/**\n * @brief Draws a single tile using the SpriteRendererComponent data.\n * \n * This function updates necessary buffers and statistics as needed, based on the details provided by the SpriteRendererComponent.\n * \n * @param SRC The SpriteRendererComponent containing all the information about the tile to be drawn.\n */"
void Renderer2D::DrawTile(const SpriteRendererComponent& SRC)
	{
		//SpriteSheetUtils::SetTexCoords(SRC.SubTexture, SRC.QuadProps, false);

		if (RenderCommand::s_GraphicsPipeline->GetData().TileIndexCounts[(size_t)SRC.TilesLayer] >= Renderer2DData::MaxIndexCount)
		{
			RenderCommand::s_GraphicsPipeline->NextBatch2D();
		}
		const Ref<Texture2D> texture = SRC.SubTexture->GetTexture();
		float TextureIndex = 0.f;

		if (texture != nullptr)
		{
			for (uint32_t i = 1; i < RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex; i++)
			{
				if (*RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[i].get() == *texture.get())
				{
					TextureIndex = (float)i;
					break;
				}
			}

			if (TextureIndex == 0.f)
			{
				TextureIndex = (float)RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlots[RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex] = texture;
				RenderCommand::s_GraphicsPipeline->GetData().TextureSlotIndex++;

			}
		}
		RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs[(size_t)SRC.TilesLayer] = RenderCommand::s_GraphicsPipeline->GetData().TileVertexBuffers[(size_t)SRC.TilesLayer]->CreateTile(RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs[(size_t)SRC.TilesLayer], SRC.QuadProps.TintColor, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, SRC.QuadProps.Size, SRC.QuadProps.Transform, SRC.QuadProps.TextureCoords, SRC.QuadProps.TilingFactor, TextureIndex, SRC.QuadProps.EntityID);
		RenderCommand::s_GraphicsPipeline->GetData().TileIndexCounts[(size_t)SRC.TilesLayer] += 6;
		RenderCommand::s_GraphicsPipeline->GetData().Stats.TileCount++;
	}
	
void Renderer2D::DrawString(const StringProperties& Props)
	{

		const auto& FontGeometry = Props.TextFont->GetMSDFData()->FontGeometry;
		const auto& Metrics = FontGeometry.getMetrics();

		Ref<Texture2D> FontAtlas = Props.TextFont->GetAtlasTexture();
		float TextureIndex = 0.f;
		if (FontAtlas != nullptr)
		{
			for (uint32_t i = 1; i < RenderCommand::s_GraphicsPipeline->GetData().AtlusSlotIndex; i++)
			{
				if (*RenderCommand::s_GraphicsPipeline->GetData().FontAtlasTextures[i].get() == *FontAtlas.get())
				{
					TextureIndex = (float)i;
					break;
				}
			}

			if (TextureIndex == 0.f)
			{
				TextureIndex = (float)RenderCommand::s_GraphicsPipeline->GetData().AtlusSlotIndex;
				RenderCommand::s_GraphicsPipeline->GetData().FontAtlasTextures[RenderCommand::s_GraphicsPipeline->GetData().AtlusSlotIndex] = FontAtlas;
				RenderCommand::s_GraphicsPipeline->GetData().AtlusSlotIndex++;

			}
		}

		double x = 0.0;
		double FSScale = (0.1 * Props.FontSize) / (Metrics.ascenderY - Metrics.descenderY);
		double y = 0.0;
		float LineHeightOffset = 0.f;


		for (size_t i = 0; i < Props.Text.size(); i++)
		{
			char Character = Props.Text[i];
			if (Character == '\r')
			{
				continue;
			}

			if (Character == '\n')
			{
				x = 0;
				y -= FSScale * Metrics.lineHeight + LineHeightOffset;
				continue;
			}
			auto Glyph = FontGeometry.getGlyph((uint32_t)Character);
			if (!Glyph)
			{
				Glyph = FontGeometry.getGlyph('?');
			}
			if (!Glyph)
			{
				return;
			}

			if (Character == '\t')
			{
				Glyph = FontGeometry.getGlyph(' ');
			}

			double al, ab, ar, at;
			Glyph->getQuadAtlasBounds(al, ab, ar, at);
			Vector2 TexCoordMin((float)al, (float)ab);
			Vector2 TexCoordMax((float)ar, (float)at);

			double pl, pb, pr, pt;
			Glyph->getQuadPlaneBounds(pl, pb, pr, pt);
			Vector2 QuadMin((float)pl, (float)pb);
			Vector2 QuadMax((float)pr, (float)pt);

			QuadMin *= (float)FSScale, QuadMax *= (float)FSScale;
			QuadMin += Vector2((float)x, (float)y);
			QuadMax += Vector2((float)x, (float)y);

			double TexelWidth = 1.f / (float)FontAtlas->GetWidth();
			double TexelHeight = 1.f / (float)FontAtlas->GetHeight();

			TexCoordMin.x *= (float)TexelWidth;
			TexCoordMin.y *= (float)TexelHeight;
			TexCoordMax.x *= (float)TexelWidth;
			TexCoordMax.y *= (float)TexelHeight;

			Vector4 Pos[4];
			Pos[0] = { QuadMin.x, QuadMin.y, 0.f,1.f };
			Pos[1] = { QuadMin.x, QuadMax.y, 0.f,1.f };
			Pos[2] = { QuadMax.x, QuadMax.y, 0.f,1.f };
			Pos[3] = { QuadMax.x, QuadMin.y, 0.f,1.f };

			Vector2 Coords[4];
			Coords[0] = TexCoordMin;
			Coords[1] = { TexCoordMin.x, TexCoordMax.y };
			Coords[2] = TexCoordMax;
			Coords[3] = { TexCoordMax.x, TexCoordMin.y };

			Matrix4D Transform  = Math::MakeTransform(Props.Position, Props.Rotation, {1.f});
			RenderCommand::s_GraphicsPipeline->GetData().TextVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Text"]->CreateText(RenderCommand::s_GraphicsPipeline->GetData().TextVertexBufferPtr, Transform, Pos, Props.Color, Coords, TextureIndex,0);
			RenderCommand::s_GraphicsPipeline->GetData().TextIndexCount += 6;
			RenderCommand::s_GraphicsPipeline->GetData().Stats.QuadCount++;

			if (i < Props.Text.size() - 1)
			{
				double Advance = Glyph->getAdvance();
				char NextCharacter = Props.Text[i + 1];
				FontGeometry.getAdvance(Advance, (uint32_t)Character, (uint32_t)NextCharacter);

				float KerningOffset = 0.f;
				x += FSScale * Advance + KerningOffset;
			}
		}

	}
	
void Renderer2D::DrawTileMapLayers(TileMapRendererComponent& TMRC, tmx_map* Map, std::vector<tmx_layer*> layers)
	{
		AGE_PROFILE_FUNCTION();
		if (!TMRC.bFirstPass)
		{
			return;
		}
		uint32_t Offset = 0;
		uint32_t* SquareIndices = new uint32_t[RenderCommand::s_GraphicsPipeline->GetData().MaxIndexCount];




		for (uint32_t i = 0; i < RenderCommand::s_GraphicsPipeline->GetData().MaxIndexCount; i += 6)
		{
			SquareIndices[i + 0] = Offset + 0; // 0|4|8
			SquareIndices[i + 1] = Offset + 1; // 1|5|9
			SquareIndices[i + 2] = Offset + 2; // 2|6|10

			SquareIndices[i + 3] = Offset + 2; // 2|6|10
			SquareIndices[i + 4] = Offset + 3; // 3|7|11
			SquareIndices[i + 5] = Offset + 0; // 0|4|8

			Offset += 4;
		}


		Ref<IndexBuffer> SquareIB;
		SquareIB = IndexBuffer::Create(SquareIndices, RenderCommand::s_GraphicsPipeline->GetData().MaxIndexCount);

		for (size_t i = 0; i < layers.size(); i++)
		{
			RenderCommand::s_GraphicsPipeline->GetData().TileVertexArrays.push_back(VertexArray::Create());


			RenderCommand::s_GraphicsPipeline->GetData().TileVertexArrays[i]->SetIndexBuffer(SquareIB);
			RenderCommand::s_GraphicsPipeline->GetData().TileVertexBuffers.push_back(VertexBuffer::Create(RenderCommand::s_GraphicsPipeline->GetData().MaxVertices * sizeof(TileVertex)));
			RenderCommand::s_GraphicsPipeline->GetData().TileVertexBuffers[i]->SetLayout({
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::Float4, "a_Color"},
				{ ShaderDataType::Float, "a_TextureID"},
				{ ShaderDataType::Float, "a_TilingFactor"},
				{ ShaderDataType::Int, "a_EntityID"}
				});

			RenderCommand::s_GraphicsPipeline->GetData().TileVertexArrays[i]->AddVertexBuffer(RenderCommand::s_GraphicsPipeline->GetData().TileVertexBuffers[i]);
			RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferBases.push_back(new TileVertex[RenderCommand::s_GraphicsPipeline->GetData().MaxVertices]);
			RenderCommand::s_GraphicsPipeline->GetData().TileIndexCounts.push_back(0);
		}

		RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs.resize(RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferBases.size());

		for (size_t i = 0; i < RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferBases.size(); i++)
		{
			RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs[i] = RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferBases[i];
		}

		for (int i = (int)layers.size() - 1; i >= 0 ; i--)
		{
			DrawTileMapLayer(TMRC, Map, layers[(size_t)i], i);
			
		}
		TMRC.bFirstPass = false;
		
	}
	"Draws a 2D tile map layer."
void Renderer2D::DrawTileMapLayer(TileMapRendererComponent& TMRC, tmx_map* Map, tmx_layer* layer, int Depth)
	{
		AGE_PROFILE_FUNCTION();
		if (layer->visible)
		{
			if (layer->type == L_GROUP)
			{
				DrawTileMapLayer(TMRC, Map, layer->content.group_head, 0);
			}
			else if (layer->type == L_OBJGR)
			{
				CoreLogger::Assert(false, "Not Implemented!");
			}
			else if (layer->type == L_IMAGE)
			{
				//Ref<Texture2D> Tile = Texture2D::Create(layer->content.image);
				//Entity E = TMRC.ActiveScene->CreateEntity("Tile " + TMRC.TileCount);
				//E.AddComponent<SpriteRendererComponent>();
				//E.GetComponent<SpriteRendererComponent>().Texture = Tile;
				//DrawSprite(E.GetComponent<SpriteRendererComponent>());
				//TMRC.TileCount++;

			}
			else if (layer->type == L_LAYER)
			{
				uint32_t i, j;
				uint32_t gid, x, y, w, h, flags;
				uint32_t ID;
				double op;
				tmx_tileset* ts;
				tmx_image* im;
				void* image;
				op = layer->opacity;
				for (i = 0; i < Map->height; i++)
				{
					for (j = 0; j < Map->width; j++)
					{
						gid = (layer->content.gids[(i * Map->width) + j]) & TMX_FLIP_BITS_REMOVAL;
						if (Map->tiles[gid] != NULL)
						{
							ts = Map->tiles[gid]->tileset;
							im = Map->tiles[gid]->image;
							x = Map->tiles[gid]->ul_x;
							y = Map->tiles[gid]->ul_y;
							ID = Map->tiles[gid]->id;
							w = ts->tile_width;
							h = ts->tile_height;

							if (im)
							{
								image = im->resource_image;
							}
							else
							{
								image = ts->image->resource_image;
							}
							//flags = (layer->content.gids[(i * Map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
							if (image)
							{
								std::string Name = "Tile " + std::to_string(j) + ":" + std::to_string(i);
								Entity E = TMRC.ActiveScene->CreateEntity(Name);
								E.AddComponent<SpriteRendererComponent>();
								E.GetComponent<SpriteRendererComponent>().TileID = (int)ID;
								E.GetComponent<SpriteRendererComponent>().bTile = true;
								E.GetComponent<SpriteRendererComponent>().TilesLayer = Depth;
								E.GetComponent<SpriteRendererComponent>().SubTexture = TMRC.TileTextures[ID];
								E.GetComponent<SpriteRendererComponent>().TileLocation = TMRC.TileLocs[ID];
								E.GetComponent<SpriteRendererComponent>().TileWidth = (float)TMRC.TileMap->tiles[1]->tileset->tile_width;
								E.GetComponent<SpriteRendererComponent>().TileHeight = (float)TMRC.TileMap->tiles[1]->tileset->tile_height;
								E.GetComponent<SpriteRendererComponent>().Color = { 1.f,1.f,1.f,(float)op };
								E.GetComponent<SpriteRendererComponent>().QuadProps.TintColor = E.GetComponent<SpriteRendererComponent>().Color;
								SpriteSheetUtils::SetTexCoords(TMRC.TileTextures[ID], E.GetComponent<SpriteRendererComponent>().QuadProps);
								//RenderCommand::s_GraphicsPipeline->GetData().CoordBuffer.Coords.push_back(E.GetComponent<SpriteRendererComponent>().QuadProps.TextureCoords);
								E.GetComponent<TransformComponent>().Translation = { (float)j,(float)(Map->height - i),(float)Depth -10.f}; //Depth == 0 ? 
								E.GetComponent<TransformComponent>().Scale = { 1.f,1.f,1.f };
								TMRC.IDs.push_back(E.GetUUID());
								DrawTile(E.GetComponent<SpriteRendererComponent>());
							}

						}
					}
				}
			}
		}
	}
	/**
 * @brief Get the statistics of the 2D renderer.
 *
 * This function retrieves and returns the current statistics of the 2D renderer, including rendering time, draw calls, etc.
 *
 * @return A Statistics object containing the current stats of the 2D renderer.
 */
Statistics Renderer2D::GetStats()
	{
		return RenderCommand::s_GraphicsPipeline->GetData().Stats;
	}
	/** 
 * @brief This function returns the current line width.
 * @return A float representing the current line width.
 */
float Renderer2D::GetLineWidth()
	{
		return RenderCommand::s_GraphicsPipeline->GetData().LineWidth;
	}
	/**
 * @brief Set the line width for rendering.
 *
 * This function sets the line width used in rendering operations. The actual effect may vary depending on the specific renderer and its configuration.
 *
 * @param Width The new line width to be set. Must be a positive value.
 */
void Renderer2D::SetLineWidth(float Width)
	{
		RenderCommand::s_GraphicsPipeline->GetData().LineWidth = Width;
	}
}
