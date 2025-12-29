#include "Editor_ImGui/Public/ConsoleLog.h"
#include <Age.h>
#include <imgui.h>

namespace AGE
{
	void ConsoleLogWindow::OnImGuiRender()
	{
		if (ImGui::Begin("ConsoleWindow"))
		{
			auto& Logs = Log::GetLogs();
			auto& LineOffsets = Log::GetOffsets();
			auto& LogTypes = Log::GetTypes();
			
			if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
			{

				const char* Buf = &Logs.front();
				const char* Buf_End = &Logs.back();
				ImGuiListClipper clipper;
				clipper.Begin((int)LineOffsets.size());
				while (clipper.Step())
				{
					for (int l = clipper.DisplayStart; l < clipper.DisplayEnd; l++)
					{
						const char* line_start = Buf + LineOffsets[l];
						const char* line_end = (l + 1 < LineOffsets.size()) ? (Buf + LineOffsets[l + 1] - 1) : Buf_End;
						if (LogTypes.size() > l)
						{
							switch (LogTypes[l])
							{
							case LogType::Trace:
							{
								ImGui::PushStyleColor(ImGuiCol_Text, { 1.f,1.f,1.f,1.f });
								ImGui::TextUnformatted(line_start, line_end);
								ImGui::PopStyleColor();
								break;
							}
							case LogType::Info:
							{
								ImGui::PushStyleColor(ImGuiCol_Text, { 0.f,.39f,0.f,1.f });
								ImGui::TextUnformatted(line_start, line_end);
								ImGui::PopStyleColor();
								break;
							}
							case LogType::Warn:
							{
								ImGui::PushStyleColor(ImGuiCol_Text, { 1.f,1.f,0.f,1.f });
								ImGui::TextUnformatted(line_start, line_end);
								ImGui::PopStyleColor();
								break;
							}
							case LogType::Error:
							{
								ImGui::PushStyleColor(ImGuiCol_Text, { 1.f,0.f,0.f,1.f });
								ImGui::TextUnformatted(line_start, line_end);
								ImGui::PopStyleColor();
								break;
							}
							case LogType::Critical:
							{
								ImGui::PushStyleColor(ImGuiCol_Text, { 1.f,0.f,0.f,1.f });
								ImGui::TextUnformatted(line_start, line_end);
								ImGui::PopStyleColor();
								break;
							}

							}
						}
						else
						{
							ImGui::TextUnformatted(line_start, line_end);
						}
					}
				}
				clipper.End();
			}
			ImGui::EndChild();
			ImGui::End();
		}

	}
}