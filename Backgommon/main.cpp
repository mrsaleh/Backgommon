#include "Engine.h"
#include "Nut.h"
#include "Stack.h"
#include "tween.hpp"
#include <iostream>
#include <stdlib.h>
#include <numeric>

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
	void createStacks() {
		int offset = 50;	
		const int middleBarSize = 150;

		//Bottom stacks
		for (int i = 0; i < 12; i++) {
			CStack* newStack;
			if (i % 2 == 0)
				newStack = new CStack(StackType::Wooden_Two, i);
			else
				newStack = new CStack(StackType::White_One, i);
			stacks.push_back(newStack);
			
		}

		for (int i = 0; i < 12; i++) {
			auto newStack = stacks[i];
			if (i == 0)
				offset += (12 - i +1) * newStack->width ;
			if (i == 6)
				offset -= 100;
			newStack->x = offset;
			newStack->pivotY = 1.0f;
			newStack->y = 720;
			offset -= newStack->width;
		}

		//Top stacks
		for (int i =0; i < 12; i++) {
			CStack* newStack;
			if (i % 2 == 1)
				newStack = new CStack(StackType::Wooden_Two, i + 12);
			else
				newStack = new CStack(StackType::White_One, i + 12);
			stacks.push_back(newStack);
		}

		offset = 50;
		for (int i = 0; i < 12; i++) {			
			auto newStack = stacks[i + 12];
			if (i == 0)
				offset += newStack->width / 2 ;
			if (i == 6)
				offset += 100;
			newStack->x += offset;
			newStack->ratation = 180.0f;
			newStack->y = 0;
			
			offset += newStack->width;
		}

		
	}

	void addNutsToTheBoards() {
		//Creates playerOne Nuts
		//Two at 0 stack
		for (int i = 0; i < 2; i++) {
			CNut* newNut = new CNut(Player::One);
			stacks[0]->AddNut(newNut);
		}
		//Five at 11 stack
		for (int i = 0; i < 5; i++) {
			CNut* newNut = new CNut(Player::One);
			stacks[11]->AddNut(newNut);
		}

		//Three at 16 stack
		for (int i = 0; i < 3; i++) {
			CNut* newNut = new CNut(Player::One);
			stacks[16]->AddNut(newNut);
		}

		//Five at 18 stack
		for (int i = 0; i < 5; i++) {
			CNut* newNut = new CNut(Player::One);
			stacks[18]->AddNut(newNut);
		}

		//Creates playerTwo Nuts
		//Two at 23 stack
		for (int i = 0; i < 2; i++) {
			CNut* newNut = new CNut(Player::Two);
			stacks[23]->AddNut(newNut);
		}
		//Five at 12 stack
		for (int i = 0; i < 5; i++) {
			CNut* newNut = new CNut(Player::Two);
			stacks[12]->AddNut(newNut);
		}

		//Three at 7 stack
		for (int i = 0; i < 3; i++) {
			CNut* newNut = new CNut(Player::Two);
			stacks[7]->AddNut(newNut);
		}

		//Five at 5 stack
		for (int i = 0; i < 5; i++) {
			CNut* newNut = new CNut(Player::Two);
			stacks[5]->AddNut(newNut);
		}
	}

	Game() {
		selectedNut = nullptr;
		int selectedNutStack = -1;
		//Creates the stacks
		
		createStacks();
		addNutsToTheBoards();
		
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

	CNut* FindNut(int x,int y) {
		for (auto stack : stacks) {
			for (auto nut : stack->nuts) {
				if (nut->Contains(x, y))
					return nut;
			}
		}
		return nullptr;
	}

	CStack* FindStack(int x, int y,int& stackIndex) {
		int i = 0;
		for (auto stack : stacks) {
			if(stack->Contains(x,y)){
				stackIndex = i;
				return stack;
			}
			i++;
		}

		stackIndex = -1;
		return nullptr;
	}

	void DeselectNuts() {
		for (auto stack : stacks) {
			for (auto nut : stack->nuts) {
				nut->SetSelected(false);
			}
		}
	}

	void DeselectStacks() {
		for (auto stack : stacks) {
			stack->SetSelected(false);
		}
	}

	std::vector<int> FindCombinations(std::vector<int> diceNumbers) {
		std::vector<int> combinations;
		for (auto i = 0; i<diceNumbers.size(); i++) {			
			combinations.push_back(diceNumbers[i]);			
			
			for (auto j = i+1; j < diceNumbers.size(); j++) {
				auto start = std::next(diceNumbers.begin(), i); 
				auto end = std::next(diceNumbers.begin(), j+1);
				combinations.push_back(std::accumulate(start, end, 0));
			}
		}

		return combinations;
	}

	/*
	Now we must check that the move he/she requested is 
	possible or not
	If the opponent have more than one nut in the stack 
	player can not his/her nut there , if the opponent have only 
	one nut , player can remove the opponent's nut from board,
	if the stack is empty , player can move the nut to the stack
	Notice: player only can move the nut to the next stacks , can't move 
	it back and only can move to stacks which are in the sum or one of his
	dice numbers
	*/
	std::vector<CStack*> FindPossibleTargetStacks(CNut* nut, std::vector<int> dice)
	{
		std::vector<CStack *> possibleTargetStacks;		

		auto availableMoves = FindCombinations(dice);
		for (auto move : availableMoves) {
			//Check if the move is possible
			auto moveStackIndex = 0;
			if(nut->owner == Player::One)
				moveStackIndex = nut->stackIndex + move;
			else
				moveStackIndex = nut->stackIndex - move;

			if (moveStackIndex < stacks.size()) {
				auto targetStack = stacks[moveStackIndex];				
				if (targetStack->nuts.size() == 0) {
					possibleTargetStacks.push_back(targetStack);
				}else{
					auto latestNut = targetStack->nuts.back();
					if (nut->owner == latestNut->owner) {
						possibleTargetStacks.push_back(targetStack);
					}
					else if (targetStack->nuts.size() == 1) {
						//If there was only one opponent nut
						possibleTargetStacks.push_back(targetStack);
					}
				}					
			}
			else {
				//This move , moves the nut out of the board,
				//Player only can do this in the situations that
				//All of her/his nuts are in the lastest quarter of 
				//the board

			}
		}

		return possibleTargetStacks;		
	}

	void OnClick(unsigned char button, int x, int y) override {
		
		std::vector<int> dice = { 1, 2 };

		auto clickedNut = FindNut(x, y);;
		
		if (clickedNut != nullptr) {
			if (clickedNut == stacks[clickedNut->stackIndex]->nuts.back()) {
				DeselectNuts();

				clickedNut->SetSelected(true);
				selectedNut = clickedNut;

				if (selectedNut != nullptr) {
					DeselectStacks();
					auto targetStacks = FindPossibleTargetStacks(selectedNut, dice);
					for (auto stack : targetStacks) {
						stack->SetSelected(true);
					}
				}
			}
			else {
				std::cout << "Backgommon Rule: You can't move the nut that has another nut over it!" << std::endl;
			}
			
		}
		else {
			int selectedStackIndex = 0;
			auto selectedStack = FindStack(x,y, selectedStackIndex);
			if (selectedStack != nullptr) {
				if (selectedNut !=  nullptr) {
					auto possibleTargetStacks = FindPossibleTargetStacks(selectedNut, dice);
					auto targetStackIterator =  std::find(possibleTargetStacks.begin(), possibleTargetStacks.end(), selectedStack);
					if (targetStackIterator != possibleTargetStacks.end()) {
						auto nutStack = stacks[selectedNut->stackIndex];
						if (selectedNut == nutStack->PeekNut()) {
							//Remove the nut from its old stack to the new stack
							auto targetStack = (*targetStackIterator);
							if (targetStack->nuts.size() > 1 && targetStack->nuts.back()->owner != selectedNut->owner)
								throw std::runtime_error("The move is impossible , there must be an issue in "
									"FindPossibleTargetStacks functions that didn't filter this move");
							if (targetStack->nuts.size() == 1 && targetStack->nuts.back()->owner != selectedNut->owner) {
								//We must remove that lonely poor opponent's nut
								
								auto removedNut = targetStack->PopNut();
								RemoveNutFromBoard(removedNut);
							}
							nutStack->PopNut();
							targetStack->AddNut(selectedNut);

							DeselectNuts();
							DeselectStacks();
							selectedNut = nullptr;
							selectedStack = nullptr;

						}

					}
				}
				//User clicked a stack , now must make sure that 
				//does he/she meant to move a nut there , do he/she
				// selected a nut before
				
			}
		}
	}

	void RemoveNutFromBoard(CNut* removedNut) {
		//Move it to the middle of board
		if (removedNut->owner == Player::One){
			playerOneRemovedNuts.push_back(removedNut);
			removedNut->Move(stacks.back()->width * 7 + stacks.back()->width/2, 500);
		}
		else {
			playerTwoRemovedNuts.push_back(removedNut);
			removedNut->Move(stacks.back()->width * 7 + stacks.back()->width / 2, 10);
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
					nut->Tick(engine.GetDeltaTime());
					engine.Draw((CSprite *)nut);					
				}
			}

			for (CNut * nut : playerOneRemovedNuts) {
				nut->Tick(engine.GetDeltaTime());
				engine.Draw((CSprite *)nut);				
			}

			for (CNut * nut : playerTwoRemovedNuts) {
				nut->Tick(engine.GetDeltaTime());
				engine.Draw((CSprite *)nut);
			}


			engine.Render();
		}
	}
};


int main(int argc, char* argv[]) {
	std::vector<int> dice = {3,5 };
	
	Game game;
	std::vector<int> combinations = game.FindCombinations(dice);	

	game.StartGame();
	game.Run();
	return 0;
}