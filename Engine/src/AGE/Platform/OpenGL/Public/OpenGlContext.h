#pragma once

#include "Render/Public/GraphicsContext.h"




struct GLFWwindow;

namespace AGE
{
	class OpenGLPipeline;

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