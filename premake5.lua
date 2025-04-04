dependencies = {
	basePath = "./deps"
}

function dependencies.load()
	dir = path.join(dependencies.basePath, "premake/*.lua")
	deps = os.matchfiles(dir)

	for i, dep in pairs(deps) do
		dep = dep:gsub(".lua", "")
		require(dep)
	end
end

function dependencies.imports()
	for i, proj in pairs(dependencies) do
		if type(i) == 'number' then
			proj.import()
		end
	end
end

function dependencies.projects()
	for i, proj in pairs(dependencies) do
		if type(i) == 'number' then
			proj.project()
		end
	end
end

dependencies.load()

workspace "mw3-server-freezer"
startproject "client"
location "./build"
objdir "%{wks.location}/obj"
targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

configurations {"debug", "release"}

language "C++"
cppdialect "C++20"

architecture "x86"
platforms "Win32"

systemversion "latest"
symbols "On"
staticruntime "On"
editandcontinue "Off"
warnings "Extra"
characterset "ASCII"

flags {"NoIncrementalLink", "NoMinimalRebuild", "MultiProcessorCompile", "No64BitChecks"}

filter "platforms:Win*"
	defines {"_WINDOWS", "WIN32"}
filter {}

filter "configurations:release"
	optimize "Size"
	defines {"NDEBUG"}
	fatalwarnings {"All"}

	filter "toolset:msc*"
		buildoptions "/GL"
		linkoptions {"/IGNORE:4702", "/LTCG"}
	filter {}

	filter "toolset:not msc*"
		buildoptions "-Wno-unused-parameter"
	filter {}
filter {}

filter "configurations:debug"
	optimize "Debug"
	defines {"DEBUG", "_DEBUG"}
filter {}

project "common"
kind "StaticLib"
language "C++"

files {"./src/common/**.hpp", "./src/common/**.cpp"}

includedirs {"./src/common", "%{prj.location}/src"}

resincludedirs {"$(ProjectDir)src"}

dependencies.imports()

project "client"
kind "SharedLib"
language "C++"

targetname "mw3-server-freezer"

pchheader "std_include.hpp"
pchsource "src/client/std_include.cpp"

files {"./src/client/**.hpp", "./src/client/**.cpp"}

includedirs {"./src/client", "./src/common", "%{prj.location}/src"}

resincludedirs {"$(ProjectDir)src"}

links {"common"}

dependencies.imports()

group "Dependencies"
dependencies.projects()

rule "ProtobufCompiler"
display "Protobuf compiler"
location "./build"
fileExtension ".proto"
buildmessage "Compiling %(Identity) with protoc..."
buildcommands {'@echo off', 'path "$(SolutionDir)\\..\\tools"',
			   'if not exist "$(ProjectDir)\\src\\proto" mkdir "$(ProjectDir)\\src\\proto"',
			   'protoc --error_format=msvs -I=%(RelativeDir) --cpp_out=src\\proto %(Identity)'}
buildoutputs {'$(ProjectDir)\\src\\proto\\%(Filename).pb.cc', '$(ProjectDir)\\src\\proto\\%(Filename).pb.h'}
