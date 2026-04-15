#include "DrawFunctions.hpp"

// Functions for drawing shapes, sprites, images, etc

// Drawing a square
void drawSquare(
	const Vector2D& pos,
	const float& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& c1,
	const ColorRGB& c2,
	const ColorRGB& c3,
	const ColorRGB& c4
) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glBegin(GL_QUADS);
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(-size, -size, 0.0f);

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(size, -size, 0.0f);

	glColor3f(c3.red, c3.green, c3.blue);
	glVertex3f(size, size, 0.0f);

	glColor3f(c4.red, c4.green, c4.blue);
	glVertex3f(-size, size, 0.0f);
	glEnd();

	glPopMatrix();
}

// Drawing a rectangle
void drawRectangle(
	const Vector2D& pos,
	const Vector2D& scale,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& c1,
	const ColorRGB& c2,
	const ColorRGB& c3,
	const ColorRGB& c4
) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glBegin(GL_QUADS);
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(-scale.x, -scale.y, 0.0f);

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(scale.x, -scale.y, 0.0f);

	glColor3f(c3.red, c3.green, c3.blue);
	glVertex3f(scale.x, scale.y, 0.0f);

	glColor3f(c4.red, c4.green, c4.blue);
	glVertex3f(-scale.x, scale.y, 0.0f);
	glEnd();

	glPopMatrix();
}

// Drawing a triangle
void drawTriangle(
	const Vector2D& pos,
	const float& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& c1,
	const ColorRGB& c2,
	const ColorRGB& c3
) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glBegin(GL_TRIANGLES);              

	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(-size, -size, 0.0f); 

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(size, -size, 0.0f); 

	glColor3f(c3.red, c3.green, c3.blue);
	glVertex3f(0.0f, size, 0.0f); 

	glEnd();                        

	glPopMatrix();
}

// Drawing an image
void drawImage(
	const Vector2D& pos,
	const Vector2D& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const GLuint& textureID
) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size.x, -size.y, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size.x, -size.y, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size.x, size.y, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-size.x, size.y, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Drawing a sprite
void drawSprite(
	const Vector2D& pos,
	const Vector2D& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const Sprite& sprite
) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, sprite.getTextureID());

	SubTexture spriteUV = sprite.getUV();

	glBegin(GL_POLYGON);
	glTexCoord2f(spriteUV.u0, spriteUV.v0);
	glVertex3f(-size.x, -size.y, 0.0f);
	glTexCoord2f(spriteUV.u1, spriteUV.v0);
	glVertex3f(size.x, -size.y, 0.0f);
	glTexCoord2f(spriteUV.u1, spriteUV.v1);
	glVertex3f(size.x, size.y, 0.0f);
	glTexCoord2f(spriteUV.u0, spriteUV.v1);
	glVertex3f(-size.x, size.y, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Drawing a line
void drawLine(
	const Vector2D& pos1,
	const Vector2D& pos2,
	const ColorRGB& c1,
	const ColorRGB& c2
) {
	glBegin(GL_LINES);
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(pos1.x, pos1.y, 0.0f);

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(pos2.x, pos2.y, 0.0f);
	glEnd();
}

// Function to draw text
void drawText(
	const Vector2D& pos,
	const std::string& text,
	const float& lineSpace,
	const ColorRGB& color
) {

	glColor3f(color.red, color.green, color.blue);
	glRasterPos3f(pos.x, pos.y, 0.0f);

	float tempPosY = pos.y;

	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i] == '\n') {
			tempPosY -= lineSpace;
			glRasterPos3f(pos.x, tempPosY, 0.0f);
		}
		else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
			/*
			These are all the font options you have:
			GLUT_BITMAP_8_BY_13
			GLUT_BITMAP_9_BY_15
			GLUT_BITMAP_TIMES_ROMAN_10
			GLUT_BITMAP_TIMES_ROMAN_24
			GLUT_BITMAP_HELVETICA_10
			GLUT_BITMAP_HELVETICA_12
			GLUT_BITMAP_HELVETICA_18
			*/
		}
	}
}

void drawTextCentered(
	const Vector2D& pos,
	const std::string& text,
	const float& lineSpace,
	const ColorRGB& color
) {
	glColor3f(color.red, color.green, color.blue);

	void* font = GLUT_BITMAP_HELVETICA_18;

	int textWidth = 0;
	for (char c : text) {
		if (c != '\n') {
			textWidth += glutBitmapWidth(font, c);
		}
	}

	int textHeight = 18;

	float startX = pos.x - textWidth / 2.0f;
	float startY = pos.y - textHeight / 2.0f;

	glRasterPos2f(startX, startY);

	float x = startX;
	float y = startY;
	for (char c : text) {
		if (c == '\n') {
			y -= lineSpace;
			x = startX;
			glRasterPos2f(x, y);
		}
		else {
			glutBitmapCharacter(font, c);
			x += glutBitmapWidth(font, c);
		}
	}
}