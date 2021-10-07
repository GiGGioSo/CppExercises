#pragma once
#include "bunny.h"
#include <iostream>

enum Color {
    WHITE, BROWN, BLACK, SPOTTED
};

enum Sex {
    MALE, FEMALE
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
    Bunny(Color c);
    void timeStep();

};

class Node
{
public:
    Bunny* bunny;
    Node* next;

public:
    Node();
    Node(Color c);
    Node(Node*& _next);
    Node(Color c, Node*& _next);

};