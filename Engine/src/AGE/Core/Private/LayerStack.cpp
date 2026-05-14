#include "AGEpch.hpp"
#include "LayerStack.h"

namespace AGE
{
	/**
 * @brief LayerStack is a class that manages layers in a stack-like structure. 
 * It provides methods for pushing, popping and managing the layers.
 */
/**
 * @brief LayerStack is a class that manages layers in a stack-like structure. 
 * It provides methods for pushing, popping and managing layers.
 */
LayerStack::LayerStack()
	{
	}

	/**
 * @brief Destructor for the LayerStack class.
 * This function is responsible for deleting all layers in the stack, freeing up memory that was previously allocated to them.
 * It uses a range-based for loop to iterate over each layer and deletes it using the delete keyword.
 */
/**
 * @brief Destructor for the LayerStack class.
 * This function is responsible for deleting all layers in the stack when an instance of the class is destroyed. 
 * It uses a range-based for loop to iterate over each layer and deletes it using 'delete'.
 */
LayerStack::~LayerStack()
	{
		for (Layer* L : m_Layers)
		{
			delete L;
		}
	
	}


	/**
 * @brief Pushes a layer onto the stack at the specified position.
 * 
 * This function inserts a new layer into the LayerStack at the specified index, effectively pushing it to the top of the rendering order. The layer is inserted before all existing layers. If no index is provided, it defaults to the end of the stack (top).
 *
 * @param Layer Pointer to the layer that should be pushed onto the stack.
 * 
 * @return void No return value.
 */
/**
 * @brief Pushes a layer onto the stack at the specified index.
 * 
 * This function inserts a new layer into the LayerStack at the position indicated by m_LayerInsertIndex. The layer is inserted before all existing layers with lower indices, and its index in the stack increases by one.
 * 
 * @param Layer Pointer to the layer that will be pushed onto the stack.
 * @return void No return value.
 */
void LayerStack::PushLayer(Layer* Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, Layer);
		m_LayerInsertIndex++;
	}
	/** 
 * @brief Pushes an overlay layer onto the stack.
 * 
 * This function adds a new layer to the top of the LayerStack, making it visible and interactive.
 * The layer is added at the end of the m_Layers vector, so it will be rendered on top of all other layers.
 * 
 * @param Overlay Pointer to the overlay layer that should be pushed onto the stack.
 * @return void No return value.
 */
/** 
 * @brief Pushes an overlay layer onto the stack.
 * 
 * This function adds a new layer to the top of the LayerStack, making it visible and interactive.
 * The layer is added at the end of the m_Layers vector, so it will be rendered on top of all other layers.
 * 
 * @param Overlay Pointer to the overlay layer that should be pushed onto the stack.
 */
void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
	}
	/**
 * @brief This function is used to remove a layer from the LayerStack. 
 * It calls the OnDetach() method of the provided layer, then it searches for that layer in the m_Layers vector and removes it if found.
 * The index where this layer was inserted into the stack is also decremented by one.
 * @param Layer Pointer to the layer that needs to be removed from the stack.
 */
/**
 * @brief Pop a layer from the stack and detach it.
 * 
 * This function removes a specified Layer object from the LayerStack by calling its OnDetach() method, then erases it from the m_Layers vector. The index of insertion is also decremented to reflect this removal.
 * @param Layer Pointer to the layer that needs to be removed.
 */
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
	/**
 * @brief This function is used to remove an overlay from the layer stack.
 *
 * @param Overlay Pointer to the Layer object that needs to be removed.
 * 
 * @return void
 */
/**
 * @brief This function is used to remove an overlay from the layer stack.
 * 
 * @param Overlay Pointer to the Layer object that needs to be removed.
 * 
 * @return void No return value.
 */
void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
		
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	/**
 * @brief This function is used to get a layer by its name.
 *
 * The function iterates over the layers in the stack and returns the first one whose name matches the input string. If no such layer exists, it returns nullptr.
 * 
 * @param LayerName A const reference to a std::string representing the name of the layer we are looking for.
 * @return Pointer to Layer if found, otherwise nullptr.
 */
/**
 * @brief This function is used to get a layer by its name.
 * @param LayerName The name of the layer that we want to find.
 * @return Returns a pointer to the found layer if it exists, otherwise returns nullptr.
 */
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

		// TODO: Add something to let users know what happened
		return nullptr;
	}
}

