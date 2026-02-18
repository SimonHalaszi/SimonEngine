#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <vector>
#include <iostream>
#include <string>

#include "utilities.hpp"
#include "drawFunctions.hpp"
#include "textureRegistry.hpp"

class Game {
	public:
		Game() {
			textures = &TextureRegistry::getInstance();
			SoundEngine = irrklang::createIrrKlangDevice();
		}

		void init();
		void draw();
		void update();
		void timer();

		void procSpecialKeys(int key, int x, int y);
		void procSpecialKeysUp(int key, int x, int y);
		void procKeys(unsigned char key, int x, int y);
		void procMouse(int button, int state, int x, int y);

	private:
		void updateCamera();
		void setupInputs();

		TextureRegistry* textures;
		irrklang::ISoundEngine* SoundEngine;


};

#endif // !GAME_HPP
