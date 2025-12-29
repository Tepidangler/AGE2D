#include "AGEpch.hpp"
#include "LayerStack.h"

namespace AGE
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* L : m_Layers)
		{
			delete L;
		}
	
	}


	void LayerStack::PushLayer(Layer* Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, Layer);
		m_LayerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
	}
	void LayerStack::PopLayer(Layer* Layer)
	{
		Layer->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Layer);

		if (it != m_Layers.end())
		{

			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
		
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	Layer * LayerStack::GetLayerByName(const std::string &LayerName)
	{
		auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [LayerName](const Layer* Layer)
		{
			return Layer->GetName() == LayerName;
		});

		if (it != m_Layers.end())
		{
			return *it;
		}
	}
}

