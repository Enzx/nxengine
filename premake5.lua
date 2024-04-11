-- Main script for creating projects 

--include "premake_functions.lua"


	
-- Workspace setup

workspace "NxEngine"

	architecture "x86_64"
    location "./"

	configurations { "Debug", "Release" }
	
-- Define output directories
    targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
    objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}/"
	vendor_includedirs = {}

-- Projects

include "vendors/GLFW/build.lua"
include "vendors/imgui/build.lua"
include "vendors/glad/build.lua"
include "nx_engine/build.lua"
