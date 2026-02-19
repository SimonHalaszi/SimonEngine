#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

// Simple helper structs

// Used for inputting color information in draw functions
struct ColorRGB {
	float red;
	float green;
	float blue;
};

// Used for inputting positions in draw functions
struct PositionXY {
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

#endif