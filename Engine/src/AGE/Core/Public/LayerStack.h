#pragma once
#include "Core.h"
#include "Layer.h"

#include <vector>

namespace AGE
{
	class AGE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* Layer);

		void PushOverlay(Layer* Overlay);

		void PopLayer(Layer* Layer);

		void PopOverlay(Layer* Overlay);

		Layer* GetLayerByName(const std::string& LayerName);


		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.cbegin(); }

		std::vector<Layer*>::const_iterator end() const { return m_Layers.cend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex  = 0;
	};
}