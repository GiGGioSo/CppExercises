#include "bunny.h"

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

Node::Node(std::vector<std::string>& messages) {
    bunny = new Bunny(messages);
    next = NULL;
}

Node::Node(Color c, std::vector<std::string>& messages) {
    bunny = new Bunny(c, messages);
    next = NULL;
}

Node::Node(Node*& _next, std::vector<std::string>& messages) {
    bunny = new Bunny(messages);
    next = _next;
}

Node::Node(Color c, Node*& _next, std::vector<std::string>& messages) {
    bunny = new Bunny(c, messages);
    next = _next;
}

// --------BUNNY CLASS--------

// Methods initialization

Bunny::Bunny(std::vector<std::string>& messages) {
    sex = (Sex) (rand() % 2);
    color = (Color) (rand() % 4);
    age = 0;
    vampire = (rand()%100) == 33; // Estraggo un numero da 0 a 49 (inclusi), se è 33 (cioè 2% di probabilità), sarà 'true'
    alive = true;
    name = names_list[rand()%21];
    if(vampire) messages.push_back("Radioactive Mutant Vampire bunny " + name + " was born!");
    else messages.push_back("Bunny " + name + " was born!");
}

Bunny::Bunny(Color c, std::vector<std::string>& messages) {
    sex = (Sex) (rand() % 2);
    color = c;
    age = 0;
    vampire = (rand()%50) == 33; // Estraggo un numero da 0 a 49 (inclusi), se è 33 (cioè 2% di probabilità), sarà 'true'
    alive = true;
    name = names_list[rand()%21];
    if(vampire) messages.push_back("Radioactive Mutant Vampire bunny " + name + " was born!");
    else messages.push_back("Bunny " + name + " was born!");
}

void Bunny::timeStep(std::vector<std::string>& messages) {
    if((age > 9 && !vampire && alive) || (age > 49 && vampire && alive)) { 
        alive = false;
        messages.push_back("Bunny " + name + " died!");
        // std::cout << "Bunny " << name << " died!" << std::endl;
    }
    if(alive) age++;
}
