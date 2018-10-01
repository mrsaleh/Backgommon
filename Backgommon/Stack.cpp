#include "Stack.h"



CStack::CStack()
{
}

CStack::CStack(StackType type)
{
	this->type = type;
	CTextureRegion region;
	region.x = 0;
	region.y = 0;
	region.width = 63;
	region.height = 308;
	switch (type) {
	case StackType::White_One:
		this->assetName = "white_stack";
		break;
	case StackType::Wooden_Two:
		this->assetName = "wooden_stack";
		break;
	}
	this->x = 0;
	this->y = 50;
	this->width = 63;
	this->height = 308;
	this->region = region;	
	this->pivotX = 0.5f;
	this->pivotY = 0.0f;
}


CStack::~CStack()
{
}
