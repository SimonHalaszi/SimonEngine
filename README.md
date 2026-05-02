# SimonEngine

A lightweight 2D game engine and editor built with C++, OpenGL, freeglut, irrKlang, and freeImage.

## Features

- Game architecture
  - Handles scene and editor
  - Used for querying/modifying scene and editor
- Scene architecture
  - Initialization and Deintialization
  - Game object updates
  - Game object drawing
  - Update, drawing, and animation timers
  - And more utilities
- Runtime editor for constructring scenes
  - Save/Load
  - Help
  - Hierarchy
  - Inspector
  - Asset Panel
  - Scene Panel
  - Scene View
- Asset registries
  - Textures
  - Sprites
  - Sprite sheets
- Managers for input, and sound
  - Input support via OpenGL and freeglut
  - Audio support via irrKlang
- Complete game object hierarchy architecture similar to Unity
  - Sub hierarchies for AABB collision objects and UI objects
  - onStart, update, draw, onDestruction, and establishFields functionality
- Scalable editor factories for adding your assets and scenes into the editor for editing, and for calling in your game objects

## How Do I Make A Game?
 
- SimonEngine is also shipped with a fully complete mini-game called "Moneser"
  - "Moneser" and its associated GameObjects and Scenes are perfect examples for how to use SimonEngine! Give the source code a look.

## Used Technologies

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

