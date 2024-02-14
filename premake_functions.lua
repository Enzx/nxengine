function create_project(name, root)
	print("Generating " .. name .. " project")
	root_directory = name
	if root ~= nil then
		root_directory = root 
	end
	
	project(name)
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		
		location("%{wks.location}/" .. root_directory)
		files 
		{
		-- header files
            "%{prj.location}/**.h", "%{prj.location}/**.hpp", "%{prj.location}/**.hh", "%{prj.location}/**.hxx",
		-- source files
            "%{prj.location}/**.c", "%{prj.location}/**.cpp", "%{prj.location}/**.cc", "%{prj.location}/**.cxx",
		-- text files
            "%{prj.location}/**.lua", "%{prj.location}/**.md",
        }
		
		
		targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
        objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}/"
		
		filter { "platforms:Win64" }
			system "Windows"
			architecture "x86_64"
		
		filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		
		filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
end