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

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

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
    std::cout << "Welcome to Bulls & Cows!" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    PrintGameSummary();
    return;
}

FText GetValidGuess() // TODO: change to GetValidGuess
{
    FText Guess ="";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // get guess from player
        int32 CurrentTry = BCGame.GetCurrentTry();

        std::cout << "Try " << CurrentTry;
        std::cout << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        std::getline(std::cin,Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            default:
                // assume guess is valid
                break;
        }
    } while(Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? ";
    FText response = "";
    std::getline(std::cin, response);
    std::cout << std::endl;
    return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary(){
    if (BCGame.IsGameWon()){
        std::cout << "Well Done -- you win!\n";
    } else {
        std::cout << "Better luck next time.\n";
    }
}


