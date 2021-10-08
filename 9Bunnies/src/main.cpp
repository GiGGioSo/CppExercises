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
#include <time.h>
#include <random>
#include "bunny.h"
#include "linked.h"

#define DEADNESS 69

// TODO: kill half of the bunnies if they are 1000 or more

void everyoneTimeStep(Node*& h) {
    Node* tmp = h;
    while(tmp != NULL) {
        tmp->bunny->timeStep();
        tmp = tmp->next;
    }
}

void reproduce(Node*& h) {
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
                addAtTheEnd(tmp2->bunny->color, tmp2);
            }
            tmp2 = tmp2->next;
        }
    }
}

// DONE: vampire bunnies should kill other bunnies (not vampires) randomly
void transformBunnies(Node*& h) {
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
    int unlucky_index[bunnies_to_transform]; // array of the indexes of the bunnies that will have to be transformed
    for(int i = 0; i < bunnies_to_transform; i++) { // initalize the whole array to -1 (not assigned), because 0 is a valid value for this use case
        unlucky_index[i] = -1;
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
                if(unlucky_index[j] == -1) continue;
                if(unlucky_index[j] == unlucky) {
                    // std::cout << "Unlucky number " << unlucky << " found in position " << j << std::endl;
                    isOk = false;
                    break;
                }
            }
        } while (!isOk);
        unlucky_index[i] = unlucky;
    }
    // std::cout << "Starting to trasform the unlucky bunnies" << std::endl;

    // now we actually transform the bunnies :)

    current = h; // reuse 'current' variable and reset it to the head pointer
    int current_index = 0;
    while(current != NULL) {
        if(!current->bunny->vampire) { // everything happens only if the bunny is NOT vampire obv
            for(int i = 0; i < bunnies_to_transform; i++) {
                if(unlucky_index[i] == current_index) {
                    std::cout << "Bunny " << current->bunny->name << " was transformed in a vampire!" << std::endl;
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

int main() {
    bool gameOver = false;
    int most_bunnies = 0;
    srand(time(NULL));
    Node* head = new Node();
    for(int i = 0; i < 4; i++) {
        addInFront(head);
    }
    for(int i = 0; i < 300; i++) {

        std::cout << "\n\n\n----TURN " << i << "----\n" << std::endl;
        // std::cout << "Time stepping..." << std::endl;
        everyoneTimeStep(head);
        // std::cout << "Reproducing..." << std::endl;
        reproduce(head);
        // std::cout << "Transforming bunnies..." << std::endl;
        transformBunnies(head);
        // std::cout << "Removing corpses..." << std::endl;
        if(removeCorpses(head) == DEADNESS) gameOver = true;
        // std::cout << "Printing the list..." << std::endl;
        printList(head);
        int length = getLength(head);
        if(length > most_bunnies) most_bunnies = length;
        if(gameOver) {
            std::cout << "\n\nAll bunnies died, the simulation is over! The maximum number of bunnies has been " << most_bunnies << "!!" << std::endl;
            return 0;
        }
    }
    return 0;
}