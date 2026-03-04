#include "Editor_ImGui/Public/AssetRegistryWindow.h"
#include "Assets/Public/AssetManager.h"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wnontrivial-memcall"
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui.h>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui.h>
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <imgui.h>
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

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
			ImGui::Text( "%s", std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s", S.second->GetName().c_str());
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
			ImGui::Text( "%s",std::to_string(T.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",T.second->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",T.second->GetTextureFilePath().c_str());
			ImGui::TableNextColumn();

		}

		ImGui::EndTable();
	}

	static void DrawFontsTable(std::unordered_map<UUID, Ref<AGEFont>>& Fonts)
	{
		ImGui::TableSetupColumn("ID Number");
		ImGui::TableSetupColumn("Asset Name");
		ImGui::TableSetupColumn("Asset Filepath");
		ImGui::TableHeadersRow();
		ImGui::TableNextColumn();

		for (auto& F : Fonts)
		{
			ImGui::Text( "%s",std::to_string(F.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",F.second->GetAtlasTexture()->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",F.second->GetAtlasTexture()->GetTextureFilePath().c_str());
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
			ImGui::Text( "%s",std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",S.second->GetName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",S.second->GetFilePath().c_str());
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
			ImGui::Text( "%s",std::to_string(S.first).c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",S.second->GetBankName().c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s",S.second->GetFilePath().generic_string().c_str());
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
			ImGui::Text( "%s",S.first.c_str());
			ImGui::TableNextColumn();
			ImGui::Text( "%s","NULL");
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
			ImGui::Text( "%s","Asset Registry");
			ImGui::Dummy(Spacer);
			ImGui::Text( "%s","Scenes");
			if (!ImGui::BeginTable("##Scenes", 2))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}

			std::unordered_map<UUID, Ref<Scene>> Scenes = Registry->GetScenes();
			DrawScenesTable(Scenes);
			ImGui::Dummy(Spacer);
			ImGui::Text( "%s","Textures");
			if (!ImGui::BeginTable("##Textures", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}

			std::unordered_map<UUID, Ref<Texture2D>> TextureAssets = Registry->GetTextures();
			DrawTexturesTable(TextureAssets);
			ImGui::Dummy(Spacer);

			ImGui::Text( "%s","Fonts");
			if (!ImGui::BeginTable("Fonts", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<AGEFont>> Fonts = Registry->GetFonts();
			DrawFontsTable(Fonts);
			ImGui::Dummy(Spacer);

			ImGui::Text( "%s","Sounds");
			if (!ImGui::BeginTable("Sounds", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<AudioSource>> Sounds = Registry->GetSounds();
			DrawSoundsTable(Sounds);
			ImGui::Dummy(Spacer);

			ImGui::Text( "%s","Soundbanks");
			if (!ImGui::BeginTable("Banks", 3))
			{
				ImGui::EndTable();
				ImGui::End();
				return;
			}
			std::unordered_map<UUID, Ref<SoundBank>> Banks = Registry->GetSoundbanks();
			DrawSoundbankTable(Banks);
			ImGui::Dummy(Spacer);

			ImGui::Text( "%s","Shaders");
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