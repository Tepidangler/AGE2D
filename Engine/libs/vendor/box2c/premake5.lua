project "Box2D"
	kind "StaticLib"
	language "C"
	cppdialect "C++17"
	cdialect "C11"
	vectorextensions "SSE2"
	staticruntime "on"
	buildoptions {"/experimental:c11atomics"}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
		"include/**.h"
	}

	includedirs
	{
		"include",
		"src",
		"extern/simde"
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