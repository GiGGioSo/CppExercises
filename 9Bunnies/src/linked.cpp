#include "linked.h"
#include "bunny.h"
#include <iostream>

int addInFront(Node*& h, std::vector<std::string>& messages) {
    Node* newNode = new Node(messages);
    newNode->next = h;
    h = newNode;
    return 0;
}

int addInFront(Color c, Node*& h, std::vector<std::string>& messages) {
    Node* newNode = new Node(c, messages);
    newNode->next = h;
    h = newNode;
    return 0;
}


int addInMiddle(Node*& h, int pos, std::vector<std::string>& messages) {
    Node* newNode = new Node(messages);

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

int addInMiddle(Color c, Node*& h, int pos, std::vector<std::string>& messages) {
    Node* newNode = new Node(c, messages);

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


int addAtTheEnd(Node*& h, std::vector<std::string>& messages) {
    Node* newNode = new Node(messages);

    Node* current = h;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 0;
}

int addAtTheEnd(Color c, Node*& h, std::vector<std::string>& messages) {
    Node* newNode = new Node(c, messages);

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