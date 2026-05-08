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


		/**
 * @brief Returns an iterator pointing to the beginning of the Layers vector.
 * @return An iterator pointing to the start of the Layers vector. If no layers exist, returns an iterator equal to end().
 */
std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		/**
 * @brief Returns an iterator pointing to the theoretical element that follows the last element of the vector.
 * @return An iterator to the theoretical element following the last element of the vector.
 */
std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		/**
 * @brief Returns a constant iterator pointing to the beginning of the layers vector.
 * @return A constant iterator to the start of the layers vector.
 */
std::vector<Layer*>::const_iterator begin() const { return m_Layers.cbegin(); }

		/**
 * @brief Returns a constant iterator pointing to the past-the-end element of the layer vector.
 * 
 * This function returns a constant iterator that points to one position past the last element in the layer vector.
 * It is used to indicate the end of the sequence of elements in the container, similar to how std::vector's member functions cend() return an iterator pointing to the past-the-end element.
 * 
 * @return A constant iterator pointing to the past-the-end element.
 */
std::vector<Layer*>::const_iterator end() const { return m_Layers.cend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex  = 0;
	};
}