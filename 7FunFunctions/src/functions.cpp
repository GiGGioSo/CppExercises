#include "functions.h"
#include <iostream>

void say_hello(int times) {
    for(int i = 0; i < times; i++) {
        std::cout << "Hello!" << std::endl;
    }
}

int multiply(int a, int b) {
    return a * b;
}

void half(int n) {
    std::cout << n << std::endl;
    if(n > 1) half((int)(n/2));
}