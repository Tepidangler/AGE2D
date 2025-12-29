#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "VisualScripting/Public/NodeEditorManager.h"
#include "Characters/Public/Character.h"



namespace AGE
{
	uint32_t NodeEditorManager::NodeID = 0;
	NodeEditorManager::NodeEditorManager()
	{
	}

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
	void NodeEditorManager::CreateNewWindow(const std::string& WindowName, ax::NodeEditor::EditorContext* Context, void* Target, bool LoadingExisting)
	{
		m_ActiveWindows.push_back({ CreateRef<NodeEditorWindow>(WindowName, Context, Target, LoadingExisting), Context});
		m_ActiveWindows.back().first->OnAttach();

	}
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
	void NodeEditorManager::RenderWindows(TimeStep DeltaTime)
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->OnImGuiRender(DeltaTime);
			
		}
	}

	NodeEditorManager::~NodeEditorManager()
	{
		for (auto& C : m_ActiveWindows)
		{
			ax::NodeEditor::DestroyEditor(C.second);
			
		}
	}
	void NodeEditorManager::RegisterFunctions()
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->RegisterFunctions();
		}
	}
	void NodeEditorManager::DeregisterFunctions()
	{
		for (auto& W : m_ActiveWindows)
		{
			W.first->DeregisterFunctions();
		}
	}
}