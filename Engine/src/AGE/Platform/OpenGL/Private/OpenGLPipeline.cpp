#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLPipeline.h"
#include "Render/Public/RenderCommand.h"
#include "Assets/Public/AssetManager.h"
#include <glm/glm.hpp>

#include "App.h"
#include "Debug/Public/Instrumentor.h"
namespace AGE
{
	extern std::filesystem::path g_EditorAssetPath;

	COMMENT:
/**
 * @brief OpenGLPipeline is a class that represents an OpenGL pipeline. It provides methods for setting up and managing the pipeline.
 */
CONFIDENCE: 1.0;

/**
 * @brief OpenGLPipeline is a class that represents an OpenGL pipeline. 
 * It provides methods for setting up and managing the rendering process in an OpenGL context.
 */
OpenGLPipeline::OpenGLPipeline()
	{
	}
	/**
 * @brief Destructor for the OpenGLPipeline class.
 * 
 * This function is responsible for cleaning up memory that was dynamically allocated during the lifetime of an instance of this class. It deletes four arrays (QuadVertexBufferBase, CircleVertexBufferBase, LineVertexBufferBase, TextVertexBufferBase) and clears a vector (TileVertexBufferBases).
 * 
 * @return void
 */
/**
 * @brief Destructor for the OpenGLPipeline class. It is responsible for freeing up memory that was allocated dynamically during its lifetime.
 * 
 * This destructor deletes four arrays (QuadVertexBufferBase, CircleVertexBufferBase, LineVertexBufferBase and TextVertexBufferBase) which were previously allocated using new[]. Additionally, it clears the TileVertexBufferBases vector to free up memory.
 */
OpenGLPipeline::~OpenGLPipeline()
	{
		AGE_PROFILE_FUNCTION();

		delete[] m_Data.QuadVertexBufferBase;
		delete[] m_Data.CircleVertexBufferBase;
		delete[] m_Data.LineVertexBufferBase;
		delete[] m_Data.TextVertexBufferBase;
		m_Data.TileVertexBufferBases.clear();
	}
	

void OpenGLPipeline::Init()
	{
		//2D Init

		CoreLogger::Info("Initializing OpenGL Pipeline");
		m_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);

		m_Data.QuadVertexArray = VertexArray::Create();

		m_Data.VertexBuffers["Quad"] = VertexBuffer::Create(m_Data.MaxVertices * sizeof(Vertex));
		m_Data.VertexBuffers["Quad"]->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float, "a_TextureID"},
			{ ShaderDataType::Float, "a_TilingFactor"},
			{ ShaderDataType::Int, "a_EntityID"}

			});

		m_Data.QuadVertexArray->AddVertexBuffer(m_Data.VertexBuffers["Quad"]);

		m_Data.QuadVertexBufferBase = new Vertex[m_Data.MaxVertices];


		uint32_t Offset = 0;

		uint32_t* PrimIndices = new uint32_t[m_Data.MaxIndexCount];
		for (uint32_t i = 0; i < m_Data.MaxIndexCount; i += 6)
		{
			//Front
			PrimIndices[i + 0] = Offset + 0;
			PrimIndices[i + 1] = Offset + 1;
			PrimIndices[i + 2] = Offset + 2;

			PrimIndices[i + 3] = Offset + 2;
			PrimIndices[i + 4] = Offset + 3;
			PrimIndices[i + 5] = Offset + 0;

			Offset += 4;
		}

		Ref<IndexBuffer> PrimIB;
		PrimIB = IndexBuffer::Create(PrimIndices, m_Data.MaxIndexCount);
		m_Data.QuadVertexArray->SetIndexBuffer(PrimIB);
		delete[] PrimIndices;

		m_Data.CircleVertexArray = VertexArray::Create();
		m_Data.VertexBuffers["Circle"] = VertexBuffer::Create(m_Data.MaxVertices * sizeof(CircleVertex));
		m_Data.VertexBuffers["Circle"]->SetLayout({
			{ ShaderDataType::Float3, "a_WorldPosition" },
			{ ShaderDataType::Float3, "a_LocalPosition" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float, "a_Thickness"},
			{ ShaderDataType::Float, "a_Fade"},
			{ ShaderDataType::Int, "a_EntityID"}

			});

		m_Data.CircleVertexArray->AddVertexBuffer(m_Data.VertexBuffers["Circle"]);
		m_Data.CircleVertexArray->SetIndexBuffer(PrimIB);

		m_Data.CircleVertexBufferBase = new CircleVertex[m_Data.MaxVertices];

		m_Data.LineVertexArray = VertexArray::Create();
		m_Data.VertexBuffers["Line"] = VertexBuffer::Create(m_Data.MaxVertices * sizeof(LineVertex));
		m_Data.VertexBuffers["Line"]->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Int, "a_EntityID"}

			});

		m_Data.LineVertexArray->AddVertexBuffer(m_Data.VertexBuffers["Line"]);
		m_Data.LineVertexArray->SetIndexBuffer(PrimIB);

		m_Data.LineVertexBufferBase = new LineVertex[m_Data.MaxVertices];

		m_Data.TextVertexArray = VertexArray::Create();

		m_Data.VertexBuffers["Text"] = VertexBuffer::Create(m_Data.MaxVertices * sizeof(TextVertex));
		m_Data.VertexBuffers["Text"]->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float, "a_TexID"},
			{ShaderDataType::Int, "a_EntityID"}

			});

		m_Data.TextVertexArray->AddVertexBuffer(m_Data.VertexBuffers["Text"]);
		m_Data.TextVertexArray->SetIndexBuffer(PrimIB);
		m_Data.TextVertexBufferBase = new TextVertex[m_Data.MaxVertices];
		
		GenerateDefaultTextures();

#ifdef __clang__
		int32_t Samplers[32];
#else
		int32_t Samplers[m_Data.MaxTextureSlots];
#endif
		for (int i = 0; i < m_Data.MaxTextureSlots; i++)
		{
			Samplers[i] = i;
		}
		AppConfig& AppConfigRef = App::Get().GetAppConfig();
		AssetManager::Get().LoadShader(AppConfigRef.EditorAssetPath.string() +"Shaders/GLSL/Vertex/QuadShader.glsl");
		AssetManager::Get().LoadShader(AppConfigRef.EditorAssetPath.string() +"Shaders/GLSL/Vertex/CircleShader.glsl");
		AssetManager::Get().LoadShader(AppConfigRef.EditorAssetPath.string() +"Shaders/GLSL/Vertex/LineShader.glsl");
		AssetManager::Get().LoadShader(AppConfigRef.EditorAssetPath.string() +"Shaders/GLSL/Vertex/TextShader.glsl");
		AssetManager::Get().LoadShader(AppConfigRef.EditorAssetPath.string() +"Shaders/GLSL/Vertex/TileShader.glsl");

		m_Data.QuadShader = AssetManager::Get().GetShader("QuadShader");
		m_Data.CircleShader = AssetManager::Get().GetShader("CircleShader");
		m_Data.LineShader = AssetManager::Get().GetShader("LineShader");
		m_Data.TextShader = AssetManager::Get().GetShader("TextShader");
		m_Data.TileShader = AssetManager::Get().GetShader("TileShader");
		m_Data.QuadShader->SetInt("u_Textures", 0, Samplers, m_Data.MaxTextureSlots);
		m_Data.TileShader->SetInt("u_Textures", 0, Samplers, m_Data.MaxTextureSlots);

		m_Data.TextureSlots[0] = m_Data.WhiteTexture;
		m_Data.FontAtlasTextures[0] = AGEFont::GetDefault()->GetAtlasTexture();


		m_Data.QuadVertexPositions[0] = { .5f, .5f, 0.f, 1.f };
		m_Data.QuadVertexPositions[1] = { .5f, -.5f, 0.f, 1.f };
		m_Data.QuadVertexPositions[2] = { -.5f, -.5f, 0.f, 1.f };
		m_Data.QuadVertexPositions[3] = { -.5f, .5f, 0.f, 1.f };
	}
	
/**
 * @brief Resets the buffers for rendering operations in the OpenGLPipeline class.
 * 
 * @param None
 * 
 * @return None
 */
void OpenGLPipeline::StartBatch2D()
	{
		m_Data.QuadIndexCount = 0;
		m_Data.QuadVertexBufferPtr = m_Data.QuadVertexBufferBase;

		m_Data.CircleIndexCount = 0;
		m_Data.CircleVertexBufferPtr = m_Data.CircleVertexBufferBase;

		m_Data.LineVertexCount = 0;
		m_Data.LineVertexBufferPtr = m_Data.LineVertexBufferBase;

		m_Data.TextIndexCount = 0;
		m_Data.TextVertexBufferPtr = m_Data.TextVertexBufferBase;

		if (m_Data.TileVertexBufferBases.size() > 0)
		{
			for (size_t i = 0; i < m_Data.TileVertexBufferBases.size(); i++)
			{
				m_Data.TileIndexCounts[i] = 0;
				m_Data.TileVertexBufferPtrs[i] = m_Data.TileVertexBufferBases[i];
			}
		}

		m_Data.TextureSlotIndex = 1;
		m_Data.AtlusSlotIndex = 1;
	}
	/** 
 * @brief This function is used to start the next batch of 2D rendering. It first flushes any existing 2D data by calling Flush2D(), and then starts a new batch with StartBatch2D().
 * 
 * @return void
 */
/** 
 * @brief This function is used to prepare for the next batch of 2D rendering. It first flushes any existing 2D data by calling Flush2D(), and then starts a new batch with StartBatch2D().
 * 
 * @return void
 */
void OpenGLPipeline::NextBatch2D()
	{
		Flush2D();
		StartBatch2D();
	}
	

void OpenGLPipeline::Flush2D()
	{
		if (m_Data.QuadIndexCount)
		{
			uint32_t DataSize = (uint32_t)((uint8_t*)m_Data.QuadVertexBufferPtr - (uint8_t*)m_Data.QuadVertexBufferBase);
			m_Data.VertexBuffers["Quad"]->AddDataToBuffer(m_Data.QuadVertexBufferBase, DataSize);

			for (uint32_t i = 0; i < m_Data.TextureSlotIndex; i++)
			{
				if (m_Data.TextureSlots[i])
				{
					m_Data.TextureSlots[i]->Bind(i);
				}
			}

			m_Data.QuadShader->Bind();
			RenderCommand::DrawIndexed(m_Data.QuadVertexArray, m_Data.QuadIndexCount);
			m_Data.Stats.DrawCalls++;
		}

		if (m_Data.CircleIndexCount)
		{
			uint32_t DataSize = (uint32_t)((uint8_t*)m_Data.CircleVertexBufferPtr - (uint8_t*)m_Data.CircleVertexBufferBase);
			m_Data.VertexBuffers["Circle"]->AddDataToBuffer(m_Data.CircleVertexBufferBase, DataSize);

			m_Data.CircleShader->Bind();
			RenderCommand::DrawIndexed(m_Data.CircleVertexArray, m_Data.CircleIndexCount);
			m_Data.Stats.DrawCalls++;
		}

		if (m_Data.LineVertexCount)
		{
			uint32_t DataSize = (uint32_t)((uint8_t*)m_Data.LineVertexBufferPtr - (uint8_t*)m_Data.LineVertexBufferBase);
			m_Data.VertexBuffers["Line"]->AddDataToBuffer(m_Data.LineVertexBufferBase, DataSize);

			m_Data.LineShader->Bind();
			RenderCommand::SetLineWidth(m_Data.LineWidth);
			RenderCommand::DrawLines(m_Data.LineVertexArray, m_Data.LineVertexCount);
			m_Data.Stats.DrawCalls++;
		}

		if (m_Data.TextIndexCount)
		{
			uint32_t DataSize = (uint32_t)((uint8_t*)m_Data.TextVertexBufferPtr - (uint8_t*)m_Data.TextVertexBufferBase);
			m_Data.VertexBuffers["Text"]->AddDataToBuffer(m_Data.TextVertexBufferBase, DataSize);

			[[maybe_unused]] auto Buffer = m_Data.TextVertexBufferBase;
			for (size_t i = 0; i < m_Data.FontAtlasTextures.size(); i++)
			{
				if (m_Data.FontAtlasTextures[i])
				{
					m_Data.FontAtlasTextures[i]->Bind((uint32_t)i);
				}

			}

			m_Data.TextShader->Bind();
			RenderCommand::SetLineWidth(m_Data.LineWidth);
			RenderCommand::DrawIndexed(m_Data.TextVertexArray, m_Data.TextIndexCount);
			m_Data.Stats.DrawCalls++;
		}
		for (size_t i = 0; i < m_Data.TileVertexArrays.size(); i++)
		{
			if (m_Data.TileIndexCounts[i])
			{
				uint32_t DataSize = (uint32_t)((uint8_t*)m_Data.TileVertexBufferPtrs[i] - (uint8_t*)m_Data.TileVertexBufferBases[i]);
				m_Data.TileVertexBuffers[i]->AddDataToBuffer(m_Data.TileVertexBufferBases[i], DataSize);



				for (uint32_t j = 0; j < m_Data.TextureSlotIndex; j++)
				{
					if (m_Data.TextureSlots[j])
					{
						m_Data.TextureSlots[j]->Bind(j);
					}
				}
				RenderCommand::DrawIndexed(m_Data.TileVertexArrays[i], m_Data.TileIndexCounts[i]);
				m_Data.Stats.DrawCalls++;



			}
		}
		m_Data.TileShader->Bind();
	}

	/**
 * @brief Get the Renderer 2D data for this pipeline instance.
 *
 * This function returns a reference to the Renderer2DData object that is used by this OpenGLPipeline instance. The returned data can be modified, allowing changes to be reflected across all instances of OpenGLPipeline that use the same Renderer2DData.
 *
 * @return A reference to the Renderer2DData object for this pipeline instance.
 */
COMMENT:
/** 
 * @brief This function returns a reference to the Renderer2DData object used by this class.
 * @return A reference to the Renderer2DData object.
 */
CONFIDENCE: 1.0;

Renderer2DData& OpenGLPipeline::GetData()
	{
		return m_Data;
	}
	/**
 * @brief Resets the statistics of the OpenGL pipeline.
 *
 * This function sets all fields in the Statistics structure to zero using memset(). It effectively resets the counters for various 
 * statistics tracked by the OpenGL pipeline.
 *
 * @return void
 */
/**
 * @brief Resets the statistics of the OpenGL pipeline.
 *
 * This function sets all fields in the Statistics structure to zero using memset(). It effectively resets the counters and other statistics that track performance over time.
 * 
 * @return void
 */
void OpenGLPipeline::ResetStats()
	{
		memset(&m_Data.Stats, 0, sizeof(Statistics));
	}
	/**
 * @brief Get the statistics of the OpenGL Pipeline.
 * 
 * This function returns a reference to the statistics object that holds information about the performance and usage of the OpenGL Pipeline.
 * The returned Statistics object can be used for various purposes such as profiling, debugging or optimizing the rendering process.
 *
 * @return A reference to the Statistics object.
 */
/**
 * @brief Get the statistics of the OpenGL Pipeline.
 * 
 * This function returns a reference to the statistics object that holds information about the performance and usage of the OpenGL pipeline.
 * 
 * @return A reference to the Statistics object.
 */
Statistics& OpenGLPipeline::GetStats()
	{
		return m_Data.Stats;
	}

	/**
 * @brief GenerateDefaultTextures is a function that creates and initializes default textures for the OpenGLPipeline object.
 * 
 * This function generates a white texture with full alpha channel (0xffffffff) and sets it as the WhiteTexture member of the m_Data struct. The Texture2D::Create() function is used to create the texture, and the SetData() method is called on the created texture to initialize its data.
 * 
 * @return void No return value.
 */
/**
 * @brief GenerateDefaultTextures is a function that generates default textures for the OpenGLPipeline class.
 * 
 * This function creates a white texture and sets it as the default texture data member of the OpenGLPipeline object. The white texture is represented by a 32-bit unsigned integer with all its bits set to 1, which corresponds to color (255, 255, 255, 255) in RGBA format.
 * 
 * @return void No return value.
 */
void OpenGLPipeline::GenerateDefaultTextures()
	{
		uint32_t WhiteTexData = 0xffffffff;
		m_Data.WhiteTexture = Texture2D::Create(TextureSpecification());
		m_Data.WhiteTexture->SetData(&WhiteTexData, sizeof(uint32_t));
	}

	template<>
	/**
 * @brief This function returns a pointer to the OpenGLPipeline object.
 *
 * The function is used to cast the current instance of Pipeline to an OpenGLPipeline type. It does this by returning 'this' as a void pointer, then casting it back to an OpenGLPipeline pointer. 
 * This allows for polymorphism in OpenGL operations where different types of objects can respond differently to the same function calls.
 *
 * @return A pointer to the OpenGLPipeline object. If no such object exists, returns nullptr.
 */
/**
 * @brief This function returns a pointer to an OpenGLPipeline object.
 *
 * The function is used to convert the current object into an OpenGLPipeline type. It does this by returning 'this' casted as an OpenGLPipeline*. 
 *
 * @return An instance of OpenGLPipeline.
 */
OpenGLPipeline* Pipeline::As()
	{
		return (OpenGLPipeline*)this;
	}
}