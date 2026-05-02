# SimonEngine

A lightweight 2D game engine and editor built with C++, OpenGL, freeglut, irrKlang, and freeImage.

## Features

- Scene architecture
- Runtime editor for constructring scenes
- Asset registries
- Managers for input, collision, and sound
  - Audio support via irrKlang
- Complete game object hierarchy architecture similar to Unity
  - Sub hierarchies for AABB collision objects and UI objects
- Scalable editor factories for adding your assets and scenes into the editor for editing
 
- The engine is also shipped with a fully complete game "Moneser"
  - "Moneser" and its associated GameObjects and Scenes are perfect examples for how to use SimonEngine! Give the source code a look.

## Used Technology

- C++
- OpenGL + freeglut
- FreeImage
- irrKlang
- Visual Studio solution/project files included

## Build (Visual Studio)

1. Open `SimonEngine.sln`
2. Select `x64` platform
3. Build `Debug` or `Release`
4. Run the `SimonEngine` startup project

## For Help

- See the editors built in help tab!

## Project Layout

- `source/`: engine and gameplay source files
- `source/image/`: image assets
- `source/audio/`: audio assets
- `source/editorSaves/`: editor save data
- `source/include/`, `source/lib/`: local third-party headers/libs

