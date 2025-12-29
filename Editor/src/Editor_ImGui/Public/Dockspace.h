#pragma once

#include <Core/Public/Layer.h>
#include <imgui.h>

typedef unsigned int ImGuiID;
typedef int ImGuiDockNodeFlags;
struct ImGuiViewport;
struct ImGuiWindowClass;


class DockSpace : public AGE::Layer
{
public:
	DockSpace();
	~DockSpace();


	//ImGui Says if I want to start a window as a dockspace in code I have to implement this myself and tweak it. T.H.'d from: imgui.cpp
	static void MakeDockspace(/**const ImGuiViewport* viewport = (const ImGuiViewport*)0, ImGuiDockNodeFlags dockspace_flags = 0, const ImGuiWindowClass* window_class = (const ImGuiWindowClass*)0*/);
};