#include "linked.h"
#include "bunny.h"
#include <iostream>

int addInFront(Node*& h) {
    Node* newNode = new Node();
    newNode->next = h;
    h = newNode;
    std::cout << "Added new bunny at the start" << std::endl;
    return 0;
}

int addInMiddle(Node*& h, int pos) {
    Node* newNode = new Node();

    Node* current = h;
    for(int i = 0; i < pos; i++) {
        if(current != NULL) {
            if(i == pos-1) {
                current->next = newNode;
            } else {
                current = current->next;
            }
        } else {
            return -1;
        }
    }
    std::cout << "Added new bunny at position " << pos << std::endl;
    return 0;
}

int addAtTheEnd(Node*& h) {
    Node* newNode = new Node();

    Node* current = h;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    std::cout << "Added new bunny at the end" << std::endl;
    return 0;
}

void printList(Node*& h) {
    Node* current = h;
    int count = 0;

    while(current != NULL) {
        std::cout << "Bunny " << count << ": name = " << current->bunny->name << ",    color = " << current->bunny->color << ",    age = " << current->bunny->age << ",    alive = " << current->bunny->alive << std::endl;
        current = current->next;
        count++;
    }
}