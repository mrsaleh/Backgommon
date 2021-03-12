#include "Stack.h"



CStack::CStack()
{
	selected = false;
}

CStack::CStack(StackType type, int index)
{
	selected = false;
	//this->removedNut = nullptr;
	this->index = index;
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

void CStack::SetSelected(bool selected) {
	this->selected = selected;
	
	if (selected) {
		tintG = 255;
		tintR = 200;
		tintB = 150;
	}
	else
		tintR = tintG = tintB = 255;
}


void CStack::AddNut(CNut * nut) {
	
	this->nuts.push_back(nut);
	nut->stackIndex = index;	

	//Position nut
	float margin = 28;
	float nutRealHeight = nut->height - margin;
	if (index < 12) {
		nut->Move(this->x, this->y - nut->height / 2 + margin / 2 - (nuts.size() - 1) * nutRealHeight);
	}
	else {
		nut->Move(this->x, this->y + nut->height / 2 - margin / 2 + (nuts.size() - 1) * nutRealHeight);
	}
}

CNut * CStack::PopNut() {
	if (!this->nuts.empty()) {
		CNut * result = this->nuts.back();
		this->nuts.erase(this->nuts.end() - 1);
		return result;
	}
	return nullptr;
}

CNut * CStack::PeekNut() {
	if (!this->nuts.empty())
		return this->nuts.back();
	return nullptr;
}


CStack::~CStack()
{
}
