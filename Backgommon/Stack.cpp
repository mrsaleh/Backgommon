#include "Stack.h"



CStack::CStack()
{
}

CStack::CStack(StackType type, int index)
{
	this->removedNut = nullptr;
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

bool CStack::CanAdd(CNut * nut) {
	if (this->nuts.size() > 1 && nut->owner != this->nuts.back()->owner)
		return false;
	return true;
}

void CStack::AddNut(CNut * nut) {
	this->removedNut = nullptr;
	if (this->nuts.size() > 1 && nut->owner != this->nuts.back()->owner)
		return;

	if (this->nuts.empty()) {
		this->nuts.push_back(nut);
	}
	else {
		if (this->nuts.back()->owner != nut->owner) {
			if (this->nuts.size() == 1) {
				this->removedNut = this->nuts.back();
				this->nuts.clear();
				this->nuts.push_back(nut);
			}
		}
		else if (this->nuts.back()->owner == nut->owner) {
			this->nuts.push_back(nut);
		}
	}

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

CNut * CStack::Select(int x, int y, Player owner) {
	if (!this->nuts.empty()) {
		if (this->nuts.back()->owner == owner) {
			if (this->nuts.back()->Contains(x, y)) {
				return this->nuts.back();
			}
		}
	}
	return nullptr;
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


CNut * CStack::PickRemovedNut() {
	CNut * result = this->removedNut;
	this->removedNut = nullptr;
	return result;
}

CStack::~CStack()
{
}
