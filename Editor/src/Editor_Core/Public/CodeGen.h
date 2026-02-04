//
// Created by gdmgp on 2/3/2026.
//

#ifndef AGE2D_CODEGEN_H
#define AGE2D_CODEGEN_H
#pragma once
#include <string>

namespace AGE
{
	enum class AssetType
	{
		INVALID,
		Widget,
		Actor,
		AIController,
		AudioController,
		CameraController,
		PlayerController,
		InputComponent,
		GameState,
		Interactable,
		Armor,
		Item,
		Weapon

	};

	class CodeGen
	{
	public:
		virtual ~CodeGen() = default;

		static bool CreateAsset(const std::string& FileName, AssetType Type);
	protected:
		virtual bool CreateHeader(const std::string& FileName) = 0;
		virtual bool CreateHeaderNS(const std::string& FileName, const std::string& Namespace) = 0;
		virtual bool CreateSource(const std::string& FileName) = 0;
		virtual bool CreateSourceNS(const std::string& FileName, const std::string& Namespace) = 0;
	};

	class WidgetCodeGen : public CodeGen
	{
		public:
		WidgetCodeGen() = default;
		~WidgetCodeGen() = default;
	protected:
		bool CreateHeader(const std::string& FileName) override;
		bool CreateHeaderNS(const std::string& FileName, const std::string& Namespace) override;
		bool CreateSource(const std::string& FileName) override;
		bool CreateSourceNS(const std::string& FileName, const std::string& Namespace) override;
	};

} // AGE

#endif //AGE2D_CODEGEN_H