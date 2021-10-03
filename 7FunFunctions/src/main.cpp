/*
Write a function titled say_hello() that outputs to the screen "Hello"

★ Modify the function so that it takes an integer argument and says hello a number of times equal to the value passed to it.

★★ Make another function that takes two integers arguments and then returns an integer that is the product of the two integers.
(i.e., integer1: 4, Integer2: 5 returns: 20)

★★★ Make a function called half() that takes an integer argument. The function must print the number it received to the screen, 
    then the program should divide that number by two to make a new number. 
    If the new number is greater than zero the function then calls the function half() passing it the new number as its argument. 
    If the number is one or less than the function exits

Call the function half() with an argument of 100, the screen output should be
100
50
25
...
...
1.
*/

#include <iostream>
#include "functions.h"

int main() {
    say_hello(2);
    std::cout << "4 * 3 = " << multiply(4, 3) << std::endl;
    half(99);
    return 0;
}