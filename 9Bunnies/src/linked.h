#pragma once

#include <iostream>
#include "bunny.h"

int addInFront(Node*& h);
int addInFront(Color c, Node*& h);

int addInMiddle(Node*& h, int pos);
int addInMiddle(Color c, Node*& h, int pos);

int addAtTheEnd(Node*& h);
int addAtTheEnd(Color c, Node*& h);

int getLength(Node*& h);

void printList(Node*& h);