#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

// Used for inputting color information in draw functions
struct ColorRGB {
	float red;
	float green;
	float blue;
};

// Used for inputting textures positions in draw functions
struct PositionXY {
	float x;
	float y;
};

// Used for inputting TileIndex info (Could use PositionXY but I think its cleaner to do this)
struct TileIndex {
	int x;
	int y;
};

// Used for tile textures
struct SubTexture {
	float u0;
	float u1;
	float v0;
	float v1;
};

#endif