#include "entities.h"
#include <iostream>

Entity::Entity() {}

Entity::Entity(int _x, int _y, EntityType _type) {
    x = _x;
    y = _y;
    type = _type;
}

int Entity::getEntityIndex(int _x, int _y, Entity entities[], int len) {
    for(int i = 0; i < len; i++) {
        if(entities[i].x == _x && entities[i].y == _y) return i;
    }
    return -1;
}