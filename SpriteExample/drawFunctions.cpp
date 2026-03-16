#include "DrawFunctions.hpp"

// Functions for drawing shapes, sprites, images, etc

// Drawing a square
void drawSquare(Vector2D pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3, ColorRGB c4) {
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
void drawRectangle(Vector2D pos, Vector2D scale, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3, ColorRGB c4) {
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
void drawTriangle(Vector2D pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3) {
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
void drawImage(Vector2D pos, Vector2D size, float angle, bool mirror, bool flip, GLuint textureID) {
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
void drawSprite(Vector2D pos, Vector2D size, float angle, bool mirror, bool flip, Sprite sprite) {
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
void drawLine(Vector2D pos1, Vector2D pos2, ColorRGB c1, ColorRGB c2) {
	glBegin(GL_LINES);              // Start drawing a line
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(pos1.x, pos1.y, 0.0f); // Start

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(pos2.x, pos2.y, 0.0f); // End
	glEnd();                        // End drawing
}

// Function to draw text
void drawText(Vector2D pos, std::string text, float lineSpace, ColorRGB color) {

	glColor3f(color.red, color.green, color.blue);
	glRasterPos3f(pos.x, pos.y, 0.0f);

	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i] == '\n') {
			pos.y -= lineSpace; //line spacing
			glRasterPos3f(pos.x, pos.y, 0.0f);
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