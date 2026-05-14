#include "AGEpch.hpp"
#include "VisualScripting/Public/NodeEditorWindow.h"
#include "Core/Public/Colors.h"
#include "Scene/Public/ScriptableEntity.h"
#include "Render/Public/Renderer2D.h"
#include "Render/Public/Font.h"
#include "Math/Public/MathStructures.h"
#include "Structs/Public/DataStructures.h"
#include "Structs/Public/Functions.h"
#include <misc/cpp/imgui_stdlib.h>
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_LINUX
#pragma clang diagnostic ignored "-Wnontrivial-memcall"
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui_node_editor_internal.h>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui_node_editor_internal.h>
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <imgui_node_editor_internal.h>
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

//#include <imgui_internal.h>

#include "Characters/Public/Character.h"

#include "Quests/Public/QuestComponent.h"

#include "VisualScripting/Public/NodeEditorManager.h"

namespace INEUtils = ax::NodeEditor::Utilities;
using C = AGE::Colors::Color;
namespace AGE
{
	template<typename T>
	
static void DrawProperties(rttr::type TargetType, rttr::instance Instance, Ref<ScriptableEntity> Target)
	{
		T* DerivedTarget = (T*)Target.get();
		if (ImGui::CollapsingHeader("Properties"))
		{
			for (auto& P : TargetType.get_properties())
			{
				if (P.get_metadata(MetaDataType::Scriptable).get_value<bool>())
				{
					if (ImGui::TreeNode(P.get_name().to_string().c_str()))
					{
						ImGui::Text("Description:");
						ImGui::TextWrapped("%s", P.get_metadata("Description").to_string().c_str());
						if (P.get_name().to_string() == "Name")
						{
							auto Name = P.get_value(Instance).to_string();
							ImGui::Text("Name:"); ImGui::SameLine();
							ImGui::InputText("##Name: ", &Name);
							std::ignore = P.set_value(Instance, Name);
						}

						if (P.get_name().to_string() == "Quest Component")
						{


							ImGui::Checkbox("Is Quest Character", &DerivedTarget->bQuestCharacter);
							if (DerivedTarget->bQuestCharacter)
							{
								if (!DerivedTarget->GetQuestComponent())
								{
									DerivedTarget->GetQuestComponent() = AGE::CreateRef<GameFramework::QuestComponent>();
								}
								auto& CheckpointNumber = DerivedTarget->GetQuestComponent()->GetCheckpointNumber();

								ImGui::Text("QuestID: "); ImGui::SameLine();
								ImGui::Text("%s", std::to_string(DerivedTarget->GetQuestComponent()->GetID()).c_str());

								ImGui::InputInt("Checkpoint Number", &CheckpointNumber);

								std::vector<std::string> QuestStrings;
								std::string CurrentQuestString;

								auto& Quests = DerivedTarget->GetQuestComponent()->GetQuestManager()->GetQuests();

								for (auto& Q : Quests)
								{
									QuestStrings.push_back(Q.second->QuestName);
								}

								if (QuestStrings.size() > 0)
								{
									CurrentQuestString = QuestStrings[(size_t)DerivedTarget->GetQuestComponent()->GetQuest()];
								}



								if (ImGui::BeginCombo("Quest Title", CurrentQuestString.c_str()))
								{
									for (size_t i = 0; i < QuestStrings.size(); i++)
									{
										bool IsSelected = CurrentQuestString == QuestStrings[i];

										if (ImGui::Selectable(QuestStrings[i].c_str(), IsSelected))
										{
											CurrentQuestString = QuestStrings[i];
											DerivedTarget->GetQuestComponent()->SetQuestID(QuestStrings[i]);
										}

										if (IsSelected)
										{
											ImGui::SetItemDefaultFocus();
										}
									}

									ImGui::EndCombo();
								}
							}
						}
						ImGui::TreePop();
					}
					ImGui::Dummy({0.f,4.f});
				}
			}


		}
	}
	Ref<AGEFont> NodeEditorWindow::s_Font = nullptr;
	/**
 * @brief Draws a control for a Vector2 type with two float values.
 * 
 * This function creates an ImGui control for manipulating a Vector2 value, consisting of two draggable floats (x and y). It provides buttons to reset the x and y values to a specified ResetValue.
 * 
 * @param Label The label for this control.
 * @param Values A reference to the Vector2 value that will be manipulated by this control.
 * @param ResetValue The default value to which the x and y fields will be reset when their respective buttons are clicked (default is 0).
 * 
 * @return void
 */
static void DrawVec2Control(const std::string& Label, Vector2& Values, float ResetValue = 0.f)
	{
		ImGuiIO& io = ImGui::GetIO();

		auto BoldFont = io.Fonts->Fonts[0];
		ImGui::PushID(Label.c_str());

		ImGui::PushMultiItemsWidths(2, 100.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
		ImVec2 ButtonSize = { LineHeight + 3.f,LineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.9f, .2f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("X", ButtonSize))
			Values.x = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(0);
		ImGui::DragFloat("##X", &Values.x, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.3f, .8f, .3f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Y", ButtonSize))
			Values.y = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(0);
		ImGui::DragFloat("##Y", &Values.y, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();
		ImGui::PopID();


	}

	```cpp
/**
 * @brief Draws a control for Vector3 values with ImGui.
 *
 * This function displays three controls, one each for the x, y and z components of a 3D vector. Each control includes a button to reset its value to a specified default (ResetValue), and a drag float slider for adjusting the value. The width of each column can be adjusted with ColumnWidth.
 *
 * @param Label A string label for the group of controls.
 * @param Values A reference to the Vector3 object whose values are being edited.
 * @param ResetValue The default value to reset individual components to (default is 0.f).
 * @param ColumnWidth The width of each column in pixels (default is 100.f).
 */
```
static void DrawVec3Control(const std::string& Label, Vector3& Values, float ResetValue = 0.f, float ColumnWidth = 100.f)
	{
		ImGuiIO& io = ImGui::GetIO();

		auto BoldFont = io.Fonts->Fonts[0];
		ImGui::PushID(Label.c_str());

		ImGui::PushMultiItemsWidths(3, 200.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y *2;
		ImVec2 ButtonSize = { LineHeight + 3.f,LineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.9f, .2f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("X", ButtonSize))
			Values.x = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(0);
		ImGui::DragFloat("##X", &Values.x, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(.15f,0);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.3f, .8f, .3f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Y", ButtonSize))
			Values.y = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(0);
		ImGui::DragFloat("##Y", &Values.y, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(.15f, 0);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.2f, .35f, .9f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Z", ButtonSize))
			Values.z = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(0);
		ImGui::DragFloat("##Z", &Values.z, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(1, 0);
		ImGui::PopStyleVar();
		ImGui::PopID();


	}

	```cpp
/**
 * @brief Draws a control for Vector4 with four components (X, Y, Z, W) each having its own drag float.
 * 
 * @param Label The label to be displayed on the UI.
 * @param Values A reference to the Vector4 object that holds the current values of X, Y, Z and W.
 * @param ResetValue The value to reset individual components to when their respective buttons are clicked (default: 0.f).
 * @param ColumnWidth The width of each column in the UI grid (default: 100.f).
 * 
 * @return void
 */
```
static void DrawVec4Control(const std::string& Label, Vector4& Values, float ResetValue = 0.f, float ColumnWidth = 100.f)
	{
		ImGuiIO& io = ImGui::GetIO();

		auto BoldFont = io.Fonts->Fonts[0];
		ImGui::PushID(Label.c_str());

		ImGui::PushMultiItemsWidths(4, 200.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
		ImVec2 ButtonSize = { LineHeight + 3.f,LineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.9f, .2f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("X", ButtonSize))
			Values.x = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(1, 0);
		ImGui::DragFloat("##X", &Values.x, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(.1f, 0);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.3f, .8f, .3f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Y", ButtonSize))
			Values.y = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(1, 0);
		ImGui::DragFloat("##Y", &Values.y, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(.1f, 0);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.2f, .35f, .9f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Z", ButtonSize))
			Values.z = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(1, 0);
		ImGui::DragFloat("##Z", &Values.z, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(.1f, 0);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, .843f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, .97f, 0.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, .843f, 0.f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("W", ButtonSize))
			Values.w = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::Spring(1, 0);
		ImGui::DragFloat("##W", &Values.w, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::Spring(1, 0);
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();


	}

	
NodeEditorWindow::NodeEditorWindow(const std::string& WindowName, ax::NodeEditor::EditorContext* Context, void* Target, bool LoadingExisting)
		:m_Name(WindowName), m_bLoadingExisting(LoadingExisting), m_Context(Context)
	{
		AppConfig Config = App::Get().GetAppConfig();
		ScriptableEntity* Entt = reinterpret_cast<ScriptableEntity*>(Target);
		m_Target = Ref<ScriptableEntity>(Entt);
		s_Font = AGEFont::GetDefault();
		if (LoadingExisting)
		{
			std::string Path = Config.GameContentPath.string() + "VisualScripting/" + WindowName + ".AGEasset";
			FileStreamReader Stream(Path);
			Stream.ReadObject<NodeEditorWindow>(*this);
			for (auto& N : m_Nodes)
			{
				if (!N->bIsBeginPlay)
				{

					N->Func.Reference = N;
					N->Func.Entt = m_Target.get();
				}
				if (N->NextNodeID != 0)
				{
					N->NextNode = FindNode((uint64_t)N->NextNodeID);
				}
			}
			BuildNodes();
			SyncLinks();
		}
	}
	/**
 * @brief Destructor for the NodeEditorWindow class.
 * 
 * This function is responsible for cleaning up any resources that were allocated during the lifetime of this object, such as memory or file handles. It's important to ensure that all resources are properly released when an object is destroyed to prevent memory leaks and other issues.
 */
NodeEditorWindow::~NodeEditorWindow()
	{

	}
	/**
 * @brief This function is called when the NodeEditorWindow is attached to the application. It sets up various aspects of the editor, such as setting the current editor context and positioning nodes. 
 * 
 * @param None
 * 
 * @return void
 */
void NodeEditorWindow::OnAttach()
	{
		AppConfig Config = App::Get().GetAppConfig();
		ax::NodeEditor::SetCurrentEditor(m_Context);
		if (!m_bLoadingExisting)
		{
			SpawnBeginPlayNode();
			ax::NodeEditor::SetNodePosition(m_Nodes.back()->ID, { -252, 220 });
			ax::NodeEditor::NavigateToContent();
			SpawnOnUpdateNode();
			ax::NodeEditor::SetNodePosition(m_Nodes.back()->ID, { -252, 320 });
			ax::NodeEditor::NavigateToContent();
			BuildNodes();
		}
		m_HeaderBg = Texture2D::Create(Config.EditorAssetPath.string() + "/VisualScriptingTextures/Header.png");
		m_RestoreIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/VisualScriptingTextures/RestoreIcon.png");
		m_SaveIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/VisualScriptingTextures/SaveIcon.png");
	}
	/**
 * @brief This function is responsible for rendering the ImGui interface in the NodeEditorWindow.
 * 
 * @param[in] DeltaTime The time step representing the elapsed time since the last frame.
 * 
 * @return void
 */
void NodeEditorWindow::OnImGuiRender(TimeStep DeltaTime)
	{
		if (m_IsOpen)
		{
			RenderWindow(&m_IsOpen, DeltaTime);
		}
	}

	
void NodeEditorWindow::RenderWindow(bool* Opened, TimeStep DeltaTime)
	{
		if (ImGui::Begin(m_Name.c_str(), Opened))
		{
			UpdateTouch(DeltaTime);

			ax::NodeEditor::SetCurrentEditor(m_Context);
			static ax::NodeEditor::NodeId contextNodeId = 0;
			static ax::NodeEditor::LinkId contextLinkId = 0;
			static ax::NodeEditor::PinId  contextPinId = 0;
			static bool createNewNode = false;
			static Ref<AGEPin> newNodeLinkPin = nullptr;
			static Ref<AGEPin> newLinkPin = nullptr;

			static float leftPaneWidth = 400.0f;
			static float rightPaneWidth = 800.0f;

			Splitter(true, 4.0f, &leftPaneWidth, &rightPaneWidth, 50.0f, 50.0f);
			ShowLeftPane(leftPaneWidth - 4.0f);
			ImGui::SameLine(0.0f, 12.0f);
			ax::NodeEditor::Begin(m_Name.c_str());

			auto cursorTopLeft = ImGui::GetCursorScreenPos();
			uint32_t HeaderBGTexID = m_HeaderBg->GetTextureID();
			INEUtils::BlueprintNodeBuilder Builder((ImTextureID)&HeaderBGTexID, (int)m_HeaderBg->GetWidth(), (int)m_HeaderBg->GetHeight());

			for (auto& N : m_Nodes)
			{
				if (N->Type != AGENodeType::Blueprint && N->Type != AGENodeType::Simple)
				{
					continue;
				}

				const auto IsSimple = N->Type == AGENodeType::Simple;

				bool HasOutputCallbacks = false;
				for (auto& O : N->Outputs)
				{
					if (O->Type == AGEPinType::Callback)
					{
						HasOutputCallbacks = true;
					}
				}

				Builder.Begin(N->ID);
				DrawHeader(Builder, N, newLinkPin, IsSimple, HasOutputCallbacks);

				DrawInputPins(Builder, N, newLinkPin);

				if (IsSimple)
				{
					Builder.Middle();
					ImGui::Spring(1, 0);
					ImGui::TextUnformatted(N->Name.c_str());
					ImGui::Spring(1, 0);
				}

				DrawOutputPins(Builder, N, newLinkPin, IsSimple);

				Builder.End();
			}

			DrawNodes(newLinkPin);

			for (auto& L : m_Links)
			{
				ax::NodeEditor::Link(L->ID, L->StartPinID, L->EndPinID, L->Color, 2.f);
			}

			SyncLinks();
			if (!createNewNode)
			{
				auto ShowLabel = [](const char* Label, ImColor Color)
					{
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight());
						auto Size = ImGui::CalcTextSize(Label);

						auto Padding = ImGui::GetStyle().FramePadding;
						auto Spacing = ImGui::GetStyle().ItemSpacing;

						ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(Spacing.x, Spacing.y));

						auto RectMin = ImGui::GetCursorPos() - Padding;
						auto RectMax = ImGui::GetCursorPos() + Size + Padding;

						auto DrawList = ImGui::GetWindowDrawList();
						DrawList->AddRectFilled(RectMin, RectMax, Color, Size.y * .15f);
						ImGui::TextUnformatted(Label);
					};

				DrawAndCreateNewLink(newLinkPin, ShowLabel);


				DrawAndCreateNewNode(newLinkPin, newNodeLinkPin, createNewNode, ShowLabel);

			}
			else
			{
				newLinkPin = nullptr;
			}
			ax::NodeEditor::EndCreate();

			DeleteNode();
			ImGui::SetCursorScreenPos(cursorTopLeft);

			auto openPopupPosition = ImGui::GetMousePos();
			ax::NodeEditor::Suspend();
			if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
			{
				ImGui::OpenPopup("Node Context Menu");
			}
			else if (ax::NodeEditor::ShowPinContextMenu(&contextPinId))
			{
				ImGui::OpenPopup("Pin Context Menu");
			}
			else if (ax::NodeEditor::ShowLinkContextMenu(&contextLinkId))
			{
				ImGui::OpenPopup("Link Context Menu");
			}
			else if (ax::NodeEditor::ShowBackgroundContextMenu())
			{
				ImGui::OpenPopup("Create New Node");
				newNodeLinkPin = nullptr;
			}
			ax::NodeEditor::Resume();


			ax::NodeEditor::Suspend();
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
			if (ImGui::BeginPopup("Node Context Menu"))
			{
				auto node = FindNode(contextNodeId);

				ImGui::TextUnformatted("Node Context Menu");
				ImGui::Separator();
				if (node)
				{
					ImGui::Text("ID: %p", node->ID.AsPointer());
					ImGui::Text("Type: %s", node->Type == AGENodeType::Blueprint ? "Blueprint" : (node->Type == AGENodeType::Tree ? "Tree" : "Comment"));
					ImGui::Text("Inputs: %d", (int)node->Inputs.size());
					ImGui::Text("Outputs: %d", (int)node->Outputs.size());
				}
				else
					ImGui::Text("Unknown node: %p", contextNodeId.AsPointer());
				ImGui::Separator();
				if (ImGui::MenuItem("Delete"))
					ax::NodeEditor::DeleteNode(contextNodeId);
				ImGui::EndPopup();
			}

			if (ImGui::BeginPopup("Pin Context Menu"))
			{
				auto pin = FindPin(contextPinId);

				ImGui::TextUnformatted("Pin Context Menu");
				ImGui::Separator();
				if (pin)
				{
					ImGui::Text("ID: %p", pin->ID.AsPointer());
					if (pin->Node)
						ImGui::Text("Node: %p", pin->Node->ID.AsPointer());
					else
						ImGui::Text("Node: %s", "<none>");
				}
				else
					ImGui::Text("Unknown pin: %p", contextPinId.AsPointer());

				ImGui::EndPopup();
			}

			if (ImGui::BeginPopup("Link Context Menu"))
			{
				auto link = FindLink(contextLinkId);

				ImGui::TextUnformatted("Link Context Menu");
				ImGui::Separator();
				if (link)
				{
					ImGui::Text("ID: %p", link->ID.AsPointer());
					ImGui::Text("From: %p", link->StartPinID.AsPointer());
					ImGui::Text("To: %p", link->EndPinID.AsPointer());
				}
				else
					ImGui::Text("Unknown link: %p", contextLinkId.AsPointer());
				ImGui::Separator();
				if (ImGui::MenuItem("Delete"))
					ax::NodeEditor::DeleteLink(contextLinkId);
				ImGui::EndPopup();
			}

			if (ImGui::BeginPopup("Create New Node"))
			{
				auto newNodePostion = openPopupPosition;
				//ImGui::SetCursorScreenPos(ImGui::GetMousePosOnOpeningCurrentPopup());

				//auto drawList = ImGui::GetWindowDrawList();
				//drawList->AddCircleFilled(ImGui::GetMousePosOnOpeningCurrentPopup(), 10.0f, 0xFFFF00FF);

				Ref<AGENode> Node = nullptr;

				ShowNodeOptions(Node);
				
				if (Node)
				{
					BuildNodes();

					createNewNode = false;

					ax::NodeEditor::SetNodePosition(Node->ID, newNodePostion);

					if (auto startPin = newNodeLinkPin)
					{
						auto& pins = startPin->Kind == ax::NodeEditor::PinKind::Input ? Node->Outputs : Node->Inputs;

						for (auto& pin : pins)
						{
							if (CanCreateLink(startPin, pin))
							{
								auto endPin = pin;
								if (startPin->Kind == ax::NodeEditor::PinKind::Input)
								{
									std::swap(startPin, endPin);
								}

								m_Links.emplace_back(CreateRef<AGENodeLink>((uint64_t)GetNextID(), startPin->ID, endPin->ID));
								m_Links.back()->Color = GetIconColor(startPin->Type);

								break;
							}
						}
					}
				}

				ImGui::EndPopup();
			}
			else
			{
				createNewNode = false;
			}
			ImGui::PopStyleVar();
			ax::NodeEditor::Resume();
			ax::NodeEditor::End();
			ax::NodeEditor::SetCurrentEditor(nullptr);
			ImGui::End();
		}
		else
		{
			ImGui::End();
			return;
		}
	}

	/**
 * @brief This function returns an `ImRect` object that represents the rectangle of the current item.
 * 
 * The returned `ImRect` is created using the minimum and maximum coordinates of the current item as obtained by calling `ImGui::GetItemRectMin()` and `ImGui::GetItemRectMax()` respectively.
 * 
 * @return ImRect An object representing the rectangle of the current item.
 */
ImRect NodeEditorWindow::ImGui_GetItemRect()
	{
		return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());	
	}
	/**
 * @brief Expands an ImRect by a given amount in both dimensions.
 *
 * This function takes an existing ImRect and expands it by the specified amounts in both x and y directions. 
 * The resulting rectangle will have its minimum corner moved to the left and up, and its maximum corner moved to the right and down.
 *
 * @param Rect The original ImRect to be expanded.
 * @param x The amount to expand in the x direction (left/right).
 * @param y The amount to expand in the y direction (up/down).
 * 
 * @return An ImRect that is expanded by the given amounts in both dimensions.
 */
ImRect NodeEditorWindow::ImRect_Expanded(const ImRect& Rect, float x, float y)
	{
		auto Result = Rect;

		Result.Min.x -= x;
		Result.Min.y -= y;
		Result.Max.x += x;
		Result.Max.y += y;

		return Result;
	}
	/** 
 * @brief This function returns the next available ID for a new node.
 * @return The unique identifier for the next node.
 */
uint32_t NodeEditorWindow::GetNextID()
	{
		return NodeEditorManager::GetNewNodeID();
	}
	/**
 * @brief Generates the next available Link ID.
 * 
 * This function generates a unique Link ID for use in the Node Editor system. It uses the GetNextID() function to generate an integer, which is then converted into a LinkId object. The generated Link Id can be used to identify and manipulate links within the Node Editor system.
 *
 * @return ax::NodeEditor::LinkId - A unique identifier for a link in the Node Editor system.
 */
ax::NodeEditor::LinkId NodeEditorWindow::GetNextLinkID()
	{
		return ax::NodeEditor::LinkId(GetNextID());
	}
	/**
 * @brief This function is used to update the touch time for a specific node.
 * 
 * @param ID The unique identifier of the node.
 * @return void
 */
void NodeEditorWindow::TouchNode(ax::NodeEditor::NodeId ID)
	{
		m_NodeTouchTime[ID] = m_TouchTime;
	}
	/**
 * @brief Get the touch progress of a node with given ID
 * 
 * This function returns the touch progress for a specific node identified by its ID. The touch progress is calculated as the time elapsed since the last touch divided by the total touch time. If no touch data exists or if the touch time is zero, it will return 0.0f.
 * 
 * @param ID The unique identifier of the node
 * @return float The touch progress in range [0.0, 1.0]
 */
float NodeEditorWindow::GetTouchProgress(ax::NodeEditor::NodeId ID)
	{
		auto it = m_NodeTouchTime.find(ID);
		if (it != m_NodeTouchTime.end() && it->second > 0.f)
		{
			return (m_TouchTime - it->second) / m_TouchTime;
		}

		return 0.0f;
	}
	/**
 * @brief This function updates the touch time for each node in the NodeEditorWindow.
 * 
 * The function iterates over all elements (pairs of nodes and their corresponding touch times) in m_NodeTouchTime,
 * subtracts the provided DeltaTime from each element's second value if it is greater than zero. This effectively
 * reduces the remaining time for which a node has been touched by the specified amount. If the touch time reaches 0,
 * the function will not further reduce it.
 *
 * @param DeltaTime The amount of time to subtract from each element's second value in m_NodeTouchTime.
 */
void NodeEditorWindow::UpdateTouch(float DeltaTime)
	{
		for (auto& E : m_NodeTouchTime)
		{
			if (E.second > 0.f)
			{
				E.second -= DeltaTime;
			}
		}
	}
	/**
 * @brief Finds a node with the given ID in the NodeEditorWindow.
 *
 * This function iterates over all nodes in the m_Nodes vector and checks if their ID matches the input ID. If it does, 
 * that node is returned. If no matching node is found, an empty Ref<AGENode> object is returned.
 *
 * @param ID The ID of the node to be searched for.
 * @return A reference to the node with the given ID if one exists, otherwise returns an empty Ref<AGENode> object.
 */
Ref<AGENode> NodeEditorWindow::FindNode(ax::NodeEditor::NodeId ID)
	{
		for (auto& N : m_Nodes)
		{
			if (N->ID == ID)
			{
				return N;
			}
		}
		return Ref<AGENode>();
	}
	/**
 * @brief Finds a link with the given ID in the node editor window.
 * 
 * This function iterates over all links in the m_Links vector and returns the first one that has an ID matching the input parameter 'ID'. If no such link is found, it returns an empty Ref object.
 * 
 * @param ID The ID of the link to be found.
 * @return A reference to the found link or an empty Ref object if no such link exists.
 */
Ref<AGENodeLink> NodeEditorWindow::FindLink(ax::NodeEditor::LinkId ID)
	{
		for (auto& L : m_Links)
		{
			if (L->ID == ID)
			{
				return L;
			}
		}

		return Ref<AGENodeLink>();
	}
	/**
 * @brief Finds a link with the given start pin id.
 *
 * This function iterates over all links in the node editor window and returns the first one that has the same start pin id as the input parameter ID. If no such link is found, an empty reference to AGENodeLink is returned.
 *
 * @param ID The id of the start pin to search for.
 * @return A reference to the found link or an empty reference if no matching link was found.
 */
Ref<AGENodeLink> NodeEditorWindow::FindLink(ax::NodeEditor::PinId ID)
	{
		for (auto& L : m_Links)
		{
			if (L->StartPinID == ID)
			{
				return L;
			}
		}

		return Ref<AGENodeLink>();
	}
	/**
 * @brief Finds a pin with the given ID in the node editor.
 * 
 * This function iterates over all nodes and their inputs/outputs to find a pin that matches the provided ID. If no such pin is found, an empty reference (Ref<AGEPin>()) is returned.
 * @param ID The ID of the pin to be found.
 * @return A reference to the found pin or an empty reference if no matching pin was found.
 */
Ref<AGEPin> NodeEditorWindow::FindPin(ax::NodeEditor::PinId ID)
	{
		if (!ID)
		{
			return Ref<AGEPin>();
		}

		for (auto& N : m_Nodes)
		{
			for (auto& P : N->Inputs)
			{
				if (P->ID == ID)
				{
					return P;
				}
			}

			for (auto& P : N->Outputs)
			{
				if (P->ID == ID)
				{
					return P;
				}
			}
		}

		return Ref<AGEPin>();
	}
	/**
 * @brief GetIconColor returns the color corresponding to a given pin type.
 * 
 * @param Type The AGEPinType for which we want to get the icon color.
 * @return ImColor The color that corresponds to the input pin type.
 */
COMMENT:
"This function takes an enum of type AGEPinType as argument and returns an ImColor object corresponding to it."
CONFIDENCE: 1.0;

ImColor NodeEditorWindow::GetIconColor(AGEPinType Type)
	{
		switch (Type)
		{
		default:
		case AGEPinType::Flow:     return ImColor(C::White[0], C::White[1], C::White[2]);
		case AGEPinType::Boolean:     return ImColor(C::Red[0], C::Red[1], C::Red[2]);
		case AGEPinType::Int:      return ImColor(C::Blue[0], C::Blue[1], C::Blue[2]);
		case AGEPinType::Int16:	   return ImColor(C::Indigo[0], C::Indigo[1], C::Indigo[2]);
		case AGEPinType::Int64:	   return ImColor(C::Navy[0], C::Navy[1], C::Navy[2]);
		case AGEPinType::UInt16:   return ImColor(C::Crimson[0], C::Crimson[1], C::Crimson[2]);
		case AGEPinType::UInt32:   return ImColor(C::DarkBlue[0], C::DarkBlue[1], C::DarkBlue[2]);
		case AGEPinType::UInt64:   return ImColor(C::Mint[0], C::Mint[1], C::Mint[2]);
		case AGEPinType::Vector2D: return ImColor(C::Lavender[0], C::Lavender[1], C::Lavender[2]);
		case AGEPinType::Vector3D: return ImColor(C::Yellow[0], C::Yellow[1], C::Yellow[2]);
		case AGEPinType::Vector4D: return ImColor(C::SeaGreen[0], C::SeaGreen[1], C::SeaGreen[2]);
		case AGEPinType::Float:    return ImColor(C::Green[0], C::Green[1], C::Green[2]);
		case AGEPinType::String:   return ImColor(C::Purple[0], C::Purple[1], C::Purple[2]);
		case AGEPinType::Object:   return ImColor(C::Cyan[0], C::Cyan[1], C::Cyan[2]);
		case AGEPinType::Function: return ImColor(C::Pink[0], C::Pink[1], C::Pink[2]);
		case AGEPinType::Callback: return ImColor(C::DarkRed[0],C::DarkRed[1],C::DarkRed[2]);
		case AGEPinType::Any:	   return ImColor(C::Gray[0], C::Gray[1], C::Gray[2]);
		}
	}
	
void NodeEditorWindow::ShowStyleEditor(bool* Show)
	{
		if (!ImGui::Begin("Style", Show))
		{
			ImGui::End();
			return;
		}

		auto paneWidth = ImGui::GetContentRegionAvail().x;

		auto& editorStyle = ax::NodeEditor::GetStyle();
		ImGui::BeginHorizontal("Style buttons", ImVec2(paneWidth, 0), 1.0f);
		ImGui::TextUnformatted("Values");
		ImGui::Spring();
		if (ImGui::Button("Reset to defaults"))
			editorStyle = ax::NodeEditor::Style();
		ImGui::EndHorizontal();
		ImGui::Spacing();
		ImGui::DragFloat4("Node Padding", &editorStyle.NodePadding.x, 0.1f, 0.0f, 40.0f);
		ImGui::DragFloat("Node Rounding", &editorStyle.NodeRounding, 0.1f, 0.0f, 40.0f);
		ImGui::DragFloat("Node Border Width", &editorStyle.NodeBorderWidth, 0.1f, 0.0f, 15.0f);
		ImGui::DragFloat("Hovered Node Border Width", &editorStyle.HoveredNodeBorderWidth, 0.1f, 0.0f, 15.0f);
		ImGui::DragFloat("Hovered Node Border Offset", &editorStyle.HoverNodeBorderOffset, 0.1f, -40.0f, 40.0f);
		ImGui::DragFloat("Selected Node Border Width", &editorStyle.SelectedNodeBorderWidth, 0.1f, 0.0f, 15.0f);
		ImGui::DragFloat("Selected Node Border Offset", &editorStyle.SelectedNodeBorderOffset, 0.1f, -40.0f, 40.0f);
		ImGui::DragFloat("Pin Rounding", &editorStyle.PinRounding, 0.1f, 0.0f, 40.0f);
		ImGui::DragFloat("Pin Border Width", &editorStyle.PinBorderWidth, 0.1f, 0.0f, 15.0f);
		ImGui::DragFloat("Link Strength", &editorStyle.LinkStrength, 1.0f, 0.0f, 500.0f);
		//ImVec2  SourceDirection;
		//ImVec2  TargetDirection;
		ImGui::DragFloat("Scroll Duration", &editorStyle.ScrollDuration, 0.001f, 0.0f, 2.0f);
		ImGui::DragFloat("Flow Marker Distance", &editorStyle.FlowMarkerDistance, 1.0f, 1.0f, 200.0f);
		ImGui::DragFloat("Flow Speed", &editorStyle.FlowSpeed, 1.0f, 1.0f, 2000.0f);
		ImGui::DragFloat("Flow Duration", &editorStyle.FlowDuration, 0.001f, 0.0f, 5.0f);
		//ImVec2  PivotAlignment;
		//ImVec2  PivotSize;
		//ImVec2  PivotScale;
		//float   PinCorners;
		//float   PinRadius;
		//float   PinArrowSize;
		//float   PinArrowWidth;
		ImGui::DragFloat("Group Rounding", &editorStyle.GroupRounding, 0.1f, 0.0f, 40.0f);
		ImGui::DragFloat("Group Border Width", &editorStyle.GroupBorderWidth, 0.1f, 0.0f, 15.0f);

		ImGui::Separator();

		static ImGuiColorEditFlags edit_mode = ImGuiColorEditFlags_DisplayRGB;
		ImGui::BeginHorizontal("Color Mode", ImVec2(paneWidth, 0), 1.0f);
		ImGui::TextUnformatted("Filter Colors");
		ImGui::Spring();
		ImGui::RadioButton("RGB", &edit_mode, ImGuiColorEditFlags_DisplayRGB);
		ImGui::Spring(0);
		ImGui::RadioButton("HSV", &edit_mode, ImGuiColorEditFlags_DisplayHSV);
		ImGui::Spring(0);
		ImGui::RadioButton("HEX", &edit_mode, ImGuiColorEditFlags_DisplayHex);
		ImGui::EndHorizontal();

		static ImGuiTextFilter filter;
		filter.Draw("##filter", paneWidth);

		ImGui::Spacing();

		ImGui::PushItemWidth(-160);
		for (int i = 0; i < ax::NodeEditor::StyleColor_Count; ++i)
		{
			auto name = ax::NodeEditor::GetStyleColorName((ax::NodeEditor::StyleColor)i);
			if (!filter.PassFilter(name))
				continue;

			ImGui::ColorEdit4(name, &editorStyle.Colors[i].x, edit_mode);
		}
		ImGui::PopItemWidth();

		ImGui::End();
	}
	/**
 * @brief This function is used to display the detail panel for a given target. 
 * The detail panel shows stats and properties of the entity.
 * 
 * @param ShowPanel A boolean pointer that indicates whether the detail panel should be shown or not.
 */
void NodeEditorWindow::ShowDetailPanel(bool* ShowPanel)
	{
		if (!ImGui::Begin("Details", ShowPanel))
		{
			ImGui::End();
			return;
		}
		rttr::instance Instance = m_Target;
		rttr::type TargetType = m_Target->get_type();
		//Draw Stats for Entity
		ImGui::Text("Entity Type:"); ImGui::SameLine();
		ImGui::Text("%s", TargetType.get_name().to_string().c_str());
		if (TargetType.get_name().to_string() == "Character")
		{
			DrawProperties<GameFramework::Character>(TargetType,Instance,m_Target);
		}

		ImGui::End();
	}
	
void NodeEditorWindow::ShowLeftPane(float PaneWidth)
	{
		auto& io = ImGui::GetIO();

		ImGui::BeginChild("Selection###", ImVec2(PaneWidth, 0));

		PaneWidth = ImGui::GetContentRegionAvail().x;

		static bool showStyleEditor = false;
		static bool showDetailPanel = false;
		std::string StyleName = m_Name + "##" + "Style Editor";
		ImGui::BeginHorizontal(StyleName.c_str(), ImVec2(PaneWidth, 0));
		ImGui::Spring(0.0f, 0.0f);
		if (ImGui::Button("Zoom to Content"))
			ax::NodeEditor::NavigateToContent();
		ImGui::Spring(0.0f);
		if (ImGui::Button("Show Flow"))
		{
			for (auto& link : m_Links)
				ax::NodeEditor::Flow(link->ID);
		}
		ImGui::Spring();
		if (ImGui::Button("Edit Style"))
			showStyleEditor = true;
		if (ImGui::Button("Show Details Panel"))
		{
			showDetailPanel = true;
		}
		ImGui::EndHorizontal();
		ImGui::Checkbox("Show Ordinals", &m_ShowOrdinals);
		if (ImGui::Button("Save Graph"))
		{
			SaveGraph();
		}
		ImGui::SameLine();
		if (ImGui::Button("Compile"))
		{
			CompileGraph();
		}

		if (showStyleEditor)
			ShowStyleEditor(&showStyleEditor);
		if (showDetailPanel)
		{
			ShowDetailPanel(&showDetailPanel);
		}

		std::vector<ax::NodeEditor::NodeId> selectedNodes;
		std::vector<ax::NodeEditor::LinkId> selectedLinks;
		selectedNodes.resize((size_t)ax::NodeEditor::GetSelectedObjectCount());
		selectedLinks.resize((size_t)ax::NodeEditor::GetSelectedObjectCount());

		int nodeCount = ax::NodeEditor::GetSelectedNodes(selectedNodes.data(), static_cast<int>(selectedNodes.size()));
		int linkCount = ax::NodeEditor::GetSelectedLinks(selectedLinks.data(), static_cast<int>(selectedLinks.size()));

		selectedNodes.resize((size_t)nodeCount);
		selectedLinks.resize((size_t)linkCount);

		float saveIconWidth = (float)m_SaveIcon->GetWidth();
		float saveIconHeight = (float)m_SaveIcon->GetHeight();
		float restoreIconWidth = (float)m_RestoreIcon->GetWidth();
		float restoreIconHeight = (float)m_RestoreIcon->GetHeight();

		ImGui::GetWindowDrawList()->AddRectFilled(
			ImGui::GetCursorScreenPos(),
			ImGui::GetCursorScreenPos() + ImVec2(PaneWidth, ImGui::GetTextLineHeight()),
			ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
		ImGui::Spacing(); ImGui::SameLine();
		ImGui::TextUnformatted("Nodes");
		ImGui::Indent();
		for (auto& node : m_Nodes)
		{
			ImGui::PushID(node->ID.AsPointer());
			auto start = ImGui::GetCursorScreenPos();
			const auto progress = GetTouchProgress(node->ID);
			if (progress > 0.f)
			{
				ImGui::GetWindowDrawList()->AddLine(
					start + ImVec2(-8, 0),
					start + ImVec2(-8, ImGui::GetTextLineHeight()),
					IM_COL32(255, 0, 0, 255 - (int)(255 * progress)), 4.0f);
			}

			bool isSelected = std::find(selectedNodes.begin(), selectedNodes.end(), node->ID) != selectedNodes.end();
# if IMGUI_VERSION_NUM >= 18967
			ImGui::SetNextItemAllowOverlap();
# endif
			if (ImGui::Selectable((node->Name + "##" + std::to_string(reinterpret_cast<uintptr_t>(node->ID.AsPointer()))).c_str(), &isSelected))
			{
				if (io.KeyCtrl)
				{
					if (isSelected)
						ax::NodeEditor::SelectNode(node->ID, true);
					else
						ax::NodeEditor::DeselectNode(node->ID);
				}
				else
					ax::NodeEditor::SelectNode(node->ID, false);

				ax::NodeEditor::NavigateToSelection();
			}
			if (ImGui::IsItemHovered() && !node->State.empty())
				ImGui::SetTooltip("State: %s", node->State.c_str());

			auto id = std::string("(") + std::to_string(reinterpret_cast<uintptr_t>(node->ID.AsPointer())) + ")";
			auto textSize = ImGui::CalcTextSize(id.c_str(), nullptr);
			auto iconPanelPos = start + ImVec2(
				PaneWidth - ImGui::GetStyle().FramePadding.x - ImGui::GetStyle().IndentSpacing - saveIconWidth - restoreIconWidth - ImGui::GetStyle().ItemInnerSpacing.x * 1,
				(ImGui::GetTextLineHeight() - saveIconHeight) / 2);
			ImGui::GetWindowDrawList()->AddText(
				ImVec2(iconPanelPos.x - textSize.x - ImGui::GetStyle().ItemInnerSpacing.x, start.y),
				IM_COL32(255, 255, 255, 255), id.c_str(), nullptr);

			auto drawList = ImGui::GetWindowDrawList();
			ImGui::SetCursorScreenPos(iconPanelPos);
# if IMGUI_VERSION_NUM < 18967
			ImGui::SetItemAllowOverlap();
# else
			ImGui::SetNextItemAllowOverlap();
# endif
			if (node->SavedState.empty())
			{
				if (ImGui::InvisibleButton("save", ImVec2((float)saveIconWidth, (float)saveIconHeight)))
					node->SavedState = node->State;

				uint32_t SaveIconTexID = m_SaveIcon->GetTextureID();
				if (ImGui::IsItemActive())
					drawList->AddImage((ImTextureID)&SaveIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 96));
				else if (ImGui::IsItemHovered())
					drawList->AddImage((ImTextureID)&SaveIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255));
				else
					drawList->AddImage((ImTextureID)&SaveIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 160));
			}
			else
			{
				uint32_t SaveIconTexID = m_SaveIcon->GetTextureID();
				ImGui::Dummy(ImVec2((float)saveIconWidth, (float)saveIconHeight));
				drawList->AddImage((ImTextureID)&SaveIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 32));
			}

			ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
# if IMGUI_VERSION_NUM < 18967
			ImGui::SetItemAllowOverlap();
# else
			ImGui::SetNextItemAllowOverlap();
# endif
			if (!node->SavedState.empty())
			{
				if (ImGui::InvisibleButton("restore", ImVec2((float)restoreIconWidth, (float)restoreIconHeight)))
				{
					node->State = node->SavedState;
					ax::NodeEditor::RestoreNodeState(node->ID);
					node->SavedState.clear();
				}
				uint32_t RestoreIconTexID = m_RestoreIcon->GetTextureID();
				if (ImGui::IsItemActive())
					drawList->AddImage((ImTextureID)&RestoreIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 96));
				else if (ImGui::IsItemHovered())
					drawList->AddImage((ImTextureID)&RestoreIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255));
				else
					drawList->AddImage((ImTextureID)&RestoreIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 160));
			}
			else
			{
				uint32_t RestoreIconTexID = m_RestoreIcon->GetTextureID();
				ImGui::Dummy(ImVec2((float)restoreIconWidth, (float)restoreIconHeight));
				drawList->AddImage((ImTextureID)&RestoreIconTexID, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 32));
			}

			ImGui::SameLine(0, 0);
# if IMGUI_VERSION_NUM < 18967
			ImGui::SetItemAllowOverlap();
# endif
			ImGui::Dummy(ImVec2(0, (float)restoreIconHeight));

			ImGui::PopID();
		}
		ImGui::Unindent();

		static int changeCount = 0;

		ImGui::GetWindowDrawList()->AddRectFilled(
			ImGui::GetCursorScreenPos(),
			ImGui::GetCursorScreenPos() + ImVec2(PaneWidth, ImGui::GetTextLineHeight()),
			ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
		ImGui::Spacing(); ImGui::SameLine();
		ImGui::TextUnformatted("Selection");

		std::string SelectionName = m_Name + "##" + "Selection Stats";
		ImGui::BeginHorizontal(SelectionName.c_str(), ImVec2(PaneWidth, 0));
		ImGui::Text("Changed %d time%s", changeCount, changeCount > 1 ? "s" : "");
		ImGui::Spring();
		if (ImGui::Button("Deselect All"))
			ax::NodeEditor::ClearSelection();
		ImGui::EndHorizontal();
		ImGui::Indent();
		for (size_t i = 0; i < nodeCount; ++i) ImGui::Text("Node (%p)", selectedNodes[i].AsPointer());
		for (size_t i = 0; i < linkCount; ++i) ImGui::Text("Link (%p)", selectedLinks[i].AsPointer());
		ImGui::Unindent();

		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z)))
			for (auto& link : m_Links)
				ax::NodeEditor::Flow(link->ID);

		if (ax::NodeEditor::HasSelectionChanged())
			++changeCount;

		ImGui::EndChild();
	}
	
void NodeEditorWindow::DrawPinIcon(const Ref<AGEPin>& Pin, bool Connected, int Alpha)
	{
		ax::Widgets::IconType iconType;
		ImColor Color = GetIconColor(Pin->Type);
		Color.Value.w = (float)(Alpha / 255);

		switch (Pin->Type)
		{
		case AGEPinType::Flow:     iconType = ax::Widgets::IconType::Flow;   break;
		case AGEPinType::Boolean:     iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Int:      iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Int16:    iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Int64:    iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::UInt16:   iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::UInt32:   iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::UInt64:   iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Vector2D: iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Vector3D: iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Vector4D: iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Float:    iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::String:   iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Object:   iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Function: iconType = ax::Widgets::IconType::Circle; break;
		case AGEPinType::Callback: iconType = ax::Widgets::IconType::Square; break;
		case AGEPinType::Any:	   iconType = ax::Widgets::IconType::Circle; break;
		default:
			return;
		}
		
		ax::Widgets::Icon(ImVec2((float)m_PinIconSize, (float)m_PinIconSize), iconType, Connected, Color, ImColor(32, 32, 32, Alpha));
	}
	/**
 * @brief Checks if a pin is linked.
 *
 * This function checks whether the given PinId (ID) is linked to any other pins in the NodeEditorWindow. 
 * It does this by iterating over all links in m_Links and checking if either the StartPinID or EndPinID of each link equals the provided ID.
 * If a match is found, it returns true indicating that the pin is linked. Otherwise, it returns false.
 *
 * @param ID The PinId to check for linking status.
 * 
 * @return True if the pin is linked (i.e., connected to another pin), False otherwise.
 */
bool NodeEditorWindow::IsPinLinked(ax::NodeEditor::PinId ID)
	{
		if (!ID)
		{
			return false;
		}

		for (auto& L : m_Links)
		{
			if (L->StartPinID == ID || L->EndPinID == ID)
			{
				return true;
			}
		}

		return false;

	}
	/**
 * @brief Checks if a link can be created between two pins.
 * 
 * This function checks whether it is possible to create a link between two pins, A and B. It considers several factors such as the existence of the pins, their equality, the kind of each pin, and the type of each pin. Additionally, it also takes into account certain special cases where one pin's type can be any of 'Flow' or 'Callback'.
 * 
 * @param A The first pin to consider for creating a link.
 * @param B The second pin to consider for creating a link.
 * @return True if a link can be created, false otherwise.
 */
bool NodeEditorWindow::CanCreateLink(Ref<AGEPin> A, Ref<AGEPin> B)
	{
		if (!A || !B || A == B || A->Kind == B->Kind || A->Type != B->Type || A->Node == B->Node || 
			(B->Type == AGEPinType::Any && (A->Type != AGEPinType::Flow && A->Type != AGEPinType::Callback) ))
		{
			return true;
		}
		return false;
	}
	/**
 * @brief This function builds a node by setting its inputs and outputs.
 * 
 * @param Node The node to be built. It is expected that this node has been initialized with at least some input and output pins.
 */
void NodeEditorWindow::BuildNode(Ref<AGENode> Node)
	{
		for (auto& I : Node->Inputs)
		{
			I->Node = Node;
			I->Kind = ax::NodeEditor::PinKind::Input;
		}

		for (auto& O : Node->Outputs)
		{
			O->Node = Node;
			O->Kind = ax::NodeEditor::PinKind::Output;
		}
	}
	/**
 * @brief This function builds all the nodes in the NodeEditorWindow.
 * It iterates over each node (`m_Nodes`) and calls `BuildNode()` on it. 
 * The purpose of this function is to update or rebuild all nodes in the window, ensuring they are up-to-date with any changes made elsewhere in the program.
 * @return void
 */
void NodeEditorWindow::BuildNodes()
	{
		for (auto& N : m_Nodes)
		{
			BuildNode(N);
		}
	}
	
void NodeEditorWindow::DrawHeader(INEUtils::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin,bool IsSimple, bool HasOutputCallbacks)
	{
		if (!IsSimple)
		{
			Builder.Header(Node->Color);
			ImGui::Spring(0);
			ImGui::TextUnformatted(Node->Name.c_str());
			ImGui::Spring(1);
			ImGui::Dummy(ImVec2(0, 28));
			if (HasOutputCallbacks)
			{
				std::string CallbacksName = m_Name + "##" + "Callbacks";
				ImGui::BeginVertical(CallbacksName.c_str(), ImVec2(0, 28));
				ImGui::Spring(1, 0);
				for (auto& O : Node->Outputs)
				{
					if (O->Type != AGEPinType::Callback)
					{
						continue;
					}

					auto Alpha = ImGui::GetStyle().Alpha;
					if (newLinkPin && !CanCreateLink(newLinkPin, O) && O != newLinkPin)
					{
						Alpha = Alpha * (48.f / 255.f);
					}
					ax::NodeEditor::BeginPin(O->ID, ax::NodeEditor::PinKind::Output);
					ax::NodeEditor::PinPivotAlignment(ImVec2(1.f, .5f));
					ax::NodeEditor::PinPivotSize(ImVec2(0, 0));
					ImGui::BeginHorizontal(O->ID.AsPointer());
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Alpha);
					if (!O->Name.empty())
					{
						ImGui::TextUnformatted(O->Name.c_str());
						ImGui::Spring(0);
					}
					DrawPinIcon(O, IsPinLinked(O->ID), (int)(Alpha * 255));
					ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
					ImGui::EndHorizontal();
					ImGui::PopStyleVar();
					ax::NodeEditor::EndPin();
				}
				ImGui::Spring(1, 0);
				ImGui::EndVertical();
				ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
			}
			else
			{
				ImGui::Spring(0);
			}
			Builder.EndHeader();
		}
	}
	
void NodeEditorWindow::DrawInputPins(INEUtils::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin)
	{
		for (auto& I : Node->Inputs)
		{
			auto Alpha = ImGui::GetStyle().Alpha;

			if (newLinkPin && !CanCreateLink(newLinkPin, I) && I != newLinkPin)
			{
				Alpha = Alpha * (48.f / 255.f);
			}

			Builder.Input(I->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Alpha);
	
			DrawPinIcon(I, IsPinLinked(I->ID), (int)(Alpha * 255));
			ImGui::Spring(0);
			if (!I->Name.empty())
			{
				ImGui::TextUnformatted(I->Name.c_str());
				ImGui::Spring(0);
			}
			if (I->Type == AGEPinType::Boolean)
			{
				ImGui::Checkbox("##bool",&I->Boolean);
				ImGui::Spring(0);
			}
			if (I->Type == AGEPinType::Float)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputFloat(I->Name.c_str(), &I->Value);
				ImGui::Spring(1,0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::String)
			{
				if (!IsPinLinked(I->ID))
				{
					ImGui::PushMultiItemsWidths(1, 100.f);
					ImGui::InputText("##String", &I->String);
					ImGui::Spring(1, 0);
					ImGui::PopItemWidth();
				}
			}
			if (I->Type == AGEPinType::Int)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputInt(I->Name.c_str(), &I->Integer);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::Int16)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputInt("##Int16", &I->Integer16);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::Int64)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputInt("##Int64", &I->Integer64);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::UInt16)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputUInt("##UInt16", &I->UInteger16);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::UInt32)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputUInt("##UInt32", &I->UInteger32);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}
			if (I->Type == AGEPinType::UInt64)
			{
				ImGui::PushMultiItemsWidths(1, 50.f);
				ImGui::InputUInt("##UInt64", &I->UInteger64);
				ImGui::Spring(1, 0);
				ImGui::PopItemWidth();
			}

			if (I->Type == AGEPinType::Vector2D)
			{
				DrawVec2Control("##Vector2D", I->Vector2D);
				ImGui::Spring(1, 0);
			}
			if (I->Type == AGEPinType::Vector3D)
			{
				DrawVec3Control("##Vector3D", I->Vector3D);
				ImGui::Spring(1, 0);
			}
			if (I->Type == AGEPinType::Vector4D)
			{
				DrawVec4Control("##Vector4D", I->Vector4D);
				ImGui::Spring(1, 0);
			}
			ImGui::PopStyleVar();
			Builder.EndInput();

		}
	}
	
void NodeEditorWindow::DrawOutputPins(INEUtils::BlueprintNodeBuilder& Builder, Ref<AGENode>& Node, Ref<AGEPin>& newLinkPin, bool IsSimple)
	{
		for (auto& O : Node->Outputs)
		{
			if (!IsSimple && O->Type == AGE::AGEPinType::Callback)
			{
				continue;
			}

			auto Alpha = ImGui::GetStyle().Alpha;
			if (newLinkPin && !CanCreateLink(newLinkPin, O) && O != newLinkPin)
			{
				Alpha = Alpha * (48.f / 255.f);
			}

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Alpha);
			Builder.Output(O->ID);

			if (!O->Name.empty())
			{
				ImGui::Spring(0);
				ImGui::TextUnformatted(O->Name.c_str());
			}
			ImGui::Spring(0);
			DrawPinIcon(O, IsPinLinked(O->ID), (int)(Alpha * 255));
			ImGui::PopStyleVar();
			Builder.EndOutput();
		}
	}
	
void NodeEditorWindow::DrawNodes(Ref<AGEPin>& newLinkPin)
	{
		for (auto& N : m_Nodes)
		{
			if (N->Type != AGENodeType::Tree)
			{
				continue;
			}

			const float rounding = 5.0f;
			const float padding = 12.0f;

			const auto pinBackground = ax::NodeEditor::GetStyle().Colors[ax::NodeEditor::StyleColor_NodeBg];


			ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_NodeBg, ImColor(128, 128, 128, 200));
			ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
			ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_PinRect, ImColor(60, 180, 255, 150));
			ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_NodeRounding, rounding);
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_SourceDirection, ImVec2(0.0f, 1.0f));
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_TargetDirection, ImVec2(0.0f, -1.0f));
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_LinkStrength, 0.0f);
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinBorderWidth, 1.0f);
			ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinRadius, 5.0f);

			ax::NodeEditor::BeginNode(N->ID);

			ImGui::BeginVertical(N->ID.AsPointer());
			std::string InputsName = m_Name + "##" + "Inputs";
			ImGui::BeginHorizontal(InputsName.c_str());
			ImGui::Spring(0, padding * 2);

			ImRect InputsRect;
			int InputAlpha = 200;

			if (!N->Inputs.empty())
			{
				auto& Pin = N->Inputs[0];

				ImGui::Dummy(ImVec2(0, padding));
				ImGui::Spring(1, 0);
				InputsRect = ImGui_GetItemRect();


				ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinArrowSize, 10.0f);
				ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinArrowWidth, 10.0f);
				ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinCorners, ImDrawFlags_RoundCornersBottom);
				ax::NodeEditor::BeginPin(Pin->ID, ax::NodeEditor::PinKind::Input);
				ax::NodeEditor::PinPivotRect(InputsRect.GetTL(), InputsRect.GetBR());
				ax::NodeEditor::PinRect(InputsRect.GetTL(), InputsRect.GetBR());
				ax::NodeEditor::EndPin();
				ax::NodeEditor::PopStyleVar(3);

				if (newLinkPin && !CanCreateLink(newLinkPin, Pin) && Pin != newLinkPin)
				{
					InputAlpha = (int)(255 * ImGui::GetStyle().Alpha * (48.f / 255.f));
				}
			}
			else
			{
				ImGui::Dummy(ImVec2(0, padding));
			}

			ImGui::Spring(0, padding * 2);
			ImGui::EndHorizontal();

			ImGui::BeginHorizontal(std::string(m_Name + "##" + "content frame").c_str());
			ImGui::Spring(1, padding);

			ImGui::BeginVertical(std::string(m_Name + "##" + "content").c_str(), ImVec2(0.f, 0.f));
			ImGui::Dummy(ImVec2(160, 0));
			ImGui::Spring(1);
			ImGui::TextUnformatted(N->Name.c_str());
			ImGui::Spring(1);
			ImGui::EndVertical();

			auto ContentRect = ImGui_GetItemRect();

			ImGui::Spring(1, padding);
			ImGui::EndHorizontal();

			ImGui::BeginHorizontal(std::string(m_Name + "##" + "outputs").c_str());
			ImGui::Spring(0, padding * 2);

			ImRect OutputsRect;
			int OutputAlpha = 200;

			if (N->Outputs.empty())
			{
				auto& Pin = N->Outputs[0];
				ImGui::Dummy(ImVec2(0, padding));
				ImGui::Spring(1, 0);
				OutputsRect = ImGui_GetItemRect();

				ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PinCorners, ImDrawFlags_RoundCornersTop);
				ax::NodeEditor::BeginPin(Pin->ID, ax::NodeEditor::PinKind::Output);
				ax::NodeEditor::PinPivotRect(OutputsRect.GetTL(), OutputsRect.GetBR());
				ax::NodeEditor::PinRect(OutputsRect.GetTL(), OutputsRect.GetBR());
				ax::NodeEditor::EndPin();
				ax::NodeEditor::PopStyleVar();

				if (newLinkPin && !CanCreateLink(newLinkPin, Pin) && Pin != newLinkPin)
				{
					OutputAlpha = (int)(255 * ImGui::GetStyle().Alpha * (48.f / 255.f));
				}
			}
			else
			{
				ImGui::Dummy(ImVec2(0, padding));
			}

			ImGui::Spring(0, padding * 2);
			ImGui::EndHorizontal();

			ImGui::EndVertical();

			ax::NodeEditor::EndNode();
			ax::NodeEditor::PopStyleVar(7);
			ax::NodeEditor::PopStyleColor(4);

			auto DrawList = ax::NodeEditor::GetNodeBackgroundDrawList(N->ID);

			const auto    topRoundCornersFlags = ImDrawFlags_RoundCornersTop;
			const auto bottomRoundCornersFlags = ImDrawFlags_RoundCornersBottom;

			DrawList->AddRectFilled(
				InputsRect.GetTL() + ImVec2(0, 1), InputsRect.GetBR(),
				IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), InputAlpha),
				4.f, bottomRoundCornersFlags);

			//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
			DrawList->AddRect(InputsRect.GetTL() + ImVec2(0, 1), InputsRect.GetBR(),
				IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), InputAlpha), 4.0f, bottomRoundCornersFlags);
			//ImGui::PopStyleVar();
			DrawList->AddRectFilled(OutputsRect.GetTL(), OutputsRect.GetBR() - ImVec2(0, 1),
				IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), OutputAlpha), 4.0f, topRoundCornersFlags);
			//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
			DrawList->AddRect(OutputsRect.GetTL(), OutputsRect.GetBR() - ImVec2(0, 1),
				IM_COL32((int)(255 * pinBackground.x), (int)(255 * pinBackground.y), (int)(255 * pinBackground.z), OutputAlpha), 4.0f, topRoundCornersFlags);
			//ImGui::PopStyleVar();
			DrawList->AddRectFilled(ContentRect.GetTL(), ContentRect.GetBR(), IM_COL32(24, 64, 128, 200), 0.0f);
			//ImGui::PushStyleVar(ImGuiStyleVar_AntiAliasFringeScale, 1.0f);
			DrawList->AddRect(
				ContentRect.GetTL(),
				ContentRect.GetBR(),
				IM_COL32(48, 128, 255, 100), 0.0f);
			//ImGui::PopStyleVar();
		}
	}
	/**
 * @brief Draws and creates a new link between two pins.
 *
 * @param[out] newLinkPin The newly created link pin.
 * @param ShowLabelFunction A function to show labels with different colors.
 */
void AGE::NodeEditorWindow::DrawAndCreateNewLink(Ref<AGEPin>& newLinkPin, std::function<void(const char*, ImColor)>ShowLabelFunction)
	{
		if (ax::NodeEditor::BeginCreate(ImColor(255, 255, 255), 2.f))
		{
			ax::NodeEditor::PinId StartPinID = 0, EndPinID = 0;

			if (ax::NodeEditor::QueryNewLink(&StartPinID, &EndPinID))
			{
				auto StartPin = FindPin(StartPinID);
				auto EndPin = FindPin(EndPinID);

				newLinkPin = StartPin ? StartPin : EndPin;

				if (StartPin->Kind == ax::NodeEditor::PinKind::Input)
				{
					std::swap(StartPin, EndPin);
					std::swap(StartPinID, EndPinID);
				}

				if (StartPin && EndPin)
				{
					if (EndPin == StartPin)
					{
						ax::NodeEditor::RejectNewItem(ImColor(255, 0, 0), 2.f);
					}
					else if (EndPin->Kind == StartPin->Kind)
					{
						ShowLabelFunction("x Incompatible Pin Kind!", { 45,32,32,180 });
						ax::NodeEditor::RejectNewItem({ 255,0,0,255 }, 2.f);
					}
					else if (EndPin->Type != StartPin->Type && EndPin->Type != AGEPinType::Any)
					{
						ShowLabelFunction("x Incompatible Pin Types!", { 45,32,32,180 });
						ax::NodeEditor::RejectNewItem({ 255,128,128,255 }, 2.f);
					}
					else
					{
						ShowLabelFunction("+ Create Link", { 32,45,32,180 });
						if (ax::NodeEditor::AcceptNewItem({ 128,255,128,255 }, 4.f))
						{
							m_Links.emplace_back(CreateRef<AGENodeLink>((uint64_t)GetNextID(), StartPinID, EndPinID));
							m_Links.back()->Color = GetIconColor(StartPin->Type);

							if (EndPin->Type == AGEPinType::Any)
							{
								EndPin->Type = StartPin->Type;
							}

							switch (StartPin->Type)
							{
							case AGEPinType::Flow:
							{
								StartPin->Node->NextNode = EndPin->Node;
								StartPin->NextNodeID = EndPin->Node->ID;
								break;
							}
							case AGEPinType::Boolean:
							{
								EndPin->Boolean = StartPin->Boolean;
								break;
							}
							case AGEPinType::Int:      
							{
								EndPin->Integer = StartPin->Integer;
								break;
							}
							case AGEPinType::Int16:  
							{
								EndPin->Integer16 = StartPin->Integer16;
								break;
							}
							case AGEPinType::Int64:    
							{
								EndPin->Integer64 = StartPin->Integer64;
								break;
							}
							case AGEPinType::UInt16:   
							{
								EndPin->UInteger16 = StartPin->UInteger16;
								break;
							}
							case AGEPinType::UInt32:   
							{
								EndPin->UInteger32 = StartPin->UInteger32;
								break;
							}
							case AGEPinType::UInt64:   
							{
								EndPin->UInteger64 = StartPin->UInteger64;
								break;
							}
							case AGEPinType::Vector2D: 
							{
								
								EndPin->Vector2D = StartPin->Vector2D;
								break;
							}
							case AGEPinType::Vector3D: 
							{
								
								EndPin->Vector3D = StartPin->Vector3D;
								break;
							}
							case AGEPinType::Vector4D: 
							{
								EndPin->Vector4D = StartPin->Vector4D;
								break;
							}
							case AGEPinType::Float:    
							{
								EndPin->Value = StartPin->Value;
								break;
							}
							case AGEPinType::String:   
							{

								EndPin->String = StartPin->String;
								break;
							}
							case AGEPinType::Object:   
							{
								EndPin->ObjPtr = StartPin->ObjPtr;
								break;
							}
							case AGEPinType::Function: 
							{
								break;
							}
							case AGEPinType::Callback: 
							{
								break; 
							}
							default:
								return;
							}

						}
					}
				}
			}
		}
	}
	/**
 * @brief Draws and creates a new node in the Node Editor Window.
 * 
 * This function handles user interactions related to creating or drawing nodes within the NodeEditorWindow. It takes references to AGEPin objects, a boolean indicating whether a new node should be created, and a ShowLabelFunction that displays labels on the UI.
 */
void NodeEditorWindow::DrawAndCreateNewNode(Ref<AGEPin>& newLinkPin, Ref<AGEPin>& newNodeLinkPin, bool createNewNode, std::function<void(const char*, ImColor)> ShowLabelFunction)
	{
		ax::NodeEditor::PinId PinID = 0;

		if (ax::NodeEditor::QueryNewNode(&PinID))
		{
			newLinkPin = FindPin(PinID);
			if (newLinkPin->Type == AGEPinType::Flow)
			{
				if (newLinkPin)
				{
					ShowLabelFunction("+ Create Node", { 32,45,32,180 });
				}


				if (ax::NodeEditor::AcceptNewItem())
				{
					createNewNode = true;
					newNodeLinkPin = FindPin(PinID);
					newLinkPin = nullptr;
					ax::NodeEditor::Suspend();
					ImGui::OpenPopup("Create New Node");
					ax::NodeEditor::Resume();
				}
			}

		}

	}
	
void NodeEditorWindow::DeleteNode()
	{
		if (ax::NodeEditor::BeginDelete())
		{
			ax::NodeEditor::NodeId NID= 0;
			while (ax::NodeEditor::QueryDeletedNode(&NID))
			{
				if (ax::NodeEditor::AcceptDeletedItem())
				{
					auto id = std::find_if(m_Nodes.begin(), m_Nodes.end(), [NID](auto& Node)
						{
							return Node->ID == NID;
						});

					if (id != m_Nodes.end())
					{
						m_Nodes.erase(id);
					}
				}
			}

			ax::NodeEditor::LinkId LID = 0;

			while (ax::NodeEditor::QueryDeletedLink(&LID))
			{
				if (ax::NodeEditor::AcceptDeletedItem())
				{
					auto id = std::find_if(m_Links.begin(), m_Links.end(), [LID](auto& Link)
						{
							return Link->ID == LID;
						});

					if (id != m_Links.end())
					{
						m_Links.erase(id);
					}
				}
			}
			ax::NodeEditor::EndDelete();
		}
	}
	
	/**
 * @brief Handles the behavior of a splitter in an ImGui context.
 * 
 * This function determines whether the user is interacting with the splitter and updates the size variables accordingly.
 * It takes into account various parameters such as the direction, thickness, minimum sizes, etc.
 */
bool NodeEditorWindow::Splitter(bool SplitVertically, float Thickness, float* Size1, float* Size2, float Min_Size1, float Min_Size2, float SplitterLongAxisSize)
	{
		ImGuiContext& G = *GImGui;
		ImGuiWindow* Window = G.CurrentWindow;
		ImGuiID ID = Window->GetID("##Splitter");
		ImRect BB;
		BB.Min = Window->DC.CursorPos + (SplitVertically ? ImVec2(*Size1, 0.f) : ImVec2(0.f, *Size1));
		BB.Max = BB.Min + ImGui::CalcItemSize(SplitVertically ? ImVec2(Thickness, SplitterLongAxisSize) : ImVec2(SplitterLongAxisSize, Thickness), 0.f, 0.f);
		
		return ImGui::SplitterBehavior(BB, ID, SplitVertically ? ImGuiAxis_X : ImGuiAxis_Y, Size1, Size2, Min_Size1, Min_Size2, 0.f);
	}
	/**
 * @brief Spawns a new Begin Play node and adds it to the nodes list.
 * 
 * This function creates a new instance of AGENode with specific attributes, such as name ("Begin Play"), color (ImColor(255,128,128)), and pin type (AGEPinType::Flow). It then adds this node to the m_Nodes list. The function returns a reference to the newly created node.
 * 
 * @return Ref<AGENode> A reference to the newly spawned Begin Play node.
 */
Ref<AGENode> NodeEditorWindow::SpawnBeginPlayNode() //Change to BeginPlay and Duplicate of OnUpdate
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Begin Play", ImColor(255,128,128)));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));

		m_Nodes.back()->bIsBeginPlay = true;
		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnOnUpdateNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "On Update", ImColor(255, 128, 128)));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Delta Time", AGEPinType::Float));

		m_Nodes.back()->bIsOnUpdate = true;

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "OnUpdate";
		m_Nodes.back()->Func.Entt = nullptr;

		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	/**
 * @brief Spawns an output action node with two outputs - "Condition" and "Event". 
 *        The first output is of type Float, the second is of type Boolean.
 * @return A reference to the newly created AGENode object.
 */
Ref<AGENode> NodeEditorWindow::SpawnOutputActionNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Output Action"));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Sample", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Condition", AGEPinType::Boolean));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Event", AGEPinType::Callback));

		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnPrintStringNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Print String"));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "In String", AGEPinType::String));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Condition", AGEPinType::Boolean));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Draw String";
		m_Nodes.back()->Func.Entt = m_Target.get();
		//Ptr->Inputs[1]->String, Font::GetDefault(), Entt->GetComponent<TransformComponent>().GetTransform(), Vector4(1.f)
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs[1]->String);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(s_Font);
		Matrix4D Transform = m_Nodes.back()->Func.Entt->GetComponent<TransformComponent>().GetTransform();
		m_Nodes.back()->FunctionArgs.Args.emplace_back(Transform);
		Vector4 Color{1.f};
		m_Nodes.back()->FunctionArgs.Args.emplace_back(Color);
		m_Nodes.back()->Func.bIsUtilFunction = true;


		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	/**
 * @brief Spawns a less than node in the graph.
 * 
 * This function creates a new AGENode with two input pins of type float and one output pin of type boolean, representing a simple comparison operation (less than). The node is then added to the m_Nodes vector.
 * 
 * @return Ref<AGENode> A reference to the newly created less than node.
 */
Ref<AGENode> NodeEditorWindow::SpawnLessThanNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "<", ImColor(128, 195, 248)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Boolean));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Less Than";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());

		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnGreaterThanNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), ">", ImColor(128, 195, 248)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Boolean));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Greater Than";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());

		return m_Nodes.back();
	}
	COMMENT:
/**
 * @brief Spawns an equal to node with two float inputs and one boolean output. The function creates a new AGENode object, assigns it an ID, type, color, and pins, sets the util function properties, builds the node, and returns it.
 * 
 * @return Ref<AGENode> A reference to the newly created equal to node.
 */
CONFIDENCE: 1.0;

Ref<AGENode> NodeEditorWindow::SpawnEqualToNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "=", ImColor(128, 195, 248)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Boolean));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Equal To";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());

		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnGTETNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), ">=", ImColor(128, 195, 248)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Boolean));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Greater Than or Equal To";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());

		return m_Nodes.back();
	}
	/**
 * @brief Spawns a Less Than or Equal To (<=) node with two float inputs and one boolean output.
 * 
 * This function creates an AGENode of type Simple, with two input pins of type Float and one output pin of type Boolean. The node's ID is set to the next available ID, its label is set to "<=", and its color is set to a light blue (128, 195, 248).
 * It also sets up the function details for this node: it references itself, stores the reference ID as the node's ID, sets the value string to "Less Than or Equal To", and sets the entity handle to null. The bIsUtilFunction flag is set to true. Finally, it calls BuildNode with the newly created node as an argument.
 * 
 * @return Ref<AGENode> A reference to the newly spawned Less Than or Equal To (<=) node.
 */
Ref<AGENode> NodeEditorWindow::SpawnLTETNode()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "<=", ImColor(128, 195, 248)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Boolean));
		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Less Than or Equal To";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());

		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnMakeLiteralString()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Make String", ImColor(124, 21, 153)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::String));
		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Make String";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	/**
 * @brief Spawns a new node with the type "Append String" and adds it to the nodes list. 
 * The function creates an instance of AGENode, sets its properties, and then calls BuildNode() on this newly created object.
 * It also emplaces two input pins (one for each string) and one output pin into the node's Inputs and Outputs vectors respectively.
 * @return A reference to the new append string node.
 */
Ref<AGENode> NodeEditorWindow::SpawnAppendString()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Append String", ImColor(124, 21, 153)));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::String));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::String));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::String));
		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Append String";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->Func.bIsUtilFunction = true;

		BuildNode(m_Nodes.back());
		return m_Nodes.back();
	}
	
Ref<AGENode> NodeEditorWindow::SpawnGetLocation2D()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Get 2D Location", ImColor(C::Aquamarine[0], C::Aquamarine[1], C::Aquamarine[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Object", AGEPinType::Object));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector2D));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "GetActorLocation";
		if (m_Nodes.back()->Inputs.back()->ObjPtr)
		{
			m_Nodes.back()->Func.Entt = m_Nodes.back()->Inputs.back()->ObjPtr.get();
			m_Nodes.back()->Func.EnttID = m_Nodes.back()->Inputs.back()->ObjPtr->GetID();
		}
		else
		{
			m_Nodes.back()->Func.Entt = m_Target.get();
			m_Nodes.back()->Func.EnttID = m_Target->GetID();
		}


		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSetLocation2D()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Set 2D Location", ImColor(C::Aquamarine[0], C::Aquamarine[1], C::Aquamarine[2])));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Object", AGEPinType::Object));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector2D));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "SetActorLocation";
		if (m_Nodes.back()->Inputs.back()->ObjPtr)
		{
			m_Nodes.back()->Func.Entt = m_Nodes.back()->Inputs.back()->ObjPtr.get();
			m_Nodes.back()->Func.EnttID = m_Nodes.back()->Inputs.back()->ObjPtr->GetID();
		}
		else
		{
			m_Nodes.back()->Func.Entt = m_Target.get();
			m_Nodes.back()->Func.EnttID = m_Target->GetID();
		}

		return m_Nodes.back();
	}

	/**
 * @brief Spawns a new Get Location 3D node in the Node Editor Window.
 * This function creates an instance of AGENode with specific properties and configurations, such as name, color, type, inputs, outputs, etc. It also sets up the function details for this node including reference to itself, ID of its object, value of the function, entity pointer and its ID. 
 * @return A Ref<AGENode> instance representing the newly created Get Location 3D node.
 */
Ref<AGENode> NodeEditorWindow::SpawnGetLocation3D()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Get 3D Location", ImColor(C::Aquamarine[0], C::Aquamarine[1], C::Aquamarine[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Object", AGEPinType::Object));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "GetActorLocation";
		if (m_Nodes.back()->Inputs.back()->ObjPtr)
		{
			m_Nodes.back()->Func.Entt = m_Nodes.back()->Inputs.back()->ObjPtr.get();
			m_Nodes.back()->Func.EnttID = m_Nodes.back()->Inputs.back()->ObjPtr->GetID();

		}
		else
		{
			m_Nodes.back()->Func.Entt = m_Target.get();
			m_Nodes.back()->Func.EnttID = m_Target->GetID();
		}
		BuildNode(m_Nodes.back());


		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSetLocation3D()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Set 3D Location", ImColor(C::Aquamarine[0], C::Aquamarine[1], C::Aquamarine[2])));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "Object", AGEPinType::Object));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Flow));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "SetActorLocation";
		if (m_Nodes.back()->Inputs.back()->ObjPtr)
		{
			m_Nodes.back()->Func.Entt = m_Nodes.back()->Inputs.back()->ObjPtr.get();
			m_Nodes.back()->Func.EnttID = m_Nodes.back()->Inputs.back()->ObjPtr->GetID();
		}
		else
		{
			m_Nodes.back()->Func.Entt = m_Target.get();
			m_Nodes.back()->Func.EnttID = m_Target->GetID();
		}
		return m_Nodes.back();
	}

	/**
 * @brief Spawns a new node of type "To String" and adds it to the nodes list. The function creates an instance of AGENode with specific properties, such as name, color, input pin type, output pin type etc., then builds the node using BuildNode() method. It also sets some additional properties for the created node like reference, ID, value, entity, and whether it is a utility function or not.
 * 
 * @return Ref<AGENode> A reference to the newly spawned AGENode instance.
 */
Ref<AGENode> NodeEditorWindow::SpawnToString()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "To String", ImColor(C::Chocolate[0], C::Chocolate[1], C::Chocolate[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Any));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::String));
		BuildNode(m_Nodes.back());
		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Convert To String";
		m_Nodes.back()->Func.Entt = nullptr;
		m_Nodes.back()->FunctionArgs.Args.emplace_back(m_Nodes.back()->Inputs.back()->Type);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(m_Nodes.back()->Inputs.back()->GetValue(m_Nodes.back()->Inputs.back()->Type));
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnGetActor()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Get Actor", ImColor(C::Cyan[0], C::Cyan[1], C::Cyan[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Object));
		m_Nodes.back()->Outputs.back()->ObjPtr = m_Target;
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Get Actor";
		m_Nodes.back()->Func.Entt = m_Target.get();
		m_Nodes.back()->Func.EnttID = m_Target->GetID();

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSum()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Sum", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Sum";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;


		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSubtract()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Subtract", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Subtract";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnMultiply()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Multiply", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Multiply";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	"/**\n * @brief SpawnDivide creates a new divide node in the graph and adds it to the nodes list.\n * The function creates an AGENode with two float inputs and one output, sets its type as Simple,\n * builds the node, assigns a reference to itself for use in the execution context,\n * and finally returns the newly created node.\n * @return Ref<AGENode> A reference to the newly spawned divide node.\n */"
Ref<AGENode> NodeEditorWindow::SpawnDivide()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Divide", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Divide";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnModulo()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Modulo", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Int));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Int));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Int));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Modulo";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	/**
 * @brief Spawns a new AGENode with type 'Pow'.
 * 
 * This function creates a new AGENode of type 'Pow' with two input pins and one output pin, all of which are of Float type. It also sets up the necessary properties for this node to be used as an util function.
 * 
 * @return Ref<AGENode> A reference to the newly created Pow AGENode.
 */
Ref<AGENode> NodeEditorWindow::SpawnPow()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Pow", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());


		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Pow";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.back()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSquareRoot()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Square Root", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Square Root";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnCubeRoot()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Cube Root", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Cube Root";
		m_Nodes.back()->FunctionArgs.Args.emplace_back(&m_Nodes.back()->Inputs.front()->Value);
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	/**
 * @brief Spawns a new node representing the dot product operation in the graph.
 * The function creates an AGENode with specific properties and adds it to the nodes list of the NodeEditorWindow instance. 
 * It also sets up the inputs, outputs, and utilities for this particular node.
 * @return A reference to the newly created AGENode.
 */
Ref<AGENode> NodeEditorWindow::SpawnDotProduct()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Dot", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Dot Product";
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnCrossProduct()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Cross", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Vector3D));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Cross Product";
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnCosine()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Cosine", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Cosine";
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
Ref<AGENode> NodeEditorWindow::SpawnSine()
	{
		m_Nodes.emplace_back(CreateRef<AGENode>(GetNextID(), "Sine", ImColor(C::Orange[0], C::Orange[1], C::Orange[2])));
		m_Nodes.back()->Type = AGENodeType::Simple;
		m_Nodes.back()->Inputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		m_Nodes.back()->Outputs.emplace_back(CreateRef<AGEPin>(GetNextID(), "", AGEPinType::Float));
		BuildNode(m_Nodes.back());

		m_Nodes.back()->Func.Reference = m_Nodes.back();
		m_Nodes.back()->Func.RefID = (uint64_t)m_Nodes.back()->ID;
		m_Nodes.back()->Func.Val = "Sine";
		m_Nodes.back()->Func.bIsUtilFunction = true;

		return m_Nodes.back();
	}

	
void NodeEditorWindow::RegisterFunctions()
	{
		if (m_Target)
		{
			Ref<AGENode> BeginPlayNode;
			Ref<AGENode> OnUpdateNode;
			for (auto& N : m_Nodes)
			{
				if (N->bIsBeginPlay)
				{
					BeginPlayNode = N;
				}

				if (N->bIsOnUpdate)
				{
					OnUpdateNode = N;
				}

				if (BeginPlayNode && OnUpdateNode)
				{
					break;
				}

			}

			Ref<AGENode> Next;
			Next = BeginPlayNode->NextNode;
			while (Next)
			{
				m_Target->AddBeginPlayFunctions(Next->Func);
				Next = Next->NextNode;
			}

			Next = OnUpdateNode->NextNode;
			while (Next)
			{
				m_Target->AddTickFunctions(Next->Func);
				Next = Next->NextNode;
			}
		}

	}

	/** 
 * @brief Deregisters all functions from the target node.
 *
 * This function is used to remove all registered functions from the target node. It calls the ClearFunctions() method on the m_Target object, which presumably clears any previously registered functions.
 *
 * @return void
 */
void NodeEditorWindow::DeregisterFunctions()
	{
		m_Target->ClearFunctions();
	}

	/**
 * @brief Synchronizes the links between nodes.
 *
 * This function iterates over all the links in the NodeEditorWindow and updates the corresponding pins based on the type of pin. 
 * It handles different types of pins such as Boolean, Int, Float, String etc., by copying the value from the start pin to the end pin.
 * The function does not return any values.
 */
void NodeEditorWindow::SyncLinks()
	{
		for (auto& L : m_Links)
		{
			Ref<AGEPin> StartPin = FindPin(L->StartPinID);
			Ref<AGEPin> EndPin = FindPin(L->EndPinID);

			switch (EndPin->Type)
			{
			case AGEPinType::Boolean:      EndPin->Boolean = StartPin->Boolean; break;
			case AGEPinType::Int:       EndPin->Integer = StartPin->Integer; break;
			case AGEPinType::Int16:     EndPin->Integer16 =  StartPin->Integer16; break;
			case AGEPinType::Int64:     EndPin->Integer64 =  StartPin->Integer64; break;
			case AGEPinType::UInt16:    EndPin->UInteger16 = StartPin->UInteger16; break;
			case AGEPinType::UInt32:    EndPin->UInteger32 = StartPin->UInteger32; break;
			case AGEPinType::UInt64:    EndPin->UInteger64 = StartPin->UInteger64; break;
			case AGEPinType::Vector2D:  EndPin->Vector2D = StartPin->Vector2D; break;
			case AGEPinType::Vector3D:  EndPin->Vector3D = StartPin->Vector3D; break;
			case AGEPinType::Vector4D:  EndPin->Vector4D = StartPin->Vector4D; break;
			case AGEPinType::Float:     EndPin->Value = StartPin->Value; break;
			case AGEPinType::String:    EndPin->String = StartPin->String; break;
			case AGEPinType::Object:    EndPin->ObjPtr = StartPin->ObjPtr; break;
			//case AGEPinType::Function:  EndPin-> = StartPin->Boolean; break;
			//case AGEPinType::Callback:  EndPin-> = StartPin->Boolean; break;
			default:break;
			}
			
		}
	}
	/**
 * @brief Displays a menu with various options for creating and assigning nodes.
 * 
 * Depending on the user's selection, different types of nodes are created using Spawn*Node() functions (where '*' can be any node type) and assigned to the input parameter 'Node'.
 * 
 * @param Node A reference to an AGENode object that will be modified by this function. The type of node created depends on which ImGui::MenuItem is selected.
 */
void NodeEditorWindow::ShowNodeOptions(Ref<AGENode>& Node)
	{
		if (ImGui::MenuItem("Begin Play"))
		{
			Node = SpawnBeginPlayNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("On Update"))
		{
			Node = SpawnOnUpdateNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Print String"))
		{
			Node = SpawnPrintStringNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Less Than?"))
		{
			Node = SpawnLessThanNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Greater Than?"))
		{
			Node = SpawnGreaterThanNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Equal To?"))
		{
			Node = SpawnEqualToNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Less Than or Equal To?"))
		{
			Node = SpawnLTETNode();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Greater Than or Equal To?"))
		{
			Node = SpawnGTETNode();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Make String"))
		{
			Node = SpawnMakeLiteralString();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Append String"))
		{
			Node = SpawnAppendString();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Get 2D Location"))
		{
			Node = SpawnGetLocation2D();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Set 2D Location"))
		{
			Node = SpawnSetLocation2D();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Get 3D Location"))
		{
			Node = SpawnGetLocation3D();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Set 3D Location"))
		{
			Node = SpawnSetLocation3D();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("To String"))
		{
			Node = SpawnToString();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Get Actor"))
		{
			Node = SpawnGetActor();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Sum"))
		{
			Node = SpawnSum();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Subtract"))
		{
			Node = SpawnSubtract();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Multiply"))
		{
			Node = SpawnMultiply();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Divide"))
		{
			Node = SpawnDivide();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Modulo"))
		{
			Node = SpawnModulo();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Pow"))
		{
			Node = SpawnPow();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Square Root"))
		{
			Node = SpawnSquareRoot();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Cube Root"))
		{
			Node = SpawnCubeRoot();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Dot Product"))
		{
			Node = SpawnDotProduct();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Cross Product"))
		{
			Node = SpawnCrossProduct();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Cosine"))
		{
			Node = SpawnCosine();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Sine"))
		{
			Node = SpawnSine();
			ImGui::CloseCurrentPopup();
		}
	}
	/**
 * @brief This function is used to rebuild the window. It sets m_IsOpen to true, indicating that the window should be rebuilt.
 * @return void
 */
void NodeEditorWindow::RebuildWindow()
	{
		m_IsOpen = true;
	}

	/**
 * @brief Saves the graph to a file in the game content directory.
 * 
 * This function retrieves the application configuration and uses it to generate the path for saving the graph. The graph itself is written using a FileStreamWriter, which writes an object of type NodeEditorWindow to the specified file path.
 * 
 * @return void
 */
void NodeEditorWindow::SaveGraph()
	{
		AppConfig Config = App::Get().GetAppConfig();
		std::string Path = Config.GameContentPath.string() + "VisualScripting/" + m_Name + ".AGEasset";
		FileStreamWriter Stream(Path);
		Stream.WriteObject<NodeEditorWindow>(*this);
	}

	/**
 * @brief Compiles the graph and saves it if successful.
 * 
 * This function compiles all nodes in the graph, sets their arguments, checks for any errors during compilation, syncs links, and finally saves the graph to a file if everything was successful.
 * It also logs an info message with the name of the saved graph and its path if the compilation is successful or an error message otherwise.
 */
void NodeEditorWindow::CompileGraph()
	{
		AppConfig Config = App::Get().GetAppConfig();
		bool bWasCompilationSuccessful = true;
		std::string Path = Config.GameContentPath.string() + "VisualScripting/" + m_Name + ".AGEasset";

		std::sort(m_Nodes.begin(), m_Nodes.end());
		for (auto& N : m_Nodes)
		{
			N->SetNodeFuncArguments();
			if (!N->CompileOutputPins())
			{
				bWasCompilationSuccessful = false;
			}
			SyncLinks();
		}


		if (bWasCompilationSuccessful)
		{
			SaveGraph();
			CoreLogger::Info("{} was saved to {}", m_Name, Path);
		}
		else
		{
			CoreLogger::Error("Compilation was unsuccessful!");
		}
	}
}

