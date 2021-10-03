/*

    Write a program that presents the user w/ a choice of your 5 favorite beverages (Coke, Water, Sprite, ... , Whatever).
    Then allow the user to choose a beverage by entering a number 1-5.
    Output which beverage they chose.

    ★ If you program uses if statements instead of a switch statement, modify it to use a switch statement.
    If instead your program uses a switch statement, modify it to use if/else-if statements.

    ★★ Modify the program so that if the user enters a choice other than 1-5 then it will output "Error. choice was not valid, here is your money back."
*/

#include <iostream>

enum Drink{
    COKE, WATER, FANTA, SPRITE, GINGER
};

int main(){
    int choice;

    std::cout << "Type a number from 1 to 5 to select a beverage:\nChoose wisely...\n\n1. Coke\n2. Water\n3. Fanta\n4. Sprite\n5. Ginger\n" << std::endl;

    std::cin >> choice;
    std::cout << std::endl;

    choice--;
    
    switch(choice){
        case COKE:
            std::cout << "Here's your coke!" << std::endl;
            break;
        case WATER:
            std::cout << "Here's your water!" << std::endl;
            break;
        case FANTA:
            std::cout << "Here's your fanta!" << std::endl;
            break;
        case SPRITE:
            std::cout << "Here's your sprite!" << std::endl;
            break;
        case GINGER:
            std::cout << "Here's your ginger!" << std::endl;
            break;
        default:
            std::cout << "Error. choice was not valid, here is your money back." << std::endl;
            break;
    }

    return 0;

}