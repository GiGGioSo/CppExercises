#pragma once

#include <iostream>
#include "bunny.h"

int addInFront(Node*& h, std::vector<std::string>& messages);
int addInFront(Color c, Node*& h, std::vector<std::string>& messages);

int addInMiddle(Node*& h, int pos, std::vector<std::string>& messages);
int addInMiddle(Color c, Node*& h, int pos, std::vector<std::string>& messages);

int addAtTheEnd(Node*& h, std::vector<std::string>& messages);
int addAtTheEnd(Color c, Node*& h, std::vector<std::string>& messages);

int getLength(Node*& h);

void printList(Node*& h);