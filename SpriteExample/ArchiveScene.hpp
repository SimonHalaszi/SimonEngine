#ifndef ARCHIVE_SCENE_HPP
#define ARCHIVE_SCENE_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <IrrKlang/irrKlang.h>

#include <string>
#include <algorithm>
#include <memory>

#include "Scene.hpp"
 
#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "TextureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"
#include "InputManager.hpp"

// Game Objects Used
#include "ArchivePlayer.hpp"
#include "RotatingColorChangingSquare.hpp"
#include "RotatingColorChangingTriangle.hpp"
#include "StaticSprite.hpp"
#include "AnimatedSprite.hpp"
#include "Axis.hpp"

class ArchiveScene : public Scene {
	public:
		ArchiveScene();

		~ArchiveScene();

		virtual void init() override final;

		virtual void draw() const override final;
		 
		virtual void update() override final;

	private:
		
		// Scene Specific Functions
		void updateCamera();

		// Scene Audio Tracks
		int currentAudioTrack_ = 0;
		const std::vector<std::string> audioTracks_;

		// Toggles
		bool musicOn_ = true;

		// Camera Settings
		float zoomFactor_ = 1.0f;
		float camX_ = 0.0f, camY_ = 0.0f, speed_ = 1.0f;

		// Keys for registries
		std::string billsRunningSheetName_;
		std::string brownsRunningSheetName_;
		std::string billsSpriteName_;
		std::string brownsSpriteName_;

		// File Paths
		const std::string runningTilesBrownsFilepath_;
		const std::string runningTilesBillsFilepath_;
};

#endif