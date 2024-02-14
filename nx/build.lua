project "nx_engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
		
	location("%{wks.location}/hello_world")
	
	targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
    objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/"
	
	links { "glfw" }
	includedirs { "../libraries/GLFW/include" }
	
	files 
	{
	-- header files
        "%{prj.location}/**.h", "%{prj.location}/**.hpp", "%{prj.location}/**.hh", "%{prj.location}/**.hxx",
	-- source files
        "%{prj.location}/**.c", "%{prj.location}/**.cpp", "%{prj.location}/**.cc", "%{prj.location}/**.cxx",
	-- text files
        "%{prj.location}/**.lua", "%{prj.location}/**.md",
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
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }
		
	