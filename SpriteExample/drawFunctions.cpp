#include "DrawFunctions.hpp"

// Functions for drawing shapes, sprites, images, etc

// Drawing a square
void drawSquare(PositionXY pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3, ColorRGB c4) {
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

// Drawing a triangle
void drawTriangle(PositionXY pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3) {
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
void drawImage(PositionXY pos, float size, float angle, bool mirror, bool flip, GLuint textureID) {
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
	glVertex3f(-size, -size, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, -size, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-size, size, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Drawing a sprite
void drawSprite(PositionXY pos, float size, float angle, bool mirror, bool flip, Sprite sprite) {
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
	glVertex3f(-size, -size, 0.0f);
	glTexCoord2f(spriteUV.u1, spriteUV.v0);
	glVertex3f(size, -size, 0.0f);
	glTexCoord2f(spriteUV.u1, spriteUV.v1);
	glVertex3f(size, size, 0.0f);
	glTexCoord2f(spriteUV.u0, spriteUV.v1);
	glVertex3f(-size, size, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Drawing a line
void drawLine(PositionXY pos1, PositionXY pos2, ColorRGB c1, ColorRGB c2) {
	glBegin(GL_LINES);              // Start drawing a line
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(pos1.x, pos1.y, 0.0f); // Start

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(pos2.x, pos2.y, 0.0f); // End
	glEnd();                        // End drawing
}

// Drawing an axis
void drawAxis(PositionXY pos1, PositionXY pos2, ColorRGB c1, ColorRGB c2, char axis) {
	if (axis == 'x') {
		drawLine(
			pos1, pos2, 
			c1, c2
		);
		drawTriangle(
			pos2, 
			0.015f, 270.0f, 
			false, false, 
			c2, c2, c2
		);
	}
	else if (axis == 'y') {
		drawLine(
			pos1, pos2, 
			c1, c2
		);
		drawTriangle(
			pos2, 
			0.015f, 0.0f, 
			false, false, 
			c2, c2, c2
		);
	}
	else if (axis == 'z') {
		std::cout << "bruh this is 2D" << std::endl;
	}
	else {
		return;
	}
}