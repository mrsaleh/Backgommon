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

