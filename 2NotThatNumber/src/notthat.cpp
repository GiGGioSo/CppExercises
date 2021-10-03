/*
    Write a program that continues to asks the user to enter any number other than 5 until the user enters the number 5.
    Then tell the user "Hey! you weren't supposed to enter 5!" and exit the program.

    ★ Modify the program so that after 10 iterations if the user still hasn't entered 5 will tell the user "Wow, you're more patient then I am, you win." and exit.

    ★★ Modify the program so that it asks the user to enter any number other than the number equal to the number of times they've been asked to enter a number. 
    (i.e on the first iteration "Please enter any number other than 0" and on the second iteration "Please enter any number other than 1"m etc. etc. 
    The program must behave accordingly exiting when the user enters the number they were asked not to.)
*/

#include <iostream>

int main() {
    
    int num;
    int iterations = 0;

    bool running = true;

    while(running) {
        std::cout << "\nPlease enter a number! (you better not choose " << iterations << "...)" << std::endl;
        std::cin >> num;

        if(num == iterations) {
            std::cout << "\nHey! you weren't supposed to enter " << iterations << "!" << std::endl;
            running = false;
        }
        if(iterations > 8) {
            std::cout << "\nWow, you're more patient then I am, you win." << std::endl;
            running = false;
        }

        iterations++;
    }

    return 0;
}