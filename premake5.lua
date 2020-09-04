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
IncludeDir["ImGui"] = "Shake_Engine/vendor/imgui"
IncludeDir["GLM"] = "Shake_Engine/vendor/glm"
IncludeDir["stb_image"] = "Shake_Engine/vendor/stb_image"
IncludeDir["entt"] = "Shake_Engine/vendor/entt/include"

group "Dependencies"
	include "Shake_Engine/vendor/GLFW"
	include "Shake_Engine/vendor/glad"
	include "Shake_Engine/vendor/imgui"
group ""

project "Shake_Engine"
	location "Shake_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "sepch.h"
	pchsource "Shake_Engine/src/sepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/imgui/examples/imgui_impl_glfw.h",
		"%{prj.name}/vendor/imgui/examples/imgui_impl_glfw.cpp",
		"%{prj.name}/vendor/imgui/examples/imgui_impl_opengl3.h",
		"%{prj.name}/vendor/imgui/examples/imgui_impl_opengl3.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}
	
	defines
	{
		"SE_ENABLE_ASSERTS",
		"SE_PLATFORM_WINDOWS",
		"SE_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "10.0.18362.0"

		defines
		{
		}
		

	filter "configurations:Debug"
		defines "SE_DEBUG"
		symbols "on"
	filter "configurations:Release"
		defines "SE_RELEASE"
		optimize "on"
	filter "configurations:Shipping"
		defines "SE_SHIPPING"
		optimize "on"

project "Sable"
	location "Sable"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Shake_Engine/src",
		"Shake_Engine/vendor",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Shake_Engine"
	}

	filter "system:windows"
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
		
project "Shake-Editor"
	location "Shake-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Shake_Engine/src",
		"Shake_Engine/vendor",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Shake_Engine"
	}

	filter "system:windows"
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
		
