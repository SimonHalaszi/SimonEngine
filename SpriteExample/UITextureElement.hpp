#ifndef UI_TEXTURE_ELEMENT_HPP
#define UI_TEXTURE_ELEMENT_HPP

#include <string>

#include "UIElement.hpp"

#include "DrawFunctions.hpp"
#include "Utilities.hpp"
#include "TextureRegistry.hpp"

// UI GameObjects will be drawn relative to camera space. So be smart when initializing their transform2D
class UITextureElement : public UIElement {
	public:
		UITextureElement(
			const Transform2D& transform2D,
			const std::string& tag,
			const std::string& name,
			const GLuint& texID
		);

		void onStart() override {}
		void draw() override final;
		void update() override {}
		void onDestruction() override {}
		void establishFields() override {}

		void toggleDrawing() { drawElement_ = !drawElement_; }

	protected:
		GLuint textureID_;
		bool drawElement_ = true;
};

#endif