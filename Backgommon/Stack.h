#pragma once

#include "Sprite.h"
#include "Nut.h"

enum struct StackType {
	Wooden_Two,
	White_One
};

class CStack :public CSprite
{
public:
	std::vector<CNut * > nuts;
private:
	StackType type;
	int index;
	//CNut * removedNut;
	bool selected;
public:
	CStack();
	CStack(StackType type,int index);
	void SetSelected(bool selected);
	void AddNut(CNut * nut);
	//Returns removed nut from AddNut operation , if there was one
	CNut * PopNut();
	CNut * PeekNut();
	~CStack();
};

