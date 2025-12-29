#include "AGEpch.hpp"
#include "Layer.h"

#include <glfw/glfw3.h>

namespace AGE
{
	Layer::Layer(const std::string& DebugName)
		: m_DebugName(DebugName)
	{


	}

	Layer::~Layer()
	{

	}
	float Layer::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}
}