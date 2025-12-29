project "DirectX12"
	kind "StaticLib"
	language "C++"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"**.h",
		"**.hpp"
	}

    filter "system:windows"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

     filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"
