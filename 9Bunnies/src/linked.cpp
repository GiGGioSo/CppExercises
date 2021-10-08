#include "linked.h"
#include "bunny.h"
#include <iostream>

int addInFront(Node*& h) {
    Node* newNode = new Node();
    newNode->next = h;
    h = newNode;
    return 0;
}

int addInFront(Color c, Node*& h) {
    Node* newNode = new Node(c);
    newNode->next = h;
    h = newNode;
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
    return 0;
}

int addInMiddle(Color c, Node*& h, int pos) {
    Node* newNode = new Node(c);

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
    return 0;
}


int addAtTheEnd(Node*& h) {
    Node* newNode = new Node();

    Node* current = h;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 0;
}

int addAtTheEnd(Color c, Node*& h) {
    Node* newNode = new Node(c);

    Node* current = h;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 0;
}


int getLength(Node*& h) {
    Node* current = h;
    int count = 0;
    while(current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// TODO: print bunnies by age  [sort them in general or just when you print them??]
void printList(Node*& h) {
    Node* current = h;
    int count = 0;

    while(current != NULL) {
        std::cout << "Bunny " << count << ": name = " << current->bunny->name << ",    color = " << current->bunny->color << ",    age = " << current->bunny->age << ",    alive = " << current->bunny->alive << ",    vampire = " << current->bunny->vampire << std::endl;
        current = current->next;
        count++;
    }
}