project "nx_engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	toolset "msc"
		
	targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
    objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/"
	
	links 
	{ 
		"glfw", 
		"imgui",
		"glad",
		"opengl32.lib"
	}

	includedirs 
	{ 
		"../vendors/GLFW/include/",
		"../vendors/imgui/",
		"../vendors/glad/include/"		
	}
	
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
    }
	
	
	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		
	filter { "system:windows"}	
		runtime "Debug"
		symbols "on"
		-- sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }
		
	