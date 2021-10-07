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

#define DEADNESS 6


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
    while(tmp != NULL) {
        if(tmp->bunny->sex == MALE && tmp->bunny->age > 1 && !tmp->bunny->vampire) {
            adult_male = true;
        }
        tmp = tmp->next;
    }

    Node* tmp2 = h;
    if(adult_male) {
        while(tmp2 != NULL) {
            if(tmp2->bunny->sex == FEMALE && tmp2->bunny->age > 1 && !tmp2->bunny->vampire) {
                addAtTheEnd(tmp2->bunny->color, tmp2);
            }
            tmp2 = tmp2->next;
        }
    }
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

// TODO: vampire bunnies should kill other bunnies (not vampires) randomly
int main() {
    srand(time(NULL));
    Node* head = new Node();
    for(int i = 0; i < 1; i++) {
        addInFront(head);
    }
    for(int i = 0; i < 15; i++) {

        std::cout << "\n\n\n----TURN " << i << "----\n" << std::endl;

        everyoneTimeStep(head);
        reproduce(head);
        if(removeCorpses(head) == DEADNESS) {
            std::cout << "\n\nAll rabbits died, the simulation is over!" << std::endl;
            return 0;
        }
        printList(head);

    }
    return 0;
}