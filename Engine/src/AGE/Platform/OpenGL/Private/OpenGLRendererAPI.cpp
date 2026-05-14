#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLRendererAPI.h"

#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
namespace AGE
{
	/**
 * @brief Initializes the OpenGL Renderer API with various settings for rendering.
 * 
 * This function sets up several important OpenGL states such as blending, depth testing, line smoothing and front face winding order.
 * It enables features like blending (for transparency), depth testing (for occlusion culling) and line smoothing (for smoother lines).
 * The blend equation is set to GL_FUNC_ADD for the source and destination colors, the blend function is set to use GL_SRC_ALPHA as the source color and GL_ONE_MINUS_SRC_ALPHA as the destination color. 
 * Depth testing is enabled with a depth function of GL_LEQUAL which means pixels that are closer to the camera will be drawn over those that are further away. The clear depth value is set to 1.0f.
 * Line smoothing is enabled, and front face winding order is set to GL_CW (counter-clockwise).
 * 
 * @return void
 */
/**
 * @brief Initializes the OpenGL Renderer API with various settings for rendering.
 * 
 * This function sets up several important OpenGL states such as blending, depth testing, line smoothing and front face winding order.
 * It enables blending by setting the source blend factor to GL_SRC_ALPHA and the destination blend factor to GL_ONE_MINUS_SRC_ALPHA. 
 * Depth testing is enabled with a depth function of GL_LEQUAL, clearing the depth buffer with glClearDepth(1.0f), and enabling line smoothing with glEnable(GL_LINE_SMOOTH). 
 * The front face winding order is set to GL_CW using glFrontFace(GL_CW).
 * 
 * @return void
 */
void OpenGLRendererAPI::Init()
	{
		AGE_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		//glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearDepth(1.0f);
		glEnable(GL_LINE_SMOOTH);
		glFrontFace(GL_CW);
	}
	/**
 * @brief This function sets the clear color for the OpenGL context.
 * 
 * @param Color A Vector4 object representing the RGBA values of the clear color.
 */
/**
 * @brief Set the clear color for OpenGL rendering context.
 *
 * This function sets the clear color for the current OpenGL rendering context. The color is specified as a Vector4 with each component ranging from 0 to 1.
 *
 * @param Color A Vector4 specifying the red, green, blue and alpha components of the color.
 */
void OpenGLRendererAPI::SetClearColor(const Vector4 Color)
	{
		glClearColor(Color[0], Color[1], Color[2], Color[3]);
		glBlendColor(1.f, 1.f, 1.f, 1.f);
		
	}
	/**
 * @brief Set the viewport for OpenGL rendering.
 * 
 * This function sets the viewport in OpenGL to a specified width and height at a given x and y position. The coordinates are defined as integers, with (0,0) being the bottom-left corner of the window/viewport.
 * @param x The x coordinate of the lower left corner of the viewport rectangle.
 * @param y The y coordinate of the lower left corner of the viewport rectangle.
 * @param Width The width of the viewport, in pixels.
 * @param Height The height of the viewport, in pixels.
 * 
 * @return void No return value is expected as this function only sets OpenGL state variables.
 */
/**
 * @brief Set the viewport for OpenGL rendering.
 * 
 * This function sets the viewport in OpenGL to a specified width and height starting at coordinates (x, y). The viewport is defined as the rectangular area of the window where rendering takes place.
 * 
 * @param x The x-coordinate of the lower left corner of the viewport rectangle.
 * @param y The y-coordinate of the lower left corner of the viewport rectangle.
 * @param Width The width of the viewport rectangle.
 * @param Height The height of the viewport rectangle.
 */
void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height)
	{
		glViewport(-1, -1, (int)Width, (int)Height);
		
	}
	/**
 * @brief Clears the color and depth buffers of the OpenGL context.
 *
 * This function uses glClear to clear both the color and depth buffer bits, indicating that all pixels in these buffers should be cleared. 
 * The color buffer is typically filled with black (0, 0, 0), while the depth buffer is set to maximum value.
 *
 * @return void
 */
/**
 * @brief Clears the color and depth buffer.
 *
 * This function uses OpenGL's glClear() function to clear both the color and depth buffers. The GL_COLOR_BUFFER_BIT and 
 * GL_DEPTH_BUFFER_BIT flags are used to specify which buffers should be cleared.
 */
void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}
	/**
 * @brief This function flushes the OpenGL command buffer. 
 * It ensures that all commands issued up to this point are executed immediately, without buffering them for later execution.
 *
 * @return void
 */
/**
 * @brief Flushes the OpenGL command queue.
 * 
 * This function calls glFlush(), which forces all pending commands to be executed as quickly as possible.
 * It is useful for ensuring that certain operations are completed before proceeding with other tasks.
 *
 * @return void
 */
void OpenGLRendererAPI::Flush()
	{
		glFlush();
	}
	/**
 * @brief Draws an indexed element array.
 * 
 * This function binds the given vertex array and then draws its elements using OpenGL's glDrawElements function. The number of indices to draw is determined by either the provided IndexCount parameter or, if no such count was provided, by the count in the bound index buffer. After drawing, it unbinds any texture for safety.
 * 
 * @param VertexArray A reference to a vertex array object that contains the data to be drawn.
 * @param IndexCount The number of indices to draw from the element array. If this is zero, the count in the index buffer will be used instead.
 * 
 * @return void
 */
/**
 * @brief This function is used to draw an indexed element array. It binds the vertex array and then uses OpenGL's glDrawElements function to render a set number of elements from the index buffer.
 * @param VertexArray A reference to a constant VertexArray object which represents the data for rendering.
 * @param IndexCount The number of indices to be drawn. If this is 0, it defaults to the count in the index buffer of the vertex array.
 * @return void
 */
void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount)
	{
		VertexArray->Bind();

		uint32_t Count = IndexCount ? IndexCount : VertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, (int)Count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	/**
 * @brief Draws a series of lines defined by the given vertex array.
 * 
 * This function binds the provided VertexArray object and then uses OpenGL's glDrawArrays to draw an array of vertices as line segments. The number of vertices drawn is specified by the 'VertexCount' parameter.
 *
 * @param VertexArray A reference to a VertexArray object that contains the vertex data for the lines to be drawn.
 * @param VertexCount The number of vertices in the VertexArray to draw.
 */
/**
 * @brief Draws a series of lines defined by the given vertex array.
 * 
 * This function binds the provided VertexArray object and then uses OpenGL's glDrawArrays to draw a series of lines, starting from the first element (index 0) and drawing 'VertexCount' number of vertices. The type of primitives drawn is specified as GL_LINES.
 * 
 * @param VertexArray A reference to a VertexArray object that contains the vertex data for the lines to be drawn.
 * @param VertexCount The number of vertices in the line strip or loop, i.e., the number of elements to draw.
 * 
 * @return void
 */
void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount)
	{
		VertexArray->Bind();
		glDrawArrays(GL_LINES, 0, (int)VertexCount);
	}
	/**
 * @brief DrawStrips is a function that draws triangle strips using OpenGL.
 * 
 * It binds the given VertexArray and then uses glDrawElements to draw elements with GL_TRIANGLE_STRIP mode. If IndexCount is not provided, it will use the count from the index buffer of the VertexArray. After drawing, it unbinds the texture for safety.
 * 
 * @param VertexArray A reference to a constant VertexArray object that represents the vertex data to be drawn.
 * @param IndexCount The number of indices to draw. If not provided, it will use the count from the index buffer of the VertexArray.
 */
/**
 * @brief DrawStrips is a function that draws triangle strips using the OpenGL API.
 * 
 * @param VertexArray A reference to a constant VertexArray object which represents the vertex array data.
 * @param IndexCount An unsigned integer representing the number of indices to be drawn. If this value is zero, it defaults to the count in the index buffer of the VertexArray.
 */
void OpenGLRendererAPI::DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount)
	{
		VertexArray->Bind();

		uint32_t Count = IndexCount ? IndexCount : VertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLE_STRIP, (int)Count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	/**
 * @brief Set the line width for subsequent drawing operations.
 * 
 * This function sets the current line width to a value in pixels. The actual effect of this setting depends on the specific rendering mode and transformation matrices currently active.
 *
 * @param Width The new line width, in pixels. Must be greater than zero.
 */
/** 
 * @brief This function sets the width of lines used for rendering.
 * @param Width The new line width to be set. Must be greater than zero.
 */
void OpenGLRendererAPI::SetLineWidth(float Width)
	{
		glLineWidth(Width);
	}
	/**
 * @brief Submits the current frame for rendering.
 *
 * This function submits the current frame to be rendered by the OpenGL Renderer API. It does not actually render anything, it just prepares everything for drawing. 
 * The actual rendering is done in the `OpenGLRendererAPI::EndScene()` function.
 *
 * @return void
 */
/**
 * @brief Submits the current frame for rendering.
 * 
 * This function submits the current frame to be rendered by the OpenGL Renderer API. It does not actually render anything, it just prepares everything for rendering.
 * 
 * @return void
 */
void OpenGLRendererAPI::Submit()
	{
	}
	/**
 * @brief This function is used to present the rendered scene to the screen. 
 * It does not take any parameters and returns void, indicating that it has completed its operation without returning a value.
 */
/**
 * @brief This function is used to present the rendered scene to the screen. 
 * It does not take any parameters and returns void, indicating that it has completed its task without returning a value.
 */
void OpenGLRendererAPI::Present()
	{
	}
}