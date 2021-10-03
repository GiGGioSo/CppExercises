/*
    Make a program that outputs a simple grid based gameboard to the screen using either numbers or characters.
    i.e.

    . . . . . . . . . .
    . G . . . . . . . .
    . . . . . . T . . .
    . . . . . . . . . .
    . . . . T . . . . .
    . . . . . . T . . .
    . . . . . . . . . X


    or

    0 0 0 0 0 0 0 0 0 0
    0 5 0 0 6 0 0 0 0 0
    0 0 0 0 0 0 7 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 7 0 0 0 0 0 0
    0 0 0 0 0 0 7 0 0 0
    0 0 0 0 0 0 0 0 0 4


    Allow the user (marked by G in the example) to move either up, down, left, or right each turn. If the player steps on a trap then they lose. If the make it to the treasure 'X' then they win.

    ★★ Add enemies that move randomly in any direction once per turn. (enemies just like traps cause the player to lose if touched)

    HINT: Don't let the player move off the gameboard! You program will crash if they move off the top or bottom of the board!
    (the same holds true for enemies)
*/

#include <iostream>
#include <random>
#include <time.h>
#include <string.h>
#include "entities.h"
#include "util.h"

int num_entities;
int gamer_index;

void drawBoard(Entity entities[]) {
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
            std::string val = "";
            if(Entity::getEntityIndex(x, y, entities, num_entities) == -1) val = " .";
            else if(entities[Entity::getEntityIndex(x, y, entities, num_entities)].type == G) val = " G";
            else if(entities[Entity::getEntityIndex(x, y, entities, num_entities)].type == E) val = " E";
            else if(entities[Entity::getEntityIndex(x, y, entities, num_entities)].type == T) val = " T";
            else if(entities[Entity::getEntityIndex(x, y, entities, num_entities)].type == X) val = " X";
            else if(entities[Entity::getEntityIndex(x, y, entities, num_entities)].type == O) val = " O";
            std::cout << val;
        }
        std::cout << std::endl;
    }
}

int main() {
    bool gameover = false;
    srand(time(NULL));
    const char starting_board[10][10] = {
        { 'V', 'V', 'V', 'E', 'V', 'V', 'T', 'V', 'V', 'V' },
        { 'V', 'G', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V' },
        { 'V', 'V', 'V', 'V', 'V', 'V', 'E', 'V', 'V', 'V' },
        { 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V' },
        { 'V', 'V', 'V', 'V', 'T', 'V', 'V', 'V', 'V', 'V' },
        { 'V', 'T', 'V', 'V', 'V', 'V', 'T', 'V', 'V', 'V' },
        { 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'E' },
        { 'V', 'V', 'V', 'V', 'V', 'E', 'V', 'V', 'V', 'V' },
        { 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V' },
        { 'T', 'E', 'T', 'V', 'V', 'V', 'V', 'V', 'V', 'X' }
    };
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(starting_board[i][j] != 'V') num_entities++;
        }
    }

    Entity* entities = new Entity[num_entities];

    int t_current_entity = 0;
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
            if(starting_board[y][x] == 'G') { 
                entities[t_current_entity] = Entity(x, y, G);
                gamer_index = t_current_entity;
                t_current_entity++;
            }
            else if(starting_board[y][x] == 'E') {
                entities[t_current_entity] = Entity(x, y, E);
                t_current_entity++;
            }
            else if(starting_board[y][x] == 'T') {
                entities[t_current_entity] = Entity(x, y, T);
                t_current_entity++;
            }
            else if(starting_board[y][x] == 'X') {
                entities[t_current_entity] = Entity(x, y, X);
                t_current_entity++;
            }
        }
    }

    bool welcome = true;
    std::cout << "Welcome to the dungeon, (G)you have to reach the (X)treasure avoid the strationary (T)traps and the moving (E)enemies!" << std::endl;
    std::cout << "You can move using W, A, S, D...\n" << std::endl;

    drawBoard(entities);

    std::string end_message = "";

    while(!gameover) {
        system("clear");
        if(welcome) {
            std::cout << "\nWelcome to THE DUNGEON, (G)you have to reach the (X)treasure avoid the strationary (T)traps and the moving (E)enemies!\n" << std::endl;
            welcome = false;
        }
        std::cout << "_/| THE DUNGEON |\\_\n" << std::endl;
        drawBoard(entities);
        std::cout << "\nInsert your move (W, A, S, D)..." << std::endl;
    
        std::string input;
        std::cin >> input;
        trim(input);
        for (auto & c: input) c = (char)toupper(c);
        while(!(input.compare("W") == 0 || input.compare("A") == 0 || input.compare("S") == 0 || input.compare("D") == 0)) {
            std::cout << "Invalid move, you can only use W, A, S D! Try again..." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string input;
            std::cin >> input;
            trim(input);
            for (auto & c: input) c = (char)toupper(c);
            if(input.compare("W") == 0 || input.compare("A") == 0 || input.compare("S") == 0 || input.compare("D") == 0) break;
        }

        // I WANT PLAYER TO UPDATE FIRST, LET HIM MOVE BEFORE THE ZOMBIES
        if(entities[gamer_index].type == G) {
            int g_x = -1; 
            int g_y = -1;
            if(input.compare("W") == 0) { // GET THE NEW COORDINATES
                g_x = entities[gamer_index].x;
                g_y = entities[gamer_index].y-1;
            } else if(input.compare("A") == 0) {
                g_x = entities[gamer_index].x-1;
                g_y = entities[gamer_index].y;
            } else if(input.compare("S") == 0) {
                g_x = entities[gamer_index].x;
                g_y = entities[gamer_index].y+1;
            } else if(input.compare("D") == 0){
                g_x = entities[gamer_index].x+1;
                g_y = entities[gamer_index].y;
            }
            if(g_x < 0 || g_x > 9 || g_y < 0 || g_y > 9) ;
            else if(Entity::getEntityIndex(g_x, g_y, entities, num_entities) == -1) { // IF THERE'S NO ENTITY THERE, JUST MOVE
                entities[gamer_index].x = g_x;
                entities[gamer_index].y = g_y;
            } else {
                Entity& e = entities[Entity::getEntityIndex(g_x, g_y, entities, num_entities)];
                if(e.type == T) { // DECIDES WHAT TO DO BASED ON WHICH TYPE IS IN THOSE COORDINATES
                    entities[gamer_index].type = O;
                    end_message = "You stepped on a trap and die, that's funny!";
                    gameover = true;
                } else if(e.type == E) {
                    entities[gamer_index].type = O;
                    end_message = "You got caught by an enemy and got killed, you deserved it!";
                    gameover = true;
                } else if(e.type == X) {
                    end_message = "You collected the treasure and died of happiness, how sad!";
                    gameover = true;
                }
            }
        }
        for(int i = 0; i < num_entities; i++) {
            if(i == gamer_index) ;
            else if(entities[i].type == E) {    
                int e_x = -1;
                int e_y = -1;
                do {
                    e_x = -1;
                    e_y = -1;
                    int random = rand() % 4;
                    if(random == 0) {
                        e_x = entities[i].x;
                        e_y = entities[i].y-1;
                    } else if(random == 1) {
                        e_x = entities[i].x-1;
                        e_y = entities[i].y;
                    } else if(random == 2) {
                        e_x = entities[i].x;
                        e_y = entities[i].y+1;
                    } else if(random == 3) {
                        e_x = entities[i].x+1;
                        e_y = entities[i].y;
                    }
                } while (!(Entity::getEntityIndex(e_x, e_y, entities, num_entities) == -1 || entities[Entity::getEntityIndex(e_x, e_y, entities, num_entities)].type == G) || (e_x < 0 || e_x > 9 || e_y < 0 || e_y > 9));
                if(Entity::getEntityIndex(e_x, e_y, entities, num_entities) == -1) {
                    entities[i].x = e_x;
                    entities[i].y = e_y;
                } else if(entities[Entity::getEntityIndex(e_x, e_y, entities, num_entities)].type == G){
                    entities[Entity::getEntityIndex(e_x, e_y, entities, num_entities)].type = O;
                    end_message = "You got caught by an enemy and got killed, you deserved it!";
                    gameover = true;
                }
            }
        }

    }

    system("clear");
    std::cout << "_/| THE DUNGEON |\\_\n" << std::endl;
    drawBoard(entities);
    std::cout << "\n\n" << end_message << std::endl;

    return 0;

}