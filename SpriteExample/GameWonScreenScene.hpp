#ifndef GAMEWON_SCREEN_SCENE_HPP
#define GAMEWON_SCREEN_SCENE_HPP

// Needed C++ Includes
#include <string>
#include <memory>

// Scene Interface
#include "Scene.hpp"

// Likely Needed SimonEngine Includes
#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "InputManager.hpp"
#include "SoundManager.hpp"

class GameWonScreenScene : public Scene {
public:
	GameWonScreenScene();

	~GameWonScreenScene();

	virtual void init() override final;

	virtual void draw() const override final;

	virtual void update() override final;

private:

	// Scene Specific Stuff Goes Here (Stuff not related to a GameObject)

	// File paths for audio
	std::string gameWonMusicFilePath_;
	std::string gameWonSoundFilePath_;

	// Keys for registries
	std::string backgroundSprite_;

	// File paths for loading textures
	std::string backgroundSpriteFilePath_;
};

#endif