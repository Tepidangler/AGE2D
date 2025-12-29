#pragma once
#include "Core/Public/Core.h"
#include "Structs/Public/DataStructures.h"
#include "Render/Public/RenderBuffer.h"
#include "Texture/Public/Texture.h"
#include "Render/Public/Shader.h"
#include "Render/Public/VertexArray.h"


namespace AGE
{
	struct Renderer2DData
	{
		static const uint32_t MaxQuadCount = 20000;
		static const uint32_t MaxVertices = MaxQuadCount * 4;
		static const uint32_t MaxIndexCount = MaxQuadCount * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> QuadShader;
		Ref<Texture2D> WhiteTexture;
		ShaderLibrary ShaderLibrary;

		uint32_t QuadIndexCount = 0;
		Vertex* QuadVertexBufferBase = nullptr;
		Vertex* QuadVertexBufferPtr = nullptr;

		Ref<VertexArray> CircleVertexArray;
		Ref<Shader> CircleShader;

		uint32_t CircleIndexCount = 0;
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;


		Ref<VertexArray> LineVertexArray;
		Ref<Shader> LineShader;

		uint32_t LineVertexCount = 0;
		LineVertex* LineVertexBufferBase = nullptr;
		LineVertex* LineVertexBufferPtr = nullptr;
		float LineWidth = 2.f;

		Ref<VertexArray> TextVertexArray;
		Ref<Shader> TextShader;

		uint32_t TextIndexCount = 0;
		TextVertex* TextVertexBufferBase = nullptr;
		TextVertex* TextVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> FontAtlasTextures;

		std::vector<Ref<VertexArray>> TileVertexArrays;
		std::vector<Ref<VertexBuffer>> TileVertexBuffers;
		Ref<Shader> TileShader;

		std::vector<uint32_t> TileIndexCounts;
		std::vector<TileVertex*> TileVertexBufferBases;
		std::vector<TileVertex*> TileVertexBufferPtrs;


		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; //0 Should ALWAYS be the white texture
		uint32_t AtlusSlotIndex = 1; //0 Should ALWAYS be the Default Atlus

		Vector4 QuadVertexPositions[4];


		struct CameraData
		{
			Matrix4D CameraViewProjection;
		};

		struct TexCoordData
		{
			std::vector<Vector2*> Coords;
		};

		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;

		TexCoordData CoordBuffer;
		Ref<UniformBuffer> TexCoordUniformBuffer;


		std::unordered_map<std::string, Ref<VertexBuffer>> VertexBuffers;
		Ref<VertexBuffer> GetVertexBuffer(const std::string& Name)
		{
			return VertexBuffers[Name]; 
		}


		Statistics Stats;
	};

	class Pipeline
	{
	public:

		virtual void Init() = 0;
		virtual void StartBatch2D() = 0;
		virtual void NextBatch2D() = 0;
		virtual void Flush2D() = 0;

		virtual Renderer2DData& GetData() = 0;


		virtual void ResetStats() =0;

		virtual Statistics& GetStats() = 0;

		template<typename T>
		T* As();

		static Scope<Pipeline> Create();
	};

}