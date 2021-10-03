/*
    Write a program that asks the user to enter the number of pancakes eaten for breakfast by 10 different people (Person 1, Person 2, ..., Person 10)
    Once the data has been entered the program must analyze the data and output which person ate the most pancakes for breakfast.

    ★ Modify the program so that it also outputs which person ate the least number of pancakes for breakfast.

    ★★★★ Modify the program so that it outputs a list in order of number of pancakes eaten of all 10 people.
    i.e.
    Person 4: ate 10 pancakes
    Person 3: ate 7 pancakes
    Person 8: ate 4 pancakes
    ...
    Person 5: ate 0 pancakes
*/

#include <iostream>

// First and second version of the task
/*
int main() { 
    const int N = 10;
    int pancakes[N];
    int satiated = 0;

    for(int i = 0; i < N; i++) {

        std::cout << "\nHow many pancakes did Person " << (i+1) << " ate?" << std::endl;
        std::cin >> pancakes[i];

        while(std::cin.fail() || pancakes[i] < 0) {
            std::cout << "Please insert a valid number of pancakes..." << std::endl;
            std::cin >> pancakes[i];
        }

        if(pancakes[i] < pancakes[satiated]) satiated = i;

    }

    std::cout << "\n----------------------\nThe most satiated person is Person " << (satiated+1) << "!!!" << std::endl;
}
*/

int main() {
    const int N = 10;
    int pancakes[N];
    int sorted_persons[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for(int i = 0; i < N; i++) {

        std::cout << "\nHow many pancakes did Person " << (i+1) << " ate?" << std::endl;
        std::cin >> pancakes[i];

        while(std::cin.fail() || pancakes[i] < 0) {
            std::cout << "Please insert a valid number of pancakes..." << std::endl;
            std::cin >> pancakes[i];
        }
    }

    std::cout << "\n-----------------------\n" << std::endl;

    for(int i = 0; i < N; i++) {
        int hungriest = i;
        for(int k = i; k < N; k++) {
            
            if(pancakes[sorted_persons[k]] > pancakes[sorted_persons[hungriest]]) hungriest = k;
        }
        int temp = sorted_persons[i];
        sorted_persons[i] = sorted_persons[hungriest];
        sorted_persons[hungriest] = temp;
    }
    for(int i = 0; i < N; i++) {
        std::cout << "Person " << (sorted_persons[i]+1) << " ate " << pancakes[sorted_persons[i]] << " pancakes!" << std::endl;
    }
}