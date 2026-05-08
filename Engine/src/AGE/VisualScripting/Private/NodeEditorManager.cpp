#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "VisualScripting/Public/NodeEditorManager.h"
#include "Characters/Public/Character.h"
//#include <imgui_node_editor_internal.h>


namespace AGE
{
	uint32_t NodeEditorManager::NodeID = 0;
	/**
 * @brief NodeEditorManager is a class that manages the editing of nodes in a graph-based system.
 * 
 * It provides methods for creating, deleting and updating nodes. The manager also keeps track of all active nodes.
 */
NodeEditorManager::NodeEditorManager()
	{
	}

	Unknown
void NodeEditorManager::CreateContextAndWindow(const std::filesystem::path& Filepath, const std::string& WindowName, void* Target)
	{
		AppConfig appConfig = App::Get().GetAppConfig();
		ax::NodeEditor::Config Config;
		bool SettingsExist = std::filesystem::exists(appConfig.GameContentPath.string() + "VisualScripting/" + Filepath.string());
		if (Filepath.string().size() > 0)
		{
			Config.SettingsFile = appConfig.GameContentPath.string() + "VisualScripting/" + Filepath.string();
		}
		else
		{
			Config.SettingsFile = "Settings.json";
		}

		Config.UserPointer = this;

		Config.LoadNodeSettings = [](ax::NodeEditor::NodeId ID, char* Data, void* UserPointer) -> size_t
			{
				auto Self = static_cast<NodeEditorManager*>(UserPointer);
				Ref<AGENode> Node;

				for (auto& W : Self->m_ActiveWindows)
				{
					if (W.first->FindNode(ID))
					{
						Node = W.first->FindNode(ID);
						break;
					}
					else
					{
						Node = nullptr;
					}
				}

				if (!Node)
				{
					return 0;
				}

				if (Data != nullptr)
				{
					memcpy(Data, Node->State.data(), Node->State.size());
					return Node->State.size();
				}

				return 0;
			};

		Config.SaveNodeSettings = [](ax::NodeEditor::NodeId ID, const char* Data, size_t Size, ax::NodeEditor::SaveReasonFlags Reason, void* UserPointer) -> bool
			{
				auto Self = static_cast<NodeEditorManager*>(UserPointer);

				Ref<AGENode> Node;
				Ref<NodeEditorWindow> Window;
				for (auto& W : Self->m_ActiveWindows)
				{
					if (W.first->FindNode(ID))
					{
						Node = W.first->FindNode(ID);
						Window = W.first;
						break;
					}
					else
					{
						Node = nullptr;
					}
				}

				if (!Node)
				{
					return false;
				}

				Node->State.assign(Data, Size);
				Window->TouchNode(ID);
				return true;

			};
		if (!IsConfigFileStored(Config))
		{
			m_Configs.emplace_back(Config);
		}
		else
		{ 
			RebuildWindow(WindowName);
			return;
		}

		CreateNewWindow(WindowName, ax::NodeEditor::CreateEditor(&Config), Target, SettingsExist);
	}
	/**
 * @brief This function creates a new window and adds it to the active windows list.
 * 
 * @param WindowName The name of the window to be created.
 * @param Context Pointer to the editor context which is used by the NodeEditorWindow.
 * @param Target A void pointer that points to some target object, but no specific type information is provided in this function signature.
 * @param LoadingExisting A boolean flag indicating whether an existing window is being loaded or not.
 * 
 * @return None
 */
void NodeEditorManager::CreateNewWindow(const std::string& WindowName, ax::NodeEditor::EditorContext* Context, void* Target, bool LoadingExisting)
	{
		m_ActiveWindows.push_back({ CreateRef<NodeEditorWindow>(WindowName, Context, Target, LoadingExisting), Context});
		m_ActiveWindows.back().first->OnAttach();

	}
	/**
 * @brief Rebuilds a window with the given name. If no such window exists, this function does nothing.
 * 
 * This function iterates over all active windows and checks if their names match the provided one. When it finds a match, it calls the `RebuildWindow` method on that window object to rebuild it.
 * 
 * @param WindowName The name of the window to be rebuilt.
 */
void NodeEditorManager::RebuildWindow(const std::string& WindowName)
	{
		for (auto& W : m_ActiveWindows)
		{
			if (W.first->GetWindowName() == WindowName)
			{
				W.first->RebuildWindow();
				return;
			}
		}
	}
	/**
 * @brief Checks if a configuration file is stored in the NodeEditorManager instance.
 * 
 * This function iterates over all stored configurations and checks if there's one with the same SettingsFile as the provided Config parameter.
 * If it finds such a configuration, it returns true; otherwise, false.
 * 
 * @param Config The configuration to check for.
 * @return True if the config file is stored, False otherwise.
 */
bool NodeEditorManager::IsConfigFileStored(ax::NodeEditor::Config Config)
	{
		for (auto& C : m_Configs)
		{
			if (C.SettingsFile == Config.SettingsFile)
			{
				return true;
			}
		}
		return false;
	}
	/**
 * @brief Render all active windows in the NodeEditorManager.
 * 
 * This function iterates over all active windows and calls their OnImGuiRender method, passing in the provided TimeStep value.
 * It is used to update and render each window during the main application loop.
 * 
 * @param DeltaTime The time step for rendering and updating the windows.
 */
void NodeEditorManager::RenderWindows(TimeStep DeltaTime)
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->OnImGuiRender(DeltaTime);
			
		}
	}

	/**
 * @brief Destructor for NodeEditorManager class. It iterates over all active windows and destroys each editor instance using ax::NodeEditor::DestroyEditor function.
 * 
 * @return None
 */
NodeEditorManager::~NodeEditorManager()
	{
		for (auto& C : m_ActiveWindows)
		{
			ax::NodeEditor::DestroyEditor(C.second);
			
		}
	}
	/**
 * @brief This function is used to register functions for all active windows in the NodeEditorManager.
 * It iterates over each window (pair of a pointer to a Window and its name) in m_ActiveWindows, 
 * and calls RegisterFunctions() on the Window object pointed to by the first element of the pair.
 * @return void
 */
void NodeEditorManager::RegisterFunctions()
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->RegisterFunctions();
		}
	}
	/**
 * @brief Deregisters functions from all active windows.
 *
 * This function iterates over the list of active windows (m_ActiveWindows) and calls 
 * the DeregisterFunctions() method on each window's node editor. It is used to remove 
 * any registered functions that are no longer needed or relevant.
 *
 * @return void
 */
void NodeEditorManager::DeregisterFunctions()
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->DeregisterFunctions();
		}
	}
}