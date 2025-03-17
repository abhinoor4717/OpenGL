workspace "OpenGL"
    architecture "x64"
    startproject "GlApp"

    configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GlApp/vendor/GLFW/include"
IncludeDir["Glm"] = "GlApp/vendor/Glm/include"
IncludeDir["Glad"] = "GlApp/vendor/Glad/include"

include "GlApp/vendor/GLFW"
include "GlApp/vendor/Glad"

project "GlApp"
    location "GlApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

    includedirs {
        "%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.Glad}"
    }

    links {
        "GLFW",
        "Glad",
        "opengl32",
        "gdi32",
        "user32"
    }

    filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"