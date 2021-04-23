workspace "animacao"
    architecture "x86_64"
    startproject "animacao-2d"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "libs/vendor/GLFW/include"
IncludeDir["Glad"] = "libs/vendor/Glad/include"
IncludeDir["glm"] = "libs/vendor/glm"
IncludeDir["stb_image"] = "libs/vendor/stb_image"

group "Dependencies"
    include "libs/vendor/GLFW"
    include "libs/vendor/Glad"
group ""

project "animacao-2d"
    location "animacao-2d"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",

        "libs/vendor/stb_image/**.h",
        "libs/vendor/stb_image/**.cpp",
        "libs/vendor/glm/glm/**.hpp",
        "libs/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}",
        "libs",

        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        
        -- taken from https://learnopengl.com/Getting-started/Creating-a-window
        "GL",
        "X11",
        "pthread",
        "Xrandr",
        "Xi",
        "dl"
    }

    filter "system:Unix"
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"