workspace "Sable"
	architecture "x64"
	startproject "Sable"

	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Shake_Engine/vendor/GLFW/include"
IncludeDir["GLAD"] = "Shake_Engine/vendor/glad/include"

include "Shake_Engine/vendor/GLFW"
include "Shake_Engine/vendor/glad"

project "Shake_Engine"
	location "Shake_Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "sepch.h"
	pchsource "Shake_Engine/src/sepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"SE_PLATFORM_WINDOWS",
			"SE_BUILD_DLL",
			"SE_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sable")
		}
		

	filter "configurations:Debug"
		defines "SE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "SE_RELEASE"
		optimize "On"
	filter "configurations:Shipping"
		defines "SE_SHIPPING"
		optimize "On"

project "Sable"
	location "Sable"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Shake_Engine/vendor/spdlog/include",
		"Shake_Engine/src"
	}

	links
	{
		"Shake_Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"SE_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "SE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "SE_RELEASE"
		optimize "On"
	filter "configurations:Shipping"
		defines "SE_SHIPPING"
		optimize "On"
		

