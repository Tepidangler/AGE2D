#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGlContext.h"
#include "Platform/OpenGL/Public/OpenGLPipeline.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AGE
{
	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
		: m_WindowHandle(WindowHandle)
	{

		AGE_CORE_ASSERT(WindowHandle, "Window handle is null");
	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Init()
	{
		AGE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AGE_CORE_ASSERT(status, "Failed to initialize GLAD");

		CoreLogger::Info("OpenGL Info: ");
		
		CoreLogger::Trace("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
				
		CoreLogger::Trace("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
				
		CoreLogger::Trace("	Version: {0}", (const char*)glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers()
	{
		AGE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);


	}

	OpenGLPipeline* OpenGLContext::GetPipeline()
	{
		return m_Pipeline;
	}

	void OpenGLContext::SetPipeline(OpenGLPipeline* Pipeline)
	{
		m_Pipeline = Pipeline;
	}

	template<>
	OpenGLContext* GraphicsContext::As()
	{
		return (OpenGLContext*)this;
	}
}