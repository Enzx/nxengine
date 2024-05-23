project "nx_engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	toolset "msc"
		
	targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
    objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/"
	

	links 
	{ 
		"opengl32.lib",
		"glfw", 
		"imgui",
		"imgui_backends",
		"glad",
		"assimp",
	}

	includedirs 
	{ 
		"../vendors/GLFW/include/",
		"../vendors/imgui/",
		"../vendors/glad/include/",
		"../vendors/assimp/include/",
		"../vendors/include/",
		"../nx_engine/",
		
	}
	
	-- defines { "ASSIMP_STATIC" }
	
	files 
	{
	-- header files
        "%{wks.location}/nx_engine/**.h", 
		"%{wks.location}/nx_engine/**.hpp", 
		"%{wks.location}/nx_engine/**.hh", 
		"%{wks.location}/nx_engine/**.hxx",
	-- source files
        "%{wks.location}/nx_engine/**.c", 
		"%{wks.location}/nx_engine/**.cpp", 
		"%{wks.location}/nx_engine/**.cc", 
		"%{wks.location}/nx_engine/**.cxx",
	-- text files
        "%{wks.location}/nx_engine/**.lua", 
		"%{wks.location}/nx_engine/**.md",
	-- assets
		"%{wks.location}/assets/**.**",
    }
	
	
	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "_ITERATOR_DEBUG_LEVEL=2", "DEBUG" }
		buildoptions { "/MDd" }
		
	filter { "system:windows"}	
		runtime "Debug"
		symbols "on"
		-- sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }
		

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"
		-- linkoptions {"/NODEFAULTLIB:MSVCRT"}
		defines { "_ITERATOR_DEBUG_LEVEL=0", "NDEBUG" }
		buildoptions { "/MD" } 
		
	