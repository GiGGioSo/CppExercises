/*
Write a program that creates a linked list of bunny objects.
Each bunny object must have
Sex: Male, Female (random at creation 50/50)
color: white, brown, black, spotted
age : 0-10 (years old)
Name : randomly chosen at creation from a list of bunny names.
radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true)

At program initialization 5 bunnies must be created and given random colors.
Each turn afterwards the bunnies age 1 year.
So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older;
a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
New bunnies born should be the same color as their mother.
If a bunny becomes older than 10 years old, it dies.
If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny.
(if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
Radioactive vampire bunnies do not die until they reach age 50.
The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age.
The program should also output each turns events such as
"Bunny Thumper was born!
Bunny Fufu was born!
Radioactive Mutant Vampire Bunny Darth Maul was born!
Bunny Julius Caesar died!
The program should write all screen output to a file.
When all the bunnies have died the program terminates.
If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)

★ Modify the program to run in real time, with each turn lasting 2 seconds, and a one second pause between each announement.

★★ Allow the user to hit the 'k' key to initiate a mass rabit cull! which causes half of all the rabits to be killed (randomly chosen).

★★★★ Modify the program to place the rabits in an 80x80 grid. Have the rabits move one space each turn randomly.
Mark juvenile males with m, adult males w/ M,
juvenile females w/ f, adult femails w/ F
radioactive mutant vampire bunnies with X

Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny. (if no empty square exits then the baby bunny isn't born)

★★★★★ Modify the program so that it saves each turn to a file and can play back at accelearted speed all subsequent turns.
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <chrono>
#include <thread>
#include "bunny.h"
#include "linked.h"

#define DEADNESS 69

const int MAXIMUM_BUNNIES = 1000;

const int TIME_TO_DISPLAY_EVENTS_MS = 2000;
const int DEFAULT_TIME_WHEN_NO_EVENTS_MS = 1000;

const int TIME_TO_PRINT_BUNNIES_MS = 2000;

const int DEFAULT_SLOW_PRINT_TOTAL_TIME = 1500;


// DONE: Print the list in a prettier way


void slow_print(std::string& message, int total_time_ms = DEFAULT_SLOW_PRINT_TOTAL_TIME) {
    unsigned int actual_size = 0;
    for(size_t i = 0; i < message.size(); i++) {
        if(message[i] != '\n') actual_size++;
    }
    int time_between_words_ms = total_time_ms / actual_size;
    for(size_t i = 0; i < message.size(); i++) {
        std::cout << message[i];
        std::cout.flush();
        if(message[i] != '\n') std::this_thread::sleep_for(std::chrono::milliseconds(time_between_words_ms));
    }
}

void everyoneTimeStep(Node*& h, std::vector<std::string>& messages) {
    Node* tmp = h;
    while(tmp != NULL) {
        tmp->bunny->timeStep(messages);
        tmp = tmp->next;
    }
}

void reproduce(Node*& h, std::vector<std::string>& messages) {
    bool adult_male = false;
    Node* tmp = h;
    while(tmp != NULL) { // just check if there is a male bunny older than 2
        if(tmp->bunny->sex == MALE && tmp->bunny->age > 2 && !tmp->bunny->vampire) {
            adult_male = true;
        }
        tmp = tmp->next;
    }

    Node* tmp2 = h;
    if(adult_male) {
        while(tmp2 != NULL) { // for every female bunny, a new bunny gets added at the end, with her same color
            if(tmp2->bunny->sex == FEMALE && tmp2->bunny->age > 2 && !tmp2->bunny->vampire) {
                addInFront(tmp2->bunny->color, h, messages);
            }
            tmp2 = tmp2->next;
        }
    }
}

void transformBunnies(Node*& h, std::vector<std::string>& messages) {
    Node* current = h;
    int normals = 0;
    int vampires = 0;
    int bunnies_to_transform = 0;
    while(current != NULL) { // Check how many vampires and sane bunnies are there
        if(current->bunny->vampire) vampires++;
        else normals++;
        current = current->next;
    }
    // std::cout << "There are " << normals << " normal bunnies and " << vampires << " vampire bunnies" << std::endl;
    if(normals == 0) return;
    if(vampires == 0) return;
    bunnies_to_transform = (vampires > normals) ? normals : vampires; // If there are more vampires than normal bunnies, I reduce the number of bunnies to transform to the one of the normals ones
    int unlucky_indexes[bunnies_to_transform]; // array of the indexes of the bunnies that will have to be transformed
    for(int i = 0; i < bunnies_to_transform; i++) { // initalize the whole array to -1 (not assigned), because 0 is a valid value for this use case
        unlucky_indexes[i] = -1;
    }
    // std::cout << "Starting to assign unlucky indexes\n" << std::endl;
    for(int i = 0; i < bunnies_to_transform; i++) { // all the bunnies get picked
        bool isOk = true;
        int unlucky = 0;
        do {
            isOk = true;
            unlucky = rand() % normals; // pick a random index from the possible normals bunnies that will have to die
            // std::cout << "The possible number is " << unlucky << std::endl;
            for(int j = 0; j < bunnies_to_transform; j++) {
                if(unlucky_indexes[j] == unlucky) {
                    // std::cout << "Unlucky number " << unlucky << " found in position " << j << std::endl;
                    isOk = false;
                    break;
                }
            }
        } while (!isOk);
        unlucky_indexes[i] = unlucky;
    }
    // std::cout << "Starting to trasform the unlucky bunnies" << std::endl;

    // now we actually transform the bunnies :)

    current = h; // reuse 'current' variable and reset it to the head pointer
    int current_index = 0;
    while(current != NULL) {
        if(!current->bunny->vampire) { // everything happens only if the bunny is NOT vampire obv
            for(int i = 0; i < bunnies_to_transform; i++) {
                if(unlucky_indexes[i] == current_index) {
                    messages.push_back("Bunny " + current->bunny->name + " was transformed in a vampire!");
                    current->bunny->vampire = true; // here it transforms
                    break;
                }
            }
            current_index++;
        }
        current = current->next;
    }
    return;
}

int removeCorpses(Node*& h) {
    Node* tmp = h;

    if(tmp == NULL) return DEADNESS;

    if(!tmp->bunny->alive) {
        Node* newNext = tmp->next;
        while(newNext != NULL && !newNext->bunny->alive) {
            newNext = newNext->next;
        }
        if(newNext == NULL) {
            h = newNext;
            return DEADNESS;
        } else {
            h = newNext;
            removeCorpses(h);
        }
    } else {
        while(tmp->next != NULL && tmp->next->bunny->alive) {
            tmp = tmp->next;
        }
        if(tmp->next == NULL) {
            return 0;
        } else {
            Node* newNext = tmp->next;
            while(newNext != NULL && !newNext->bunny->alive) {
                newNext = newNext->next;
            }
            if(newNext == NULL) {
                tmp->next = newNext;
                return 0;
            } else {
                tmp->next = newNext;
                removeCorpses(tmp->next);
            }
        }
    }
    return 0;
    /*if(!tmp->bunny->alive) { // CONTROLLO SE IL PRIMO CONIGLIO È MORTO, E IN CASO SOSTITUISCO HEAD CON UN ALTRO
        Node* newNext = tmp->next;
        while(newNext != NULL && !newNext->bunny->alive) {
            Node* tmp2 = newNext;  // La variabile tmp2 dovrebbe fare in modo che istanza di coniglio non vivo venga eliminata, penso
            newNext = newNext->next;
            delete tmp2;
        }
        if(newNext == NULL) {
            delete newNext;
            return 69; // LA PARTITA SIGNIFICA CHE È FINITA, SONO TUTTI MORTI
        } else {
            h = newNext;
            newNext = NULL;
            delete newNext;
        }
    }

    tmp = h;

    while(tmp != NULL) {
        if(!tmp->next->bunny->alive) {
            prev = tmp;
            Node* newNext = tmp->next;
            while(newNext != NULL && !newNext->bunny->alive) {
                Node* tmp3 = newNext;  // La variabile tmp3 dovrebbe fare in modo che istanza di coniglio non vivo venga eliminata, penso
                newNext = newNext->next;
                delete tmp3;
            }
            prev->next = newNext;
            tmp = prev->next;
        }
        tmp = tmp->next;
    }
    return 0;
    */
}

void killHalfBunnies(Node*& h, int& length) {
    int unlucky_bunnies[length / 2];
    for(int i = 0; i < length/2; i++) {
        unlucky_bunnies[i] = -1;
    }
    for(int i = 0; i < length/2; i++) {
        bool isOk = true;
        int unlucky_index = 0;
        do {
            isOk = true; // I assume the random number will be OK, then I check if it's not
            unlucky_index = rand() % length; // random number among the possible ones (length)
            //std::cout << "Random number is " << unlucky_index << std::endl;
            for(int j = 0; j < length/2; j++) {
                if(unlucky_bunnies[j] == unlucky_index) {
                    isOk = false;
                    break;
                }
            }
        } while(!isOk);
        unlucky_bunnies[i] = unlucky_index;
    }

    Node* current = h;
    int current_index = 0;
    while(current != NULL) {
        for(int i = 0; i < length/2; i++) {
            if(unlucky_bunnies[i] == current_index) {
                current->bunny->alive = false;  
                break;
            }
        }
        current_index++;
        current = current->next;
    }
}

void printEventsAndList(Node*& h, std::vector<std::string>& messages, int length, int turn = -1) {
    // Printing turn title
    std::string turn_message;
    if(turn >= 0) turn_message = "\n\n\n----TURN " + std::to_string(turn+1) + "----\n";
    else turn_message = "----INITIAL SITUATION----\n";
    slow_print(turn_message);
    // Printing events
    int time_between_events_ms = 0;
    if(messages.size() > 0) {
        time_between_events_ms = TIME_TO_DISPLAY_EVENTS_MS / messages.size();
    } else { // If there are no messages I want to annouce it
        messages.push_back("Nothing happened this turn...");
        time_between_events_ms = DEFAULT_TIME_WHEN_NO_EVENTS_MS;
    }
    for(const std::string& message : messages) {
        std::cout << message << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_between_events_ms));
    }
    messages.clear();
    // Printing list of bunnies
    Node* current = h;
    if(current == NULL) return;
    std::string tmp_message = "\n_Bunny List_\n";
    slow_print(tmp_message, DEFAULT_SLOW_PRINT_TOTAL_TIME/2);
    int time_between_bunnies_ms = (length > 0) ? TIME_TO_PRINT_BUNNIES_MS / length : 0;
    int count = 1;
    while(current != NULL) {
        // Getting all the info of the bunny in a pretty way
        // ID
        std::string tmp = "  Bunny ID: ";
        tmp += (count > 999) ? std::to_string(count) : ((count > 99) ? std::to_string(count) + " " : (count > 9) ? std::to_string(count) + "  " : std::to_string(count) + "   ");
        // NAME
        tmp += "   Name: " + current->bunny->name + std::string(9 - current->bunny->name.size(), ' ');
        // AGE
        tmp += "   Age: " + std::to_string(current->bunny->age);
        if(current->bunny->age < 10) tmp += " ";
        // COLOR
        Color col = current->bunny->color; // I don't want to have to write 'current->bunny->color' every time in the next if statements
        tmp += "   Color: ";
        tmp += (col == WHITE) ? "WHITE   " : ((col == BROWN) ? "BROWN   " : ((col == BLACK) ? "BLACK   " : "SPOTTED "));
        // VAMPIRE
        tmp += "   Vampire: ";
        tmp += (current->bunny->vampire) ? "YES" : "NO";
        std::cout << tmp << std::endl;
        current = current->next;
        count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_between_bunnies_ms));
    }
}

int main() {
    srand(time(NULL));
    std::vector<std::string> messages = {};
    bool gameOver = false;
    int most_bunnies = 0;
    int length = 0;
    Node* head = new Node(messages);

    for(int i = 0; i < 5; i++) {
        addInFront(head, messages);
    }
    length = getLength(head);
    printEventsAndList(head, messages, length);
    for(int i = 0; i < 300; i++) {

        // std::cout << "Time stepping..." << std::endl;
        everyoneTimeStep(head, messages);
        // std::cout << "Reproducing..." << std::endl;
        reproduce(head, messages);
        // std::cout << "Transforming bunnies..." << std::endl;
        transformBunnies(head, messages);
        // std::cout << "Removing corpses..." << std::endl;
        length = getLength(head);
        if(length > MAXIMUM_BUNNIES) killHalfBunnies(head, length);
        if(length > most_bunnies) most_bunnies = length;
        if(removeCorpses(head) == DEADNESS) gameOver = true;
        length = getLength(head);
        // std::cout << "Printing the list..." << std::endl;
        printEventsAndList(head, messages, length, i+1);
        if(gameOver) {
            std::cout << "\n\nAll bunnies died, the simulation is over! The maximum number of bunnies has been " << most_bunnies << "!!" << std::endl;
            return 0;
        }
    }
    return 0;
}