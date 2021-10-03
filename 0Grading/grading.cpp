/*
    Write a program that allows the user to enter the grade scored in a programming class (0-100).
    If the user scored a 100 then notify the user that they got a perfect score.

    ★ Modify the program so that if the user scored a 90-100 it informs the user that they scored an A

    ★★ Modify the program so that it will notify the user of their letter grade
    0-59 F 60-69 D 70-79 C 80-89 B 90-100 A
*/

#include <iostream>

int main() {
    int score = -1;
    char mark;

    while(true) {
        std::cout << "Insert a score from 0 to 100!" << std::endl << "Insert an invalid score to exit the program." << std::endl;
        std::cin >> score;
        if(std::cin.fail() ||score < 0 || score > 100) break;
        if(score < 60) mark = 'F';
        else if (score < 70) mark = 'D';
        else if (score < 80) mark = 'C';
        else if (score < 90) mark = 'B';
        else if (score < 101) mark = 'A';

        if(score == 100) std::cout << "PERFECT SCORE!" << std::endl;
        std::cout << "Your grade is: " << mark << std::endl;
    }
    std::cout << "Why tho..." << std::endl;
    return 0;

}