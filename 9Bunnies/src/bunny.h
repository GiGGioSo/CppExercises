#pragma once
#include "bunny.h"
#include <iostream>

enum Color {
    WHITE, BROWN, BLACK, SPOTTED
};

enum Sex {
    MALE, FEMALE
};

class Node
{
public:
    Bunny* bunny;
    Node* next;

public:
    Node();
    Node(Node*& _next);

};

class Bunny
{
public: // VARIABLES
    Sex sex;
    Color color;
    unsigned int age;
    std::string name;
    bool vampire;
    bool alive;

public: // METHODS
    Bunny();
    void timeStep();

};
