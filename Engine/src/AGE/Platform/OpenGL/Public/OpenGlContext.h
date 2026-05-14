#pragma once

#include "Render/Public/GraphicsContext.h"




struct GLFWwindow;

namespace AGE
{
	class OpenGLPipeline;

	/**
 * @brief Constructor for OpenGLContext. Initializes the context with a GLFW window handle.
 * 
 * @param WindowHandle A pointer to an existing GLFWwindow object that this context will be bound to.
 */
/** 
 * @brief This class represents an OpenGL context. It is responsible for initializing and managing the OpenGL pipeline.
 * 
 * @param WindowHandle A pointer to a GLFWwindow object, which represents the window that this context will be associated with.
 */
class AGE_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* WindowHandle);
			

		virtual ~OpenGLContext();


		virtual void Init() override;
		virtual void SwapBuffers()  override;


		OpenGLPipeline* GetPipeline();

		void SetPipeline(OpenGLPipeline* Pipeline);

	private:

		GLFWwindow* m_WindowHandle;
		OpenGLPipeline* m_Pipeline;

	};
}