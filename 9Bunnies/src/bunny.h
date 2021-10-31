#pragma once
#include "bunny.h"
#include <iostream>
#include <vector>

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
    Bunny(std::vector<std::string>& messages);
    Bunny(Color c, std::vector<std::string>& messages);
    void timeStep(std::vector<std::string>& messages);

};

class Node
{
public:
    Bunny* bunny;
    Node* next;

public:
    Node(std::vector<std::string>& messages);
    Node(Color c, std::vector<std::string>& messages);
    Node(Node*& _next, std::vector<std::string>& messages);
    Node(Color c, Node*& _next, std::vector<std::string>& messages);

};