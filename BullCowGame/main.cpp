/*
 * This is the console executable, that makes use of the BullCow class
 * This acts as the view in a MVC pattern, and is responsible for all the user interaction.
 * For game logic see the FBullCowGame class.
 */
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// Function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// Entry point to the application
int main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro()
{
	std::cout << "MM                   MM                                     \n";
	std::cout << "MMM+                8MM                                     \n";
	std::cout << "MMMMMM            :MMM                        MM,     ZMM   \n";
	std::cout << "ZMMM+MMMM+       MMMM                         MMMO  MMMMM   \n";
	std::cout << "   MMM  MMMMMMMMMMMN                            MMMMMMMZ    \n";
	std::cout << "    MMMMM   MMMMMMMMM                        ZMMMZMZ, MMMMMM\n";
	std::cout << "      $MMD  MMM    MMMMMMM         MMMMMMMMMMMMM         MMM\n";
	std::cout << "777MMMMDI               I7MMM~  7MMMIIIIIII+                \n";
	std::cout << "MMM?                       MMM +MM                          \n";
	std::cout << "                           ZMM +M+                          \n";
	std::cout << "        B U L L S          MMM  MM            C O W S       \n";
	std::cout << "                     MMMMMMMO    MMMMMMM                    \n";
	std::cout << "               ZMMMMMMMM               MMMMM                \n";
	std::cout << "             MMMM                         MMMMM             \n";
	std::cout << "            MMM                               MMMMM         \n";
	std::cout << "           MMO                                   MM,        \n";
	std::cout << "\n                   Welcome to Bulls & Cows\n";
	std::cout << "Isogram: a word that does not have any repeating letters in it.\n";
	std::cout << "  \"planet\" is an isogram, while \"pollen\" is not.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries to guess the correct word.\n\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();

	// loop asking for guesses until the game NOT is won and there are still turns remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = GetValidGuess();

		// Submit a valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " | Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText response = "";
	getline(std::cin, response);

	return response[0] == 'y' || response[0] == 'Y';
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		// Check status and give feedback.
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			// Assume the guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK);

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Congrats.. You Won the game. \n\n";
	else
		std::cout << "Sorry.. You have lost the game, better of next time. \n\n";
}
