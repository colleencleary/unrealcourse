//
//  main.cpp
//  BullCowGame
//
//  Created by Colleen Cleary on 12/28/18.
//  Copyright © 2018 Colleen Cleary. All rights reserved.
//

/* This is the console executable that makes use of the BullCow class.
 This acts as the view in a MVC pattern and is responsible for all user interaction.
 For game logic, see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    return 0;
}


void PrintIntro() {
    // introduce the game
    std::cout << "Welcome to Bulls & Cows!" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    return;
}

void PlayGame()
{
    // play game
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    for (int32 count = 1; count <= MaxTries; count++)
    {
        FText Guess = GetValidGuess();
        
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

    }
    
}

FText GetValidGuess() // TODO: change to GetValidGuess
{
    FText Guess ="";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // get guess from player
        int32 CurrentTry = BCGame.GetCurrentTry();

        std::cout << "Try " << CurrentTry;
        std::cout << ". Enter your guess: ";
        std::getline(std::cin,Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n";
                break;
            default:
                return Guess;
        }
        std::cout << std::endl;
    } while(Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? ";
    FText response = "";
    std::getline(std::cin, response);
    std::cout << std::endl;
    return (response[0] == 'y') || (response[0] == 'Y');
}




