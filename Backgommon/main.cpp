#include "Engine.h"
#include "Nut.h"
#include "Stack.h"
#include "tween.hpp"
#include <iostream>
#include <stdlib.h>

enum struct Player {
	One,
	Two
};

class Game : public CMouseInputListener {
private:
	Player currentPlayer;
	std::vector<CNut *> playerOneRemovedNuts;
	std::vector<CNut *> playerTwoRemovedNuts;
	std::vector<std::vector<CNut*>> stacksNuts;
	std::vector<CStack *> stacks;
public:
	Game() {

		//Creates the stacks
		for (int i = 11; i >= 0; i--) {
			CStack * newStack;
			if (i % 2 == 0)
				newStack = new CStack(StackType::Wooden_Two);
			else
				newStack = new CStack(StackType::White_One);
			newStack->x += i* newStack->width + newStack->width / 2;
			newStack->pivotY = 1.0f;
			newStack->y = 720;
			stacks.push_back(newStack);
		}

		for (int i = 0; i < 12; i++) {
			CStack * newStack;
			if (i % 2 == 1)
				newStack = new CStack(StackType::Wooden_Two);
			else
				newStack = new CStack(StackType::White_One);
			newStack->x += i* newStack->width + newStack->width / 2;
			newStack->ratation = 180.0f;
			newStack->y = 0;
			stacks.push_back(newStack);
		}
		//Initializing nuts stack
		for (int i = 0; i < 24; i++) {
			stacksNuts.push_back(std::vector<CNut*>());
		}
		//Creates playerOne Nuts
		//Two at 0 stack
		for (int i = 0; i < 2; i++) {
			CNut * newNut = new CNut(NutType::White_One);
			stacksNuts[0].push_back(newNut);
			MoveNutToStack(newNut, 0, i);
		}
		//Five at 11 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(NutType::White_One);
			stacksNuts[11].push_back(newNut);
			MoveNutToStack(newNut, 11, i);
		}

		//Three at 16 stack
		for (int i = 0; i < 3; i++) {
			CNut * newNut = new CNut(NutType::White_One);
			stacksNuts[16].push_back(newNut);
			MoveNutToStack(newNut, 16, i);
		}

		//Five at 18 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(NutType::White_One);
			stacksNuts[18].push_back(newNut);
			MoveNutToStack(newNut, 18, i);
		}

		//Creates playerTwo Nuts
		//Two at 23 stack
		for (int i = 0; i < 2; i++) {
			CNut * newNut = new CNut(NutType::Wooden_Two);
			stacksNuts[23].push_back(newNut);
			MoveNutToStack(newNut, 23, i);
		}
		//Five at 12 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(NutType::Wooden_Two);
			stacksNuts[12].push_back(newNut);
			MoveNutToStack(newNut, 12, i);
		}

		//Three at 7 stack
		for (int i = 0; i < 3; i++) {
			CNut * newNut = new CNut(NutType::Wooden_Two);
			stacksNuts[7].push_back(newNut);
			MoveNutToStack(newNut, 7, i);
		}

		//Five at 5 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(NutType::Wooden_Two);
			stacksNuts[5].push_back(newNut);
			MoveNutToStack(newNut, 5, i);
		}		
	}

	void SetStarterPlayer() {
		//Generates random numbers for players , and determine which player must star playing
		int  firstPlayerScore = (rand() % 6) + 1;
		int  secondPlayerScore = (rand() % 6) + 1;

		while (firstPlayerScore == secondPlayerScore)
		{
			firstPlayerScore = (rand() % 6) + 1;
			secondPlayerScore = (rand() % 6) + 1;
		}

		if (firstPlayerScore > secondPlayerScore)
			currentPlayer = Player::One;
		else
			currentPlayer = Player::Two;
	}

	void StartGame() {
		SetStarterPlayer();
	}

	void MoveNutToStack(CNut* nut, int stackIndex, int order) {
		float margin = 28;
		float nutRealHeight = nut->height - margin;
		CStack * selectedStack = stacks[stackIndex];		
		if (stackIndex < 12) {
			nut->Move(selectedStack->x, selectedStack->y - nut->height / 2 + margin / 2 - order * nutRealHeight);
		}
		else {
			nut->Move(selectedStack->x, selectedStack->y + nut->height / 2 - margin / 2 + order * nutRealHeight);
		}

	}

	void OnClick(unsigned char button, int x, int y) override {
		std::cout << "Mouse button pressed" << std::endl;
	}

	void Run() {
		CEngine engine;
		engine.LoadTextureFromPng("wooden_nut");
		engine.LoadTextureFromPng("white_nut");
		engine.LoadTextureFromPng("wooden_stack");
		engine.LoadTextureFromPng("white_stack");
		engine.RegisterMouseInputListener(this);


		while (engine.DoEvents()) {
			engine.Clear();

			for (CStack * stack : stacks) {
				engine.Draw((CSprite *)stack);
			}

			for (auto stackedNuts : stacksNuts) {				
				for (auto nut : stackedNuts) {					
					engine.Draw((CSprite *)nut);
					nut->Tick(engine.GetDeltaTime());
				}
			}
			engine.Render();
		}
	}
};


int main(int argc, char * argv[]) {
	Game game;
	game.Run();
	return 0;
}