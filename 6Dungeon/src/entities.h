#pragma once

enum EntityType {
    G, E, T, X, O
};

class Entity {
public:
    int x;
    int y;
    EntityType type;

public:

    // dummy contructor, don't use it
    Entity();
    
    Entity(int _x, int _y, EntityType _type);

    // find an entity inside an array with specific coordinates
    static int getEntityIndex(int _x, int _y, Entity entities[], int len); 
};