#include "Nut.h"
#include "tween.hpp"

CNut::CNut() :CNut(NutType::White_One) {

}

CNut::CNut(NutType type)
{
	this->type = type;
	CTextureRegion region;
	region.x = 0;
	region.y = 0;
	region.width = 95;
	region.height = 95;
	switch (type) {
	case NutType::White_One:
		this->assetName = "white_nut";
		break;
	case NutType::Wooden_Two:
		this->assetName = "wooden_nut";
		break;
	}
	this->width = this->height = 95;
	this->x = 100;
	this->y = 50;
	this->width = 95;
	this->height = 95;
	this->region = region;

	this->targetX = this->x;
	this->targetY = this->y;
	this->nutStartX = this->x;
	this->nutStartY = this->y;
}


void CNut::Tick(float deltaTime) {
	passedTime += deltaTime;
	if (passedTime <= 1.0f) {
		this->x = nutStartX + tween::cubicinout(passedTime) * (targetX - nutStartX);
		this->y = nutStartY + tween::cubicinout(passedTime) * (targetY - nutStartY);
	}
}

void CNut::Move(int targetX, int targetY) {
	this->targetX = targetX;
	this->targetY = targetY;
	passedTime = 0;
	nutStartX = this->x;
	nutStartY = this->y;
}

CNut::~CNut()
{
}
