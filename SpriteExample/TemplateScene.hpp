#ifndef TEMPLATE_SCENE_HPP
#define TEMPLATE_SCENE_HPP

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

// Game Objects Used
#include "NonColliderSprite.hpp"
//

class TemplateScene : public Scene {
	public:
		TemplateScene();

		~TemplateScene();

		virtual void init() override final;

		virtual void draw() const override final;

		virtual void update() override final;
};

#endif