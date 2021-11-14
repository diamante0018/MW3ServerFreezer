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
    location "./build"
    objdir "%{wks.location}/obj"
    targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"

    language "C++"

    architecture "x86"
    platforms "x86"

    buildoptions "/std:c++latest"
    systemversion "latest"

    flags { "NoIncrementalLink", "NoMinimalRebuild", "MultiProcessorCompile", "No64BitChecks" }

    configurations {"Debug", "Release"}

    symbols "On"
    staticruntime "On"
    editandcontinue "Off"
    warnings "Extra"
    characterset "ASCII"

    configuration "Release"
        optimize "Size"
        defines {"NDEBUG"}
        flags {"FatalCompileWarnings"}
        buildoptions {"/GL"}
        linkoptions { "/IGNORE:4702", "/LTCG" }
    configuration {}

    configuration "Debug"
        optimize "Debug"
        defines {"DEBUG", "_DEBUG"}
    configuration {}

project "mw3-server-freezer"
    kind "SharedLib"
    language "C++"

    pchheader "stdinc.hpp"
    pchsource "src/stdinc.cpp"

    files { "/src/**.hpp", "/src/**.cpp" }

    includedirs { "src" }

dependencies.imports()

group "Dependencies"
dependencies.projects()
