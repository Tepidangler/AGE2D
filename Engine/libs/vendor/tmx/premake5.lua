project "libtmx"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	defines{
		"LIBXML_STATIC"
	}

	files
	{
		"include/**.h",
		"src/**.h",
		"src/**.c"
	}
	--LibraryDir["LibXML2"] = "Engine/libs/vendor/libxml2/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/libxml2"

	--libdirs(LibraryDir)


	includedirs
	{
		"include/",
		"src/",

	}
	defines 
	{ 
		"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }
		links
		{
			"../libxml2/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/LibXML/LibXML"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"
		links
		{
			"../libxml2/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/LibXML/LibXML"
		}

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"
