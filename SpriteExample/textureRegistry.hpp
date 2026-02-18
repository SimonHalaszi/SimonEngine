#ifndef TEXTURE_REGISTRY_HPP
#define TEXTURE_REGISTRY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <unordered_map>
#include <string>
#include <iostream>

// Using very epic and awesome design patterns to make Nesty proud
class TextureRegistry {
	public:

		static TextureRegistry& getInstance() {
			static TextureRegistry instance;
			return instance;
		}

		GLuint loadTexture(std::string filepath);
		void unloadTexture(std::string filepath);

		GLuint getTextureID(std::string filepath) const;

		TextureRegistry(const TextureRegistry&) = delete;
		TextureRegistry& operator=(const TextureRegistry&) = delete;
		TextureRegistry(const TextureRegistry&&) = delete;
		TextureRegistry& operator=(const TextureRegistry&&) = delete;

	private:
		TextureRegistry() {}

		~TextureRegistry() {
			for (auto& pair : textureMap_) {
				glDeleteTextures(1, &pair.second);
			}
		}

		// Registry
		static std::unordered_map<std::string, GLuint> textureMap_;
};

#endif
