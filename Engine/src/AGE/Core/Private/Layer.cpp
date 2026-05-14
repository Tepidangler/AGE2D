#include "AGEpch.hpp"
#include "Layer.h"

#include <GLFW/glfw3.h>

namespace AGE
{
	/**
 * @brief Constructs a Layer object with the given debug name.
 * 
 * This function is used to create a new Layer object, which can be used for various purposes such as logging or debugging. The debug name provided will be stored and can be accessed later using getDebugName() method.
 * 
 * @param DebugName A string representing the debug name of the layer.
 */
/**
 * @brief Constructs a Layer object with the given debug name.
 * 
 * This function is used to create a new Layer object with a specific debug name. The debug name can be used for debugging purposes and provides context about the layer's purpose or functionality.
 * 
 * @param DebugName A string representing the debug name of the layer.
 */
Layer::Layer(const std::string& DebugName)
		: m_DebugName(DebugName)
	{


	}

	/**
 * @brief Destructor for the Layer class.
 *
 * This destructor does not perform any specific actions when called, but it is a necessary part of the class's interface as it releases any resources that were acquired during the lifetime of an object of this class. 
 *
 * @return None.
 */
/**
 * @brief Destructor for the Layer class.
 */
Layer::~Layer()
	{

	}
	/**
 * @brief Get the current time in seconds since GLFW was initialized.
 * 
 * This function uses glfwGetTime(), which returns the time in seconds since GLFW was initialized.
 * The returned value is a double precision floating point number, so it can be used for more precise timing measurements.
 *
 * @return A float representing the current time in seconds.
 */
/** 
 * @brief This function returns the time in seconds since GLFW was initialized, as a floating-point number.
 * @return A float representing the current time in seconds.
 */
float Layer::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}
}