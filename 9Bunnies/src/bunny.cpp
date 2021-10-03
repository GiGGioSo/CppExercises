#include "bunny.h"
#include <iostream>

// name list
std::string names_list[] = {
        "Gioele",
        "Eloisa",
        "Daniele",
        "Giovanni",
        "Samuele",
        "Elia",
        "Cosmin",
        "Radu",
        "Candu",
        "PietrA",
        "Pietro",
        "Marco",
        "Giuseppe",
        "Alfredo",
        "Kyrios",
        "Dante",
        "Cesare",
        "Giancarlo",
        "Bob",
        "Sus",
        "Sas"
    };


// NODE CLASS INITIALIZATION

Node::Node() {
    bunny = new Bunny();
    next = NULL;
}

Node::Node(Node*& _next) {
    bunny = new Bunny();
    next = _next;
}

// --------BUNNY CLASS--------

// Methods initialization

Bunny::Bunny() {
    sex = (Sex) (rand() % 2);
    color = (Color) (rand() % 4);
    age = 0;
    vampire = (rand()%50) == 33; // Estraggo un numero da 0 a 49 (inclusi), se è 33 (cioè 2% di probabilità), sarà 'true'
    alive = true;
    name = names_list[rand()%21];
    std::cout << "Bunny " << name << " was born!" << std::endl;
}

void Bunny::timeStep() {
    if((age > 9 && !vampire) || (age > 50 && vampire)) { 
        alive = false;
        std::cout << "Bunny " << name << " died!" << std::endl;
    }
    if(alive) age++;
}
