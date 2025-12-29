workspace "LibXML"
	architecture "x64"
	startproject "LibXML"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "LibXML"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"**.c"
	}

	defines
	{
		"LIBXML_STATIC",
		"LIBXML_READER_ENABLED",
		"LIBXML_WRITER_ENABLED",
		"LIBXML_TREE_ENABLED",
		"LIBXML_THREAD_ENABLED",
		"LIBXML_THREAD_ALLOC_ENABLED"

	}

	includedirs
	{
		"./include",
	}

	filter "system:windows"
		systemversion "latest"
		flags{}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"