#pragma once
#include "Scene/Public/Scene.h"
#include "Project/Public/Project.h"

namespace AGE
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& S);

		void Serialize(const std::string& FilePath);

		bool Deserialize(const std::string& FilePath);

	private:
		Ref<Scene> m_Scene;
	};

	class ProjectSerializer
	{
	public:
		ProjectSerializer(Ref<Project> Project);

		bool Serialize(const std::filesystem::path& FilePath);
		void SerializeBinary(const std::filesystem::path& FilePath);
		bool Deserialize(const std::filesystem::path& FilePath);
		bool DeserializeBinary(const std::filesystem::path& FilePath);
	private:

		Ref<Project> m_Project;
	};
}