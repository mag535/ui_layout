# README


This is a UI Layout Library made using C++ and Raylib.


## Features

- Text Label
    - customize the label by adding a border, border color, background
      color, text color, text size, padding, and border width.
- Text Input
    - Same as  Text Label.
    - Accepts ASCII text.
    - Option for numbers only (only allows for integers).
- Interactibility
    - hovering.
    - visible indicator that an interactive element is active, inactive, or
      disabled.
- Toggle Button
    - Same as Text Label.
    - it's exactly what it sounds like.


## Planned Features

- [ ] Buttons
    - [ ] Click
    - [x] Toggle
- [ ] Slider
- [x] Text Input
    - [x] All visible ASCII
    - [x] numbers only
- [x] Text Label
- [ ] Images
- [ ] Containers
    - [ ] horizontal
    - [ ] vertical


## How to Build

Tools Needed:
- CMake 3.15 or newer
- Raylib 5.0 or newer
- A C++ compiler that supports C++20 and C99


### Linux

Raylib (static library version) needs to either be installed or copied into the
`include/` directory.

After that's done, run these commands:
```sh
cd PROJECT_DIR
./build.sh [GENERATOR] [ARCHITECTURE]
```

The GENERATOR and ARCHITECTURE parameters are optional. They'll default to
cmake's default. However, if you specify ARCHITECTURE, you need to use "" as
the value for GENERATOR.
Example: `./build.sh "" ARM64`


### Windows

Raylib (static library version) needs to be copied into `include/` directory.
You can download the precompiled static library directly from Raylib's release
page on GitHub or compile it yourself following Raylib's wiki.

After that's done, double-click `build.bat`.


### MacOS

WIP


## How to Use

The executables are placed in `./bin/` on Linux and `.\bin\Debug\` on Windows.

You can also load the generated project / solution into its respective
application (eg. open UILayout.sln in Visual Studio).
