#include "Sprite.h"

CSprite::CSprite()
{
	this->ratation = 0;
	this->flipX = this->flipY = false;
	this->pivotX = this->pivotY = 0.5f;
}

CSprite::~CSprite()
{
}

bool CSprite::Contains(int x, int y) {
	float minX = this->x - this->pivotX * this->width;
	float maxX = minX + this->width;
	float minY = this->y - this->pivotY  * this->height;
	float maxY = minY + this->height;

	if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
		return true;
	}
	return false;
}



