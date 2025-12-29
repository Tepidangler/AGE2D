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

	class IniSerializer
	{
	public:
		IniSerializer(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings);

		bool Serialize(const std::filesystem::path& FilePath, const std::string& FileName);
		bool Deserialize(const std::filesystem::path& FilePath, const std::string& FileName);

	private:
		std::vector<std::pair<std::string, std::vector<uint8_t>>> m_AxisBindings;
		std::vector<std::pair<std::string, std::vector<uint8_t>>> m_ActionBindings;
	};
}