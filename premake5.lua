workspace "Sable"
	architecture "x64"
	startproject "Sable"

	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Shake_Engine"
	location "Shake_Engine"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include;"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"SE_PLATFORM_WINDOWS",
			"SE_BUILD_DLL"		
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
		

