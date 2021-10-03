/*
Write a program that asks for a user first name and last name separately.
The program must then store the users full name inside a single string and out put it to the string.
i.e.
Input:
John
Smith
Output:
John Smith

★ Modify the program so that it then replaces every a, e, i , o, u w/ the letter z.
i.e.
John Smith -> Jzhn Smzth

★★ Modify the Program so that it reverses the users name
i.e.
John Smith -> htimS nhoJ
*/

#include <iostream>
#include <cstring>

// First and second version 
/*
int main() {
    char first_name[20];
    char last_name[20];
    std::cout << "Insert your first name:" << std::endl;
    std::cin.getline(first_name, 20);
    std::cout << "Insert your last name:" << std::endl;
    std::cin.getline(last_name, 20);

    for(int i = 0; i < (int)strlen(first_name); i++) {
        if(first_name[i] == 'a' || first_name[i] == 'e' || first_name[i] == 'i' || first_name[i] == 'o' || first_name[i] == 'u')
            first_name[i] = 'z';
    }

    for(int i = 0; i < (int)strlen(last_name); i++) {
        if(last_name[i] == 'a' || last_name[i] == 'e' || last_name[i] == 'i' || last_name[i] == 'o' || last_name[i] == 'u')
            last_name[i] = 'z';
    }

    std::cout << "\nHey there, you're name is: " << first_name << " " << last_name << std::endl;
}
*/

// Third version
int main() {
    char first_name[20];
    char last_name[20];

    std::cout << "Insert your first name:" << std::endl;
    std::cin.getline(first_name, 20);
    std::cout << "Insert your last name:" << std::endl;
    std::cin.getline(last_name, 20);

    int first_len = strlen(first_name);
    int last_len = strlen(last_name);

    char first_rev[first_len];
    char last_rev[last_len];

    for(int i = 0; i < first_len; i++) {
        int reversed = first_len - i - 1;
        first_rev[reversed] = first_name[i];
    }

    for(int i = 0; i < last_len; i++) {
        int reversed = last_len - i - 1;
        last_rev[reversed] = last_name[i];
    }

    std::cout << "\nHey there, you're name is: " << first_rev << " " << last_rev << "!" << std::endl;
}

