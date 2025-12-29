#include "AGEpch.hpp"

#include "Render/Public/Renderer2D.h"
#include "Render/Public/RenderCommand.h"
#include "Render/Public/MSDFData.h"
#include "Render/Public/VertexArray.h"
#include "Render/Public/Shader.h"
#include "Scene/Public/Entity.h"
#include "Platform/OpenGL/Public/OpenGLShader.h"
#include "Platform/OpenGL/Public/OpenGLTexture.h"
#include "Utils/Public/WindowsUtils.h"
#include "Sprite/Public/SpriteAPI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <rttr/registration>

RTTR_REGISTRATION
{
	rttr::registration::method("Draw String", &AGE::Renderer2D::DrawString);
}

namespace AGE
{

	void Renderer2D::Init()
	{

	}
		

	void Renderer2D::Shutdown()
	{

	}
	
	void Renderer2D::BeginScene(const Camera& Camera, const Matrix4D& Transform)
	{
		AGE_PROFILE_FUNCTION();
		RenderCommand::s_GraphicsPipeline->StartBatch2D();
	}
	void Renderer2D::BeginScene(const EditorCamera& Camera)
	{
		AGE_PROFILE_FUNCTION();

		Matrix4D WVPM = (Camera.GetProjection() * Camera.GetViewMatrix()) * Camera.GetWorldMatrix();
		RenderCommand::s_GraphicsPipeline->GetData().CameraUniformBuffer->SetData(&WVPM, sizeof(Renderer2DData::CameraData));
		RenderCommand::s_GraphicsPipeline->StartBatch2D();
	}
	void Renderer2D::EndScene()
	{
		AGE_PROFILE_FUNCTION();

		RenderCommand::s_GraphicsPipeline->Flush2D();
	}
	void Renderer2D::Flush()
	{
		RenderCommand::s_GraphicsPipeline->Flush2D();		
	}

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

	void Renderer2D::DrawLine(const Vector3& Pos0, const Vector3& Pos1, const Vector4& Color, int EntityID)
	{
		RenderCommand::s_GraphicsPipeline->GetData().LineVertexBufferPtr = RenderCommand::s_GraphicsPipeline->GetData().VertexBuffers["Line"]->CreateLine(RenderCommand::s_GraphicsPipeline->GetData().LineVertexBufferPtr, Color, Pos0, Pos1, EntityID);

		RenderCommand::s_GraphicsPipeline->GetData().LineVertexCount += 2;
	}

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
	void Renderer2D::DrawTile(const SpriteRendererComponent& SRC)
	{
		//SpriteSheetUtils::SetTexCoords(SRC.SubTexture, SRC.QuadProps, false);

		if (RenderCommand::s_GraphicsPipeline->GetData().TileIndexCounts[SRC.TilesLayer] >= Renderer2DData::MaxIndexCount)
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
		RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs[SRC.TilesLayer] = RenderCommand::s_GraphicsPipeline->GetData().TileVertexBuffers[SRC.TilesLayer]->CreateTile(RenderCommand::s_GraphicsPipeline->GetData().TileVertexBufferPtrs[SRC.TilesLayer], SRC.QuadProps.TintColor, RenderCommand::s_GraphicsPipeline->GetData().QuadVertexPositions, SRC.QuadProps.Size, SRC.QuadProps.Transform, SRC.QuadProps.TextureCoords, SRC.QuadProps.TilingFactor, TextureIndex, SRC.QuadProps.EntityID);
		RenderCommand::s_GraphicsPipeline->GetData().TileIndexCounts[SRC.TilesLayer] += 6;
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
			auto Glyph = FontGeometry.getGlyph(Character);
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

			QuadMin *= FSScale, QuadMax *= FSScale;
			QuadMin += Vector2(x, y);
			QuadMax += Vector2(x, y);

			float TexelWidth = 1.f / FontAtlas->GetWidth();
			float TexelHeight = 1.f / FontAtlas->GetHeight();

			TexCoordMin.x *= TexelWidth;
			TexCoordMin.y *= TexelHeight;
			TexCoordMax.x *= TexelWidth;
			TexCoordMax.y *= TexelHeight;

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
				FontGeometry.getAdvance(Advance, Character, NextCharacter);

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

		for (int i = 0; i < layers.size(); i++)
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
			DrawTileMapLayer(TMRC, Map, layers[i], i);
			
		}
		TMRC.bFirstPass = false;
		
	}
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
				AGE_CORE_ASSERT(false, "Not Implemented!");
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
				int ID;
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
							flags = (layer->content.gids[(i * Map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
							if (image)
							{
								std::string Name = "Tile " + std::to_string(j) + ":" + std::to_string(i);
								Entity E = TMRC.ActiveScene->CreateEntity(Name);
								E.AddComponent<SpriteRendererComponent>();
								E.GetComponent<SpriteRendererComponent>().TileID = ID;
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
	Statistics Renderer2D::GetStats()
	{
		return RenderCommand::s_GraphicsPipeline->GetData().Stats;
	}
	float Renderer2D::GetLineWidth()
	{
		return RenderCommand::s_GraphicsPipeline->GetData().LineWidth;
	}
	void Renderer2D::SetLineWidth(float Width)
	{
		RenderCommand::s_GraphicsPipeline->GetData().LineWidth = Width;
	}
}
