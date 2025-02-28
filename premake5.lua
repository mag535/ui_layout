BUILDS = "build" -- where all the workspaces and projects will generate
BINARIES = "bin" -- where all the executables will generate


workspace "UI Layout"
    configurations {
	    "Debug"
	}
	location "%{BUILDS}"
	platforms {
	    "win64",
	    "lin64"
	}
	
	filter "platforms:win64"
	    system "Windows"
	    architecture "x86_64"
	filter "platforms:lin64"
	    system "Linux"
	    architecture "x86_64"

        
project "uilayout"
	kind "WindowedApp"
	language "C++"
    cppdialect "C++20"
	buildoptions {
		"-Wall",
		"-Werror"
	}
	-- where the project file will be placed
	location "%{BUILDS}"
	-- where the compiled binary will be placed
	targetdir "%{BINARIES}/%{cfg.buildcfg}"

	files {
	    "src/src/*.cpp",
        "src/include/*.h"
	}

    libdirs "src/include/"

	links { -- link to external libraries
	    -- required for raylib
	    "raylib",
	    "GL",
	    "m",
	    "pthread",
	    "dl",
	    "rt",
	    "X11"
	}
