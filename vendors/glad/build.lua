project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
    objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/"

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
		
	}
	
	includedirs {"include/"}


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
