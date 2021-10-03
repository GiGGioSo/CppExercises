/*
    Write a program that calculates a random number 1 through 100. The program then asks the user to guess the number.
    If the user guesses too high or too low then the program should output "too high" or "too low" accordingly.
    The program must let the user continue to guess until the user correctly guesses the number.

    ★ Modify the program to output how many guesses it took the user to correctly guess the right number.

    ★★ Modify the program so that instead of the user guessing a number the computer came up with, the computer guesses the number that the user has secretely decided. 
       The user must tell the computer whether it guesed too high or too low.

    ★★★★ Modify the program so that no matter what number the user thinks of (1-100) the computer can guess it in 7 or less guesses.
*/

#include <iostream>
#include <string>
#include <time.h>
#include <math.h>

// Version 1 and 2
/*
int main() { 
    
    srand(time(NULL));

    int secret = rand() % 100 + 1;
    int guess = 0;
    int tries = 0;
    std::cout << "Guess the number! It can go from 1 to 100" << std::endl;

    while(true) {
        tries++;
        std::cin >> guess;
        while(std::cin.fail() || guess < 1 || guess > 100) {
            std::cout << "\nInvalid value, you can only insert a number from 1 to 100..." << std::endl;
        }
        if(guess == secret) {
            std::cout << "\nCongratulations, you correctly guessed the number in " << tries << " tries!" << std::endl;
            break;
        } else if(guess > secret) {
            std::cout << "\nTry lower!" << std::endl;
        } else if(guess < secret) {
            std::cout << "\nTry higher!" << std::endl;
        }
    }

    return 0;

}
*/

// Version 3 and 4
int main() {
    srand(time(NULL));
    int tries = 0;
    int secret = 0;
    int guess = 0;
    bool won = false;
    int min_guess = 1;
    int max_guess = 100;
    char result = ' ';
    
    std::cout << "Insert a number from 1 to 100 for the computer to guess!" << std::endl;
    std::cin >> secret;
    while(secret < 1 || secret > 100) {
        std::cout << "\nInvalid value, you can only insert a number from 1 to 100..." << std::endl;
        std::cin >> secret;
    }

    while(!won) {
        tries++;
        //guess = rand() % (max_guess - min_guess) + min_guess; // Random method : unoptimazed
        guess = min_guess +  ceil((max_guess - min_guess) / 2); // Always goes for the half : optimazed (max 7 tries)

        std::cout << "\nI think the number is " << guess << "! Is it (C)correct, (H)higher or (L)lower?" << std::endl;
        std::cin >> result;
        result = toupper(result);

        while(!(result == 'C' || result == 'H' || result == 'L')) {
            std::cout << "\nThe fuck are you saying, try repeating something other than (C)correct, (H)higher or (L)lower..." << std::endl;
            std::cin >> result;
            result = toupper(result);
        }
        while((result == 'C' && guess != secret) || (result == 'H' && guess >= secret) || (result == 'L' && guess <= secret)) {
            std::cout << "\nAre you sure about that? (remember you choose " << secret << " as your number and i guessed " <<  guess << ", dumbfuck)\nNow tell me if it is (C)correct, (H)higher or (L)lower" << std::endl;
            std::cin >> result;
            result = toupper(result);
        }

        switch(result) {
            case 'C':
                std::cout << "\nNice, i guessed it in " << tries << " tries!" << std::endl;
                won = true;
                break;
            case 'H':
                std::cout << "Okay, I'll try higher!" << std::endl;
                min_guess = guess + 1;
                break;
            case 'L':
                std::cout << "Okay, I'll try lower!" << std::endl;
                max_guess = guess - 1;
                break;
            default:
                std::cout << "How did you even end up here..." << std::endl;
                break;
        }

    }

    return 0;
}