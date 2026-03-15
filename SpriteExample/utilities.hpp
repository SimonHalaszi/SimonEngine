#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <cmath>

// Simple helper structs and functions

// Used for inputting color information in draw functions
struct ColorRGB {
	float red;
	float green;
	float blue;
};

// Used for inputting positions in draw functions
struct Vector2D {
	float x;
	float y;
};

// Used for sprite creation (Could just use PositionXY but I think this is more clear)
struct TileIndex {
	int x;
	int y;
};

// Used for partitioning a texture for sprites (SHould probably have a better name but whatever)
struct SubTexture {
	float u0;
	float u1;
	float v0;
	float v1;
};

struct Transform2D {
	Vector2D position = { 0.0f, 0.0f };
	Vector2D scale = { 0.0f, 0.0f };
	float rotation = 0.0f;
	bool mirror = false;
	bool flip = false;
};

struct AABB {
	Vector2D min = { 0.0f, 0.0f };
	Vector2D max = { 0.0f, 0.0f };
};

constexpr float PI = 3.14159265358979323846f;

float degreesToRadians(float degrees);

Transform2D composeTransforms(const Transform2D& left, const Transform2D& right);

bool checkAABBCollision(const AABB& a, const AABB& b);

#endif