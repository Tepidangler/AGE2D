#pragma once
#include "Core/Public/Core.h"
#include "VisualScripting/Public/NodeEditorWindow.h"
#include <imgui_node_editor.h>

#include <vector>
#include <string>

namespace AGE
{
	class NodeEditorManager
	{
	public:
		NodeEditorManager();
		/**
 * @brief Deleted copy constructor for the NodeEditorManager class to prevent copying.
 *
 * This function is marked as deleted because we do not want any copies of this object. It's a good practice in C++ to avoid unnecessary copying and wasting memory resources, especially when dealing with complex objects like this one.
 * 
 * @param[in] other The NodeEditorManager instance to be copied. This parameter is ignored as the copy constructor is marked as deleted.
 *
 * @return Nothing. As a result of being marked as deleted, attempting to use it will lead to a compile-time error.
 */
NodeEditorManager(const NodeEditorManager&) = delete;
		/**
 * @brief NodeEditorManager move constructor is deleted to prevent copying of the manager object.
 * 
 * This function is marked as deleted because we do not want to allow copying of the NodeEditorManager object.
 * We only allow moving semantics, which means transferring ownership of resources from one object to another.
 * 
 * @return The move constructor does not return anything since it's a deleted function.
 */
NodeEditorManager(NodeEditorManager&&) = delete;
		virtual ~NodeEditorManager();

		void RegisterFunctions();

		void DeregisterFunctions();
		void CreateContextAndWindow(const std::filesystem::path& Filepath, const std::string& WindowName, void* Target = nullptr);
		void RenderWindows(TimeStep DeltaTime);

		/**
 * @brief Generates a new unique node ID.
 *
 * This function increments the global NodeID variable and returns it, effectively generating a new unique identifier for each call.
 *
 * @return The newly generated node ID as a uint32_t.
 */
static uint32_t GetNewNodeID() {return ++NodeID;}

	private:
		void CreateNewWindow(const std::string& WindowName, ax::NodeEditor::EditorContext* Context, void* Target = nullptr, bool LoadingExisting = false);

		void RebuildWindow(const std::string& WindowName);

		bool IsConfigFileStored(ax::NodeEditor::Config Config);


	private:

		std::vector<std::pair<Ref<NodeEditorWindow>, ax::NodeEditor::EditorContext* >> m_ActiveWindows;

		std::vector<ax::NodeEditor::Config> m_Configs;

		static uint32_t NodeID;
	};
}
