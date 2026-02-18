#include "DrawFunctions.hpp"

// Function for drawing squares given a PositionXY, a size (float), and 4 ColorRGB for the vertices
void drawSquare(PositionXY pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3, ColorRGB c4) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis	

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glBegin(GL_QUADS);              // Start drawing a quad
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(-size, -size, 0.0f); // Bottom-left

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(size, -size, 0.0f); // Bottom-right

	glColor3f(c3.red, c3.green, c3.blue);
	glVertex3f(size, size, 0.0f); // Top-right

	glColor3f(c4.red, c4.green, c4.blue);
	glVertex3f(-size, size, 0.0f); // Top-left
	glEnd();                        // End drawing

	glPopMatrix();
}

// Function for drawing triangles given a PositionXY, a size (float), and 3 ColorRGB for the vertices
void drawTriangle(PositionXY pos, float size, float angle, bool mirror, bool flip, ColorRGB c1, ColorRGB c2, ColorRGB c3) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glBegin(GL_TRIANGLES);              // Start drawing a triangle

	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(-size, -size, 0.0f); // Bottom-left

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(size, -size, 0.0f); // Bottom-right

	glColor3f(c3.red, c3.green, c3.blue);
	glVertex3f(0.0f, size, 0.0f); // Top

	glEnd();                        // End drawing

	glPopMatrix();
}

// Function for drawing a sprite given a PositionXY, a size (float), and a GLuint TextureID, and an optional SubTexture for tiling
void drawImage(PositionXY pos, float size, float angle, bool mirror, bool flip, GLuint textureID) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glEnable(GL_TEXTURE_2D); // Enable texturing

	glBindTexture(GL_TEXTURE_2D, textureID); // Which texture

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size, -size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, -size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-size, size, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D); // Turn texturing off

	glPopMatrix();
}

// Function for drawing a sprite given a PositionXY, a size (float), and a GLuint TextureID, and an optional SubTexture for tiling
void drawSprite(PositionXY pos, float size, float angle, bool mirror, bool flip, Sprite sprite) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	if (flip) {
		glScalef(1.0f, -1.0f, 1.0f);
	}

	glEnable(GL_TEXTURE_2D); // Enable texturing

	glBindTexture(GL_TEXTURE_2D, sprite.getTextureID()); // Which texture

	glBegin(GL_POLYGON);
	glTexCoord2f(sprite.getUV().u0, sprite.getUV().v0);
	glVertex3f(-size, -size, 0);
	glTexCoord2f(sprite.getUV().u1, sprite.getUV().v0);
	glVertex3f(size, -size, 0);
	glTexCoord2f(sprite.getUV().u1, sprite.getUV().v1);
	glVertex3f(size, size, 0);
	glTexCoord2f(sprite.getUV().u0, sprite.getUV().v1);
	glVertex3f(-size, size, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D); // Turn texturing off

	glPopMatrix();
}

void drawLine(PositionXY pos1, PositionXY pos2, ColorRGB c1, ColorRGB c2) {
	glBegin(GL_LINES);              // Start drawing a line
	glColor3f(c1.red, c1.green, c1.blue);
	glVertex3f(pos1.x, pos1.y, 0.0f); // Start

	glColor3f(c2.red, c2.green, c2.blue);
	glVertex3f(pos2.x, pos2.y, 0.0f); // End
	glEnd();                        // End drawing
}

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