#pragma once

#include <string>
#include "TextureRegion.h"

class CSprite
{
private:
	static long instanceId;
public:

	CSprite();
	
	~CSprite();

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
};


