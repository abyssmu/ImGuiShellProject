workspace "MyOpenGLProject"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MyOpenGLProject"
    location "MyOpenGLProject"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    files { 
        "%{prj.location}/src/**.h", 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/vendor/glfw/include/GLFW/glfw3.h",
        "%{prj.location}/vendor/glfw/include/GLFW/glfw3native.h",
        "%{prj.location}/vendor/glfw/src/glfw_config.h",
        "%{prj.location}/vendor/glfw/src/context.c",
        "%{prj.location}/vendor/glfw/src/init.c",
        "%{prj.location}/vendor/glfw/src/input.c",
        "%{prj.location}/vendor/glfw/src/monitor.c",
        "%{prj.location}/vendor/glfw/src/vulkan.c",
        "%{prj.location}/vendor/glfw/src/window.c",
        "%{prj.location}/vendor/glad/include/glad/glad.h",
        "%{prj.location}/vendor/glad/include/KHR/khrplatform.h",
        "%{prj.location}/vendor/glad/src/glad.c",
        "%{prj.location}/vendor/spdlog/include/spdlog/**.h",
        "%{prj.location}/vendor/glm/glm/**.hpp",
        "%{prj.location}/vendor/glm/glm/**.inl",
        "%{prj.location}/vendor/imgui/*.h",
        "%{prj.location}/vendor/imgui/*.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{prj.location}/vendor/glfw/include",
        "%{prj.location}/vendor/glad/include",
        "%{prj.location}/vendor/spdlog/include",
        "%{prj.location}/vendor/glm",
        "%{prj.location}/vendor/imgui"
    }

    links {
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines { 
            --"GLFW_INCLUDE_NONE",
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files {
            "%{prj.location}/vendor/glfw/src/win32_init.c",
            "%{prj.location}/vendor/glfw/src/win32_joystick.c",
            "%{prj.location}/vendor/glfw/src/win32_monitor.c",
            "%{prj.location}/vendor/glfw/src/win32_time.c",
            "%{prj.location}/vendor/glfw/src/win32_thread.c",
            "%{prj.location}/vendor/glfw/src/win32_window.c",
            "%{prj.location}/vendor/glfw/src/wgl_context.c",
            "%{prj.location}/vendor/glfw/src/egl_context.c",
            "%{prj.location}/vendor/glfw/src/osmesa_context.c"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"