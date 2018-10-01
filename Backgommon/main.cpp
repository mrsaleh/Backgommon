#include "Engine.h"
#include "Nut.h"
#include "Stack.h"
#include "tween.hpp"
#include <iostream>
#include <stdlib.h>

#include "Shared.h"

class Game : public CMouseInputListener {
private:
	Player currentPlayer;
	int currentPlayerDice1;
	int currentPlayerDice2;
	std::vector<CNut *> playerOneRemovedNuts;
	std::vector<CNut *> playerTwoRemovedNuts;
	std::vector<CStack *> stacks;
	CNut * selectedNut;
	int selectedNutStack;
public:
	Game() {
		selectedNut = nullptr;
		int selectedNutStack = -1;
		//Creates the stacks
		for (int i = 11; i >= 0; i--) {
			CStack * newStack;
			if (i % 2 == 0)
				newStack = new CStack(StackType::Wooden_Two, i);
			else
				newStack = new CStack(StackType::White_One, i);
			newStack->x += i* newStack->width + newStack->width / 2;
			newStack->pivotY = 1.0f;
			newStack->y = 720;
			stacks.push_back(newStack);
		}

		for (int i = 0; i < 12; i++) {
			CStack * newStack;
			if (i % 2 == 1)
				newStack = new CStack(StackType::Wooden_Two, i + 12);
			else
				newStack = new CStack(StackType::White_One, i + 12);
			newStack->x += i* newStack->width + newStack->width / 2;
			newStack->ratation = 180.0f;
			newStack->y = 0;
			stacks.push_back(newStack);
		}

		//Creates playerOne Nuts
		//Two at 0 stack
		for (int i = 0; i < 2; i++) {
			CNut * newNut = new CNut(Player::One);
			stacks[0]->AddNut(newNut);
		}
		//Five at 11 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(Player::One);
			stacks[11]->AddNut(newNut);
		}

		//Three at 16 stack
		for (int i = 0; i < 3; i++) {
			CNut * newNut = new CNut(Player::One);
			stacks[16]->AddNut(newNut);
		}

		//Five at 18 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(Player::One);
			stacks[18]->AddNut(newNut);
		}

		//Test
		CNut * newNut = new CNut(Player::Two);
		stacks[3]->AddNut(newNut);

		//Creates playerTwo Nuts
		//Two at 23 stack
		for (int i = 0; i < 2; i++) {
			CNut * newNut = new CNut(Player::Two);
			stacks[23]->AddNut(newNut);
		}
		//Five at 12 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(Player::Two);
			stacks[12]->AddNut(newNut);
		}

		//Three at 7 stack
		for (int i = 0; i < 3; i++) {
			CNut * newNut = new CNut(Player::Two);
			stacks[7]->AddNut(newNut);
		}

		//Five at 5 stack
		for (int i = 0; i < 5; i++) {
			CNut * newNut = new CNut(Player::Two);
			stacks[5]->AddNut(newNut);
		}
	}

	int NewDiceScore() {
		return (rand() % 6) + 1;
	}

	void SetStarterPlayer() {
		//Generates random numbers for players , and determine which player must star playing
		int firstPlayerDice1;
		int firstPlayerDice2;
		int secondPlayerDice1;
		int secondPlayerDice2;

		int  firstPlayerScore;
		int  secondPlayerScore;

		do
		{
			firstPlayerDice1 = NewDiceScore();
			firstPlayerDice2 = NewDiceScore();
			secondPlayerDice1 = NewDiceScore();
			secondPlayerDice2 = NewDiceScore();

			firstPlayerScore = firstPlayerDice1 + firstPlayerDice2;
			secondPlayerScore = secondPlayerDice1 + secondPlayerDice2;
		} while (firstPlayerScore == secondPlayerScore);

		if (firstPlayerScore > secondPlayerScore) {
			currentPlayer = Player::One;
			currentPlayerDice1 = firstPlayerDice1;
			currentPlayerDice2 = secondPlayerDice2;
			std::cout << "Player one won the roll!";
		}
		else {
			currentPlayer = Player::Two;
			currentPlayerDice1 = secondPlayerDice1;
			currentPlayerDice2 = secondPlayerDice2;
			std::cout << "Player two won the roll!";
		}
		std::cout << "Dice: " << currentPlayerDice1 << " , " << currentPlayerDice2;
	}

	void Next() {
		if (currentPlayer == Player::One) {
			currentPlayer = Player::Two;
			std::cout << "Player two turn";
		}
		else {
			currentPlayer = Player::One;
			std::cout << "Player one turn";
		}
		currentPlayerDice1 = NewDiceScore();
		currentPlayerDice2 = NewDiceScore();
		std::cout << "Dice: " << currentPlayerDice1 << " , " << currentPlayerDice2;
	}

	void StartGame() {
		SetStarterPlayer();
	}



	void OnClick(unsigned char button, int x, int y) override {
		std::cout << "Mouse button pressed" << std::endl;
		for (int i = 0; i < stacks.size(); i++) {
			if (selectedNut == nullptr) {
				//Selects a nut under cursor
				CNut * selectedNut = stacks[i]->Select(x, y, currentPlayer);
				if (selectedNut != nullptr) {
					this->selectedNut = selectedNut;
					this->selectedNutStack = i;
					std::cout << "Stack " << i << "nut selected!" << std::endl;

				}
			}
			else {
				//Moves selected nut to the under-cursor stack
				if (stacks[i]->Contains(x, y)) {


					CStack * stack = stacks[i];
					if (stack->CanAdd(selectedNut)) {
						stacks[selectedNutStack]->PopNut();
						stack->AddNut(this->selectedNut);
						CNut * removedNut = stack->PickRemovedNut();
						if (removedNut != nullptr) {
							if (removedNut->owner == Player::One) {
								playerOneRemovedNuts.push_back(removedNut);
								removedNut->Move(900, 100);
							}
							else if (removedNut->owner == Player::Two) {
								playerTwoRemovedNuts.push_back(removedNut);
								removedNut->Move(900, 100);
							}
						}
						this->selectedNut = nullptr;
						std::cout << "Nut moved from " << selectedNutStack << " to " << i << " stack!";
					}
					else {
						std::cout << "Nut can not moved from " << selectedNutStack << " to " << i << " stack!";
						this->selectedNut = nullptr;
					}
				}

			}
		}
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

			for (CStack * stack : stacks) {
				for (auto nut : stack->nuts) {
					engine.Draw((CSprite *)nut);
					nut->Tick(engine.GetDeltaTime());
				}
			}

			for (CNut * nut : playerOneRemovedNuts) {
				engine.Draw((CSprite *)nut);
				nut->Tick(engine.GetDeltaTime());
			}

			for (CNut * nut : playerTwoRemovedNuts) {
				engine.Draw((CSprite *)nut);
				nut->Tick(engine.GetDeltaTime());
			}


			engine.Render();
		}
	}
};


int main(int argc, char * argv[]) {
	Game game;
	game.StartGame();
	game.Run();
	return 0;
}