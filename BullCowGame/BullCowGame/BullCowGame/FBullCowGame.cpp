//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Colleen Cleary on 12/29/18.
//  Copyright © 2018 Colleen Cleary. All rights reserved.
//

#include "FBullCowGame.hpp"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32) MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
    return false;
}

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    const FString Hidden_Word = "planet";
    MyHiddenWord = Hidden_Word;
    
    MyCurrentTry = 1;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (false) {
        return EGuessStatus::Not_Isogram;
    }
    else if (false){
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
    // receives a valid guess, increments turn, and returns count;
    
    // increment turn number
    MyCurrentTry++;
    // setup a return variable
    FBullCowCount BullCowCount;

    // loop through all letters in the guess
    for (int32 GChar = 0; GChar < GetHiddenWordLength(); GChar++)
    {
        // compare letters against hidden word
        for (int32 MHWChar = 0; MHWChar < GetHiddenWordLength(); MHWChar++)
        {
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                if (GChar == MHWChar) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    return BullCowCount;
}










