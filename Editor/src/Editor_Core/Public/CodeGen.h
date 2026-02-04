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
	};

	class CodeGen
	{
	public:
		CodeGen() = default;
		virtual ~CodeGen() = default;

		bool CreateFile(const std::string& FileName, AssetType Type);
	protected:
		virtual bool CreateFileNS(const std::string& FileName) = 0;
		virtual bool CreateHeader(const std::string& FileName) = 0;
		virtual bool CreateHeaderNS(const std::string& FileName, const std::string& Namespace) = 0;
		virtual bool CreateSource(const std::string& FileName) = 0;
		virtual bool CreateSourceNS(const std::string& FileName, const std::string& Namespace) = 0;
	};

	class WidgetCodeGen : public CodeGen
	{
		public:
		WidgetCodeGen() = default;
		virtual ~WidgetCodeGen() = default;
	protected:
		bool CreateHeader(const std::string& FileName) override;
		virtual bool CreateHeaderNS(const std::string& FileName, const std::string& Namespace) = 0;
		bool CreateSource(const std::string& FileName) override;
		virtual bool CreateSourceNS(const std::string& FileName, const std::string& Namespace) = 0;
	};

} // AGE

#endif //AGE2D_CODEGEN_H