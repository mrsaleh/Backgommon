#include "Nut.h"
#include "tween.hpp"

#include <iostream>

CNut::CNut() :CNut(Player::One) {
	stackIndex = -1;
}

CNut::CNut(Player owner)
{
	stackIndex = -1;
	this->owner = owner;
	CTextureRegion region;
	region.x = 0;
	region.y = 0;
	region.width = 95;
	region.height = 95;
	switch (owner) {
	case Player::One:
		this->assetName = "white_nut";
		break;
	case Player::Two:
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

	CTweenManager::GoTo(
		this->x, this->y,
		targetX, TargetY,
		Easing::CubicInOut
	);
	passedTime = 0;
	nutStartX = this->x;
	nutStartY = this->y;
}

void CNut::SetSelected(bool isSelected) {
	selected = isSelected;
	
	if (selected){
		tintG = 255;
		tintR = 200;
		tintB = 150;
	}
	else
		tintR = tintG = tintB = 255;
}

CNut::~CNut()
{
}
