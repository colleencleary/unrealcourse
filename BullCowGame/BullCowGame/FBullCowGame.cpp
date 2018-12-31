//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Colleen Cleary on 12/29/18.
//  Copyright © 2018 Colleen Cleary. All rights reserved.
//

#pragma once

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int; // to make syntax Unreal friendly

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32) MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
    return WordLengthToMaxTries[GetHiddenWordLength()];
}


void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    const FString Hidden_Word = "planet";
    MyHiddenWord = Hidden_Word;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)){
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}

// receives a valid guess, increments turn, and returns count;
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 Word_Length = GetHiddenWordLength(); // assuming same length as guess

    // loop through all letters in the guess
    for (int32 GChar = 0; GChar < Word_Length; GChar++) {
        // compare letters against hidden word
        for (int32 MHWChar = 0; MHWChar < Word_Length; MHWChar++) {
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                if (GChar == MHWChar) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == Word_Length) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }
    
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    for (auto Letter : Word) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}












