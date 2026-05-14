#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGlContext.h"
#include "Platform/OpenGL/Public/OpenGLPipeline.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
namespace AGE
{
	/**
 * @brief Constructs an OpenGLContext object.
 * 
 * This constructor initializes the OpenGL context using a GLFWwindow pointer. It asserts that the window handle is not null.
 * 
 * @param WindowHandle A pointer to the GLFWwindow instance for which this OpenGLContext will be created.
 */
OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
		: m_WindowHandle(WindowHandle)
	{

		CoreLogger::Assert(WindowHandle, "Window handle is null");
	}

	/**
 * @brief Destructor for the OpenGLContext class.
 * 
 * This function is responsible for cleaning up any resources that were acquired during the lifetime of this object, such as deleting buffers and textures. It does not perform any operations on the actual rendering context itself.
 */
OpenGLContext::~OpenGLContext()
	{

	}

	/**
 * @brief Initializes the OpenGL context.
 * 
 * This function sets up the OpenGL context for use by making it the current context using glfwMakeContextCurrent(). It then initializes GLAD, a library that provides easy access to OpenGL functions and extensions in desktop OpenGL. The status of this initialization is checked with an assertion to ensure successful completion. Finally, information about the OpenGL implementation is logged.
 * 
 * @return void
 */
void OpenGLContext::Init()
	{
		AGE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CoreLogger::Assert(status, "Failed to initialize GLAD");

		CoreLogger::Info("OpenGL Info: ");

		CoreLogger::Trace("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		CoreLogger::Trace("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		CoreLogger::Trace("	Version: {0}", (const char*)glGetString(GL_VERSION));

	}
	/** 
 * @brief Swaps the front and back buffers of the specified window.
 *
 * This function is used to swap the front and back buffers of a window when rendering, effectively displaying what has been rendered.
 * The behavior of this function depends on the specific implementation of the OpenGL library being used. 
 *
 * @return void
 */
void OpenGLContext::SwapBuffers()
	{
		AGE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);


	}

	/**
 * @brief Get the pipeline object associated with this context.
 * 
 * This function returns a pointer to the OpenGLPipeline object that is currently bound to this context. The returned object can be used for rendering operations.
 * 
 * @return OpenGLPipeline* A pointer to the current OpenGLPipeline object, or nullptr if no pipeline is set.
 */
OpenGLPipeline* OpenGLContext::GetPipeline()
	{
		return m_Pipeline;
	}

	/**
 * @brief This function sets the pipeline for the OpenGL context.
 *
 * @param[in] Pipeline The new OpenGL pipeline to be set.
 */
void OpenGLContext::SetPipeline(OpenGLPipeline* Pipeline)
	{
		m_Pipeline = Pipeline;
	}

	template<>
	/**
 * @brief This function returns a pointer to the OpenGL context associated with this instance of GraphicsContext.
 * @return Pointer to an OpenGLContext object, or nullptr if no such context exists.
 */
OpenGLContext* GraphicsContext::As()
	{
		return (OpenGLContext*)this;
	}
}