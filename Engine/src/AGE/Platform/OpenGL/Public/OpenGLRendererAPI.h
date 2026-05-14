#pragma once
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public: //functions

		/**
 * @brief Default destructor for the OpenGLRendererAPI class.
 *
 * This function is responsible for releasing any resources that were acquired during the lifetime of an instance of this class. It does not perform any operations on the actual objects being rendered, but rather cleans up any internal data structures or handles used by the renderer.
 *
 * @return void
 */
/**
 * @brief Default destructor for the OpenGLRendererAPI class.
 *
 * This function is responsible for freeing any resources that were allocated during the lifetime of an instance of this class. It does not perform any operations on the state of the renderer itself, but rather cleans up any associated memory or other resources.
 * 
 * @return void
 */
~OpenGLRendererAPI() =default;
		void Init() override;
		void SetClearColor(const Vector4 Color) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height) override;
		void Clear() override;

		void Flush() override;
		/**
 * @brief This function is used to draw indexed elements in a graphics context.
 * 
 * The function takes three parameters: the number of indices (IndexCount), the starting index (IndexStart), and the starting vertex position (VertexStart). It does not return anything, hence void return type.
 * 
 * @param IndexCount Number of indices to be drawn.
 * @param IndexStart Starting index for drawing elements.
 * @param VertexStart The starting vertex position.
 * 
 * @return Nothing is returned as the function is declared with 'override' keyword, indicating it overrides a virtual function in base class.
 */
/**
 * @brief This function draws a set of vertices using index buffers.
 * @param IndexCount The number of indices to draw from the index buffer.
 * @param IndexStart The starting index in the index buffer.
 * @param VertexStart The vertex offset within the vertex buffer.
 * @return void
 */
void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart) override {}
		void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount) override;
		void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		void SetLineWidth(float Width) override;


		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		void Submit() override;
		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		void Present() override;
	};
}