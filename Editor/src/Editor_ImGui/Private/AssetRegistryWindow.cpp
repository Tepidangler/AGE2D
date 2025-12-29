#include "Editor_ImGui/Public/AssetRegistryWindow.h"
#include <imgui.h>
#include "Assets/Public/AssetManager.h"

namespace AGE
{
	static void DrawScenesTable(std::unordered_map<UUID, Ref<Scene>>& Scenes)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& S : Scenes)
		{
			ImGui::Text(std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(S.second->GetName().c_str());
			ImGui::TableNextColumn();
		}
		ImGui::EndTable();
	}

	static void DrawTexturesTable(std::unordered_map<UUID, Ref<Texture2D>>& Textures)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& T : Textures)
		{
			ImGui::Text(std::to_string(T.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(T.second->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(T.second->GetTextureFilePath().c_str());
			ImGui::TableNextColumn();

		}

		ImGui::EndTable();
	}

	static void DrawFontsTable(std::unordered_map<UUID, Ref<Font>>& Fonts)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& F : Fonts)
		{
			ImGui::Text(std::to_string(F.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(F.second->GetAtlasTexture()->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(F.second->GetAtlasTexture()->GetTextureFilePath().c_str());
			ImGui::TableNextColumn();
		}

		ImGui::EndTable();
	}
	
	static void DrawSoundsTable(std::unordered_map<UUID, Ref<AudioSource>>& Sounds)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& S : Sounds)
		{
			ImGui::Text(std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(S.second->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(S.second->GetFilePath().c_str());
			ImGui::TableNextColumn();
		}

		ImGui::EndTable();
	}

	static void DrawSoundbankTable(std::unordered_map<UUID, Ref<SoundBank>>& Sounds)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& S : Sounds)
		{
			ImGui::Text(std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text(S.second->GetBankName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text(S.second->GetFilePath().generic_string().c_str());
			ImGui::TableNextColumn();
		}

		ImGui::EndTable();
	}

	static void DrawShadersTable(Ref<ShaderLibrary>& Shaders)
	{
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& S : Shaders->GetLibrary())
		{
			ImGui::Text(S.first.c_str());
			ImGui::TableNextColumn();
			ImGui::Text("NULL");
			ImGui::TableNextColumn();
		}

		ImGui::EndTable();
	}
	void AssetRegistryWindow::OnImGuiRender()
	{
		if (bOpened)
		{
			RenderWindow("Asset Registry Window", &bOpened);
		}
	}
	void AssetRegistryWindow::RenderWindow(const char* WindowName, bool* IsOpen)
	{
		if (ImGui::Begin(WindowName, IsOpen))
		{
			ImVec2 Spacer = { 0.f,10.f };
			Ref<AssetRegistry> Registry = AssetManager::Get().GetAssetRegistry();
			ImGui::Text("Asset Registry");
			ImGui::Dummy(Spacer);
			ImGui::Text("Scenes");
			if (!ImGui::BeginTable("##Scenes", 2))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}

			std::unordered_map<UUID, Ref<Scene>> Scenes = Registry->GetScenes();
			DrawScenesTable(Scenes);
			ImGui::Dummy(Spacer);
			ImGui::Text("Textures");
			if (!ImGui::BeginTable("##Textures", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}

			std::unordered_map<UUID, Ref<Texture2D>> TextureAssets = Registry->GetTextures();
			DrawTexturesTable(TextureAssets);
			ImGui::Dummy(Spacer);

			ImGui::Text("Fonts");
			if (!ImGui::BeginTable("Fonts", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<Font>> Fonts = Registry->GetFonts();
			DrawFontsTable(Fonts);
			ImGui::Dummy(Spacer);

			ImGui::Text("Sounds");
			if (!ImGui::BeginTable("Sounds", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<AudioSource>> Sounds = Registry->GetSounds();
			DrawSoundsTable(Sounds);
			ImGui::Dummy(Spacer);

			ImGui::Text("Soundbanks");
			if (!ImGui::BeginTable("Banks", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<SoundBank>> Banks = Registry->GetSoundbanks();
			DrawSoundbankTable(Banks);
			ImGui::Dummy(Spacer);

			ImGui::Text("Shaders");
			if (!ImGui::BeginTable("Shaders", 2))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			Ref<ShaderLibrary> Shaders = Registry->GetShaders();
			DrawShadersTable(Shaders);

			ImGui::End();
		}
	}
	void AssetRegistryWindow::RestoreWindow()
	{
		bOpened = true;
	}
}