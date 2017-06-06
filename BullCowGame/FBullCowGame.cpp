#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries = { {3,5}, {4,7}, {5,11}, {6,15} }; // { WordLength, MaxTries }
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "world"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // If the guess isnt an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	// If the guess isnt all lowercase return an error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong return an error
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise return OK
	{
		return EGuessStatus::OK;
	}
}

//Recieves a VALID guess, and incriments turn and returns count;
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) // MyHiddenWordChar
	{
		// compare letters against the guessed word
		for (int32 GChar = 0; GChar < WordLength; GChar++) // GuessChar
		{
			// If they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they're in the same place
				if (MHWChar == GChar)
				{
					// incriment bulls			
					BullCowCount.Bulls++;
				}
				else
				{
					// incriment cows
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterScreen; // setup our map

	for (auto Letter : Word)	// loop through all the letters of the word
	{
		Letter = tolower(Letter);
		if (LetterScreen[Letter]) // if the letter is in the map
			return false; // we do NOT have an isogram

		LetterScreen[Letter] = true; // add the letter to the map as seen

	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	for(auto Letter : Word)
	{
		if (!tolower(Letter))
			return false;
	}
	return true;
}
