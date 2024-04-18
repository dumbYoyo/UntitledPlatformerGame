workspace "PlatformerGameMaybe"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}}"

-- // --
project "PlatformerGameMaybe"
    location "PlatformerGameMaybe"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/libraries/glad/src/glad.c",
        "%{prj.name}/libraries/stb/stb/stb_image.cpp",
        "%{prj.name}/libraries/box2d/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/glad/include",
        "%{prj.name}/libraries/GLFW/include",
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/stb",
        "%{prj.name}/libraries/entt",
        "%{prj.name}/libraries/box2d/include",
    }

    libdirs
    {
        "%{prj.name}/libraries/GLFW/lib",
    }

    links
    {
        "glfw3",
        "opengl32",
    }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
    defines "CP_RELEASE"
    optimize "On"

-- // --
project "MapEditor"
    location "MapEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/libraries/glad/src/glad.c",
        "%{prj.name}/libraries/stb/stb/stb_image.cpp",
        "%{prj.name}/libraries/box2d/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/glad/include",
        "%{prj.name}/libraries/GLFW/include",
        "%{prj.name}/libraries/glm",
        "%{prj.name}/libraries/stb",
        "%{prj.name}/libraries/entt",
        "%{prj.name}/libraries/box2d/include",
        "%{prj.name}/src"
    }

    libdirs
    {
        "%{prj.name}/libraries/GLFW/lib",
    }

    links
    {
        "glfw3",
        "opengl32",
    }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
    defines "CP_RELEASE"
    optimize "On"