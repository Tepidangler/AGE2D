#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Layer.h"
#include "Core/Public/UUID.h"
#include "Math/Public/Vector2.h"
#include "Texture/Public/Texture.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"
#include "VisualScripting/Public/VisualScriptingStructs.h"

#include <imgui_node_editor.h>
#include <utilities/builders.h>
#include <utilities/widgets.h>

struct ImRect;
class Font;

namespace AGE
{
	class NodeEditorWindow : public Layer
	{
	public:
		NodeEditorWindow(const std::string& WindowName, ax::NodeEditor::EditorContext* Context, void* Target = nullptr, bool LoadingExisting = false);
		virtual ~NodeEditorWindow();

		void OnAttach();
		void OnImGuiRender(TimeStep DeltaTime);

		const std::string& GetWindowName() const { return m_Name; }

		static void Serialize(DataWriter* Serializer, const NodeEditorWindow& Data)
		{
			std::vector<AGENode> Nodes(Data.m_Nodes.size());
			std::vector<AGENodeLink> Links(Data.m_Links.size());

			for (int i = 0; i < Nodes.size(); i++)
			{
				Nodes[i] = *Data.m_Nodes[i].get();
			}
			for (int i = 0; i < Links.size(); i++)
			{
				Links[i] = *Data.m_Links[i].get();
			}
			Serializer->WriteString(Data.m_Name);
			Serializer->WriteRaw<uint64_t>(Data.m_ID);
			Serializer->WriteArray<AGENode>(Nodes);
			Serializer->WriteArray<AGENodeLink>(Links);
			Serializer->WriteRaw<bool>(Data.m_ShowOrdinals);
		}

		static void Deserialize(DataReader* Serializer, NodeEditorWindow& Data)
		{
			uint64_t ID;
			std::vector<AGENode> Nodes;
			std::vector<AGENodeLink> Links;

			Serializer->ReadString(Data.m_Name);
			Serializer->ReadRaw<uint64_t>(ID);
			Data.m_ID = (UUID)ID;
			Serializer->ReadArray<AGENode>(Nodes);
			Serializer->ReadArray<AGENodeLink>(Links);
			Serializer->ReadRaw<bool>(Data.m_ShowOrdinals);

			for (auto& N : Nodes)
			{
				// AGENode(int id, const char* name, ImColor color = ImColor(255,255,255))
				Data.m_Nodes.emplace_back(CreateRef<AGENode>((uint64_t)N.ID, N.Name.c_str(), N.Color));
				Data.m_Nodes.back()->Inputs = N.Inputs;
				Data.m_Nodes.back()->Outputs = N.Outputs;
				Data.m_Nodes.back()->State = N.State;
				Data.m_Nodes.back()->SavedState = N.SavedState;
				Data.m_Nodes.back()->FunctionArgs = N.FunctionArgs;
				Data.m_Nodes.back()->Type = N.Type;
				Data.m_Nodes.back()->bIsBeginPlay = N.bIsBeginPlay;
				Data.m_Nodes.back()->bIsOnUpdate = N.bIsOnUpdate;
				Data.m_Nodes.back()->NextNodeID = N.NextNodeID;
				Data.m_Nodes.back()->Func = N.Func;
			}

			for (auto& L : Links)
			{
				// AGENodeLink(ax::NodeEditor::LinkId LID, ax::NodeEditor::PinId SPID, ax::NodeEditor::PinId EPID)
				Data.m_Links.emplace_back(CreateRef<AGENodeLink>((uint64_t)L.ID, L.StartPinID, L.EndPinID));
			}
		}

	protected:

		void RenderWindow(bool* Opened, TimeStep DeltaTime);
		ImRect ImGui_GetItemRect();

		ImRect ImRect_Expanded(const ImRect& Rect, float x, float y);

		uint32_t GetNextID();
		ax::NodeEditor::LinkId GetNextLinkID();
		void TouchNode(ax::NodeEditor::NodeId ID);
		float GetTouchProgress(ax::NodeEditor::NodeId ID);
		void UpdateTouch(float DeltaTime);

		Ref<AGENode> FindNode(ax::NodeEditor::NodeId ID);

		Ref<AGENodeLink> FindLink(ax::NodeEditor::LinkId ID);

		Ref<AGENodeLink> FindLink(ax::NodeEditor::PinId ID);

		Ref<AGEPin> FindPin(ax::NodeEditor::PinId ID);
		
		ImColor GetIconColor(AGEPinType Type);

		void ShowStyleEditor(bool* Show = nullptr);
		void ShowDetailPanel(bool* ShowPanel = nullptr);

		void ShowLeftPane(float PanelWidth);

		void DrawPinIcon(const Ref<AGEPin>& Pin, bool Connected, int Alpha);
		
		bool IsPinLinked(ax::NodeEditor::PinId ID);

		bool CanCreateLink(Ref<AGEPin> A, Ref<AGEPin> B);

		void BuildNode(Ref<AGENode> Node);

		void BuildNodes();

		void DrawHeader(ax::NodeEditor::Utilities::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin, bool IsSimple, bool HasOutputCallbacks);
		void DrawInputPins(ax::NodeEditor::Utilities::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin);
		void DrawOutputPins(ax::NodeEditor::Utilities::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin, bool IsSimple);
		void DrawNodes(Ref<AGEPin>& newLinkPin);
		void DrawAndCreateNewLink(Ref<AGEPin>& newLinkPin, std::function<void(const char*, ImColor)>ShowLabelFunction);
		void DrawAndCreateNewNode(Ref<AGEPin>& newLinkPin, Ref<AGEPin>& newNodeLinkPin, bool createNewNode, std::function<void(const char*, ImColor)>ShowLabelFunction);
		void DeleteNode();


		
		static bool Splitter(bool SplitVertically, float Thickness, float* Size1, float* Size2, float Min_Size1, float Min_Size2, float SplitterLongAxisSize = -1.f);

		Ref<AGENode> SpawnBeginPlayNode();
		Ref<AGENode> SpawnOnUpdateNode();

		Ref<AGENode> SpawnOutputActionNode();

		Ref<AGENode> SpawnLessThanNode();
		Ref<AGENode> SpawnGreaterThanNode();
		Ref<AGENode> SpawnEqualToNode();
		// Greater Than or Equal To
		Ref<AGENode> SpawnGTETNode();
		// Less Than or Equal To
		Ref<AGENode> SpawnLTETNode();

		Ref<AGENode> SpawnPrintStringNode();
		Ref<AGENode> SpawnMakeLiteralString();
		Ref<AGENode> SpawnAppendString();

		Ref<AGENode> SpawnGetLocation3D();
		Ref<AGENode> SpawnSetLocation3D();

		Ref<AGENode> SpawnGetLocation2D();
		Ref<AGENode> SpawnSetLocation2D();

		Ref<AGENode> SpawnToString();

		Ref<AGENode> SpawnGetActor();

		//Math

		Ref<AGENode> SpawnSum();
		Ref<AGENode> SpawnSubtract();
		Ref<AGENode> SpawnMultiply();
		Ref<AGENode> SpawnDivide();
		Ref<AGENode> SpawnModulo();
		Ref<AGENode> SpawnPow();
		Ref<AGENode> SpawnSquareRoot();
		Ref<AGENode> SpawnCubeRoot();

		Ref<AGENode> SpawnDotProduct();

		Ref<AGENode> SpawnCrossProduct();

		Ref<AGENode> SpawnCosine();

		Ref<AGENode> SpawnSine();

		void RegisterFunctions();

		void DeregisterFunctions();

		void SyncLinks();

		void ShowNodeOptions(Ref<AGENode>& Node);

		void RebuildWindow();

		void SaveGraph();
		void CompileGraph();

	private:
		std::string m_Name;

		bool m_Minimized = false;

		UUID m_ID;
		const uint32_t m_PinIconSize = 24;
		std::vector<Ref<AGENode>> m_Nodes;
		std::vector<Ref<AGENodeLink>> m_Links;
		Ref<Texture2D> m_HeaderBg;
		Ref<Texture2D> m_SaveIcon;
		Ref<Texture2D> m_RestoreIcon;
		const float m_TouchTime = 1.f;
		std::map<ax::NodeEditor::NodeId, float, NodeIdLess> m_NodeTouchTime;
		bool m_ShowOrdinals = false;

		bool m_IsOpen = true;

		bool m_bLoadingExisting = false;
		ax::NodeEditor::EditorContext* m_Context;

		Ref<ScriptableEntity> m_Target = nullptr;

		friend class NodeEditorManager;
		static Ref<Font> s_Font;

	};

}
