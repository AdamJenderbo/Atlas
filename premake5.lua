workspace "Atlas"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Atlas/vendor/GLFW/include"
    IncludeDir["Glad"] = "Atlas/vendor/Glad/include"
    IncludeDir["ImGui"] = "Atlas/vendor/imgui"
    IncludeDir["glm"] = "Atlas/vendor/glm"

    include "Atlas/vendor/GLFW"
    include "Atlas/vendor/Glad"
    include "Atlas/vendor/imgui"

project "Atlas"
    location "Atlas"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "atlaspch.h"
    pchsource "Atlas/src/atlaspch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}vendor/glm/glm/**.hpp",
        "%{prj.name}vendor/glm/glm/**.inl"

    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "Atlas/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

    defines
    {
        "ATLAS_PLATFORM_WINDOWS",
        "ATLAS_BUILD_DLL",
        "GLFW_INCLUDE_NONE"
    }

    --postbuildcommands
    --{
     --   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    --}

    filter "configurations:Debug"
        defines "ATLAS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ATLAS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ATLAS_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
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
        "Atlas/vendor/spdlog/include",
        "Atlas/src",
        "Atlas/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Atlas"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

    defines
    { 
        "ATLAS_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "ATLAS_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "ATLAS_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "ATLAS_DIST"
        optimize "on"