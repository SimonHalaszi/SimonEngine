#ifndef PLATFORMER_SCENE_HPP
#define PLATFORMER_SCENE_HPP

// Needed Other Includes
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <IrrKlang/irrKlang.h>

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

class PlatformerScene : public Scene {
	public:
		PlatformerScene();

		~PlatformerScene();

		virtual void init() override final;

		virtual void draw() const override final;

		virtual void update() override final;

	private:

		// Scene Specific Stuff Goes Here (Stuff not related to a GameObject)

		// File paths for audio
		std::string backgroundMusicFilePath_;

		// Keys for registries
		std::string playerSpriteSheet_;
		std::string turfSprite_;
		std::string concreteSprite_;
		std::string skyboxSprite_;
		std::string coinSprite_;
		std::string goalSprite_;

		// File paths for loading textures
		std::string playerSpriteSheetFilePath_;
		std::string turfTextureFilePath_;
		std::string concreteTextureFilePath_;
		std::string skyboxTextureFilepath_;
		std::string coinTextureFilepath_;
		std::string goalTextureFilepath_;
};

#endif