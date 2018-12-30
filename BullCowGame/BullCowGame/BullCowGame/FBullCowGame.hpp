//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Colleen Cleary on 12/29/18.
//  Copyright © 2018 Colleen Cleary. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
#endif /* FBullCowGame_hpp */

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

enum class EResetStatus
{
    No_Hidden_Word,
    OK
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value
    
    void Reset(); // TODO make a more rich return value
    
    // counts bulls and cows and increases try # assuming valid guess
    FBullCowCount SubmitGuess(FString);
    
// ignore this for now
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
};
