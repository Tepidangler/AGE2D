#pragma once
#include "RenderAPI.h"
#include "Render/Public/Pipeline.h"



namespace AGE
{
	class RenderCommand
	{
	public:

		static void Init();
		static void SetClearColor(const Vector4 Color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height);
		static void Clear();
		static void Submit();
		static void Present();
		static void Flush();
		static void ResetStats();
		/**
 * @brief This function returns the current renderer API being used by the application.
 * @return A reference to the current renderer API (either RendererAPI::OpenGL, RendererAPI::Vulkan or RendererAPI::Unknown).
 */
/**
 * @brief This function returns the current renderer API being used by the application.
 * @return A reference to the current renderer API (either OpenGL, DirectX or Vulkan).
 */
static RendererAPI::API& GetCurrentRendererAPI() { return s_CurrentAPI; }

		//static void ChangeRendererAPI(const RendererAPI::API Renderer) { s_RendererAPI.reset();  s_RendererAPI = RendererAPI::Create(); }

		/**
 * @brief Draw a set of indexed vertices.
 * 
 * This function is used to draw a subset of the vertices in the vertex buffer using indices from the index buffer.
 * The number of indices to be drawn, starting index and starting vertex position are specified as parameters.
 * 
 * @param IndexCount Number of indices to be drawn.
 * @param IndexStart Starting index location in the index buffer.
 * @param VertexStart Starting vertex position in the vertex buffer.
 */
/**
 * @brief DrawIndexed is a function that draws indexed vertices.
 * 
 * This function uses the RendererAPI to draw indexed vertices on the screen. The number of indices to be drawn, their starting position and the starting vertex are provided as parameters.
 * 
 * @param IndexCount The number of indices to be drawn.
 * @param IndexStart The starting position of the indices in the index buffer.
 * @param VertexStart The starting vertex for the draw call.
 * 
 * @return void
 */
inline static void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart)
		{
			s_RendererAPI->DrawIndexed(IndexCount, IndexStart, VertexStart);
		}
		/**
 * @brief DrawIndexed is a function that renders the vertices of a Vertex Array using indices.
 * 
 * @param VertexArray A reference to a constant Vertex Array object. This represents the vertex data to be rendered.
 * @param IndexCount An unsigned integer value representing the number of indices to draw. If no index count is specified, it defaults to 0 and all vertices are drawn.
 */
/**
 * @brief DrawIndexed function is used to render a set of vertices using indices.
 * 
 * This function takes in a constant reference to a VertexArray and an unsigned integer for the index count. If no index count is provided, it defaults to 0. The function uses the RendererAPI's DrawIndexed method to perform the rendering.
 * 
 * @param VertexArray A constant reference to the VertexArray that contains the vertices to be rendered.
 * @param IndexCount An unsigned integer representing the number of indices in the index buffer. Default is 0.
 */
inline static void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount = 0)
		{
			s_RendererAPI->DrawIndexed(VertexArray, IndexCount);
		}	

		/**
 * @brief Draw lines using the specified vertex array and count.
 * 
 * This function uses the Renderer API to draw lines based on the provided vertex array and count. If no vertex count is provided (0), it defaults to drawing all vertices in the array.
 * 
 * @param VertexArray A reference to a constant Vertex Array object representing the data for the lines to be drawn.
 * @param VertexCount An unsigned integer value indicating the number of vertices to draw from the vertex array. If not provided, it defaults to drawing all vertices in the array.
 * 
 * @return void
 */
/**
 * @brief Draw lines using the specified vertex array and count.
 * 
 * This function uses the Renderer API to draw lines based on the provided vertex array and count. If no count is provided (0), it will default to drawing all vertices in the array.
 * 
 * @param VertexArray A reference to a constant Vertex Array object that contains the data for the lines to be drawn.
 * @param VertexCount The number of vertices to draw from the vertex array. If not provided (0), it will default to drawing all vertices in the array.
 */
inline static void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount = 0)
		{
			s_RendererAPI->DrawLines(VertexArray, VertexCount);
		}
		/**
 * @brief DrawStrips is a function that draws vertex strips using the Renderer API.
 * 
 * @param[in] VertexArray A reference to a constant Vertex Array object which represents the data of the vertices to be drawn.
 * @param[in] VertexCount An unsigned integer value representing the number of vertices to draw. If no value is provided, it defaults to 0.
 */
/**
 * @brief DrawStrips is a function that draws vertex strips using the Renderer API.
 * 
 * @param[in] VertexArray A reference to a constant VertexArray object. This represents the vertex array to be drawn.
 * @param[in] VertexCount An unsigned integer value representing the number of vertices in the vertex array. If no value is provided, it defaults to 0.
 */
inline static void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t VertexCount = 0)
		{
			s_RendererAPI->DrawStrips(VertexArray, VertexCount);
		}

		/**
 * @brief This function sets the line width for rendering purposes.
 * 
 * @param Width The new line width to be set.
 */
/**
 * @brief This function sets the line width for rendering purposes.
 * 
 * @param Width The new line width to be set.
 */
inline static void SetLineWidth(float Width)
		{
			s_RendererAPI->SetLineWidth(Width);
		}
	private:

		static Scope<RendererAPI> s_RendererAPI;

		static Ref<Pipeline> s_GraphicsPipeline;

		static RendererAPI::API s_CurrentAPI;

		friend class Renderer2D;
		friend class Renderer3D;
	};
}