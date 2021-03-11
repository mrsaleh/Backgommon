#pragma once

#include <string>
#include <vector>
#include "TextureRegion.h"
#include <SDL.h>

class CSprite
{
private:
	static long instanceId;
public:

	CSprite();

	~CSprite();

	bool Contains(int x, int y);
public:
	std::string assetName;
	float x;
	float y;
	float width;
	float height;
	float pivotX;
	float pivotY;
	float ratation;
	CTextureRegion region;
	bool flipX;
	bool flipY;
	Uint8 tintR, tintG, tintB;
	Uint8 alpha;
};


