/*
    Make a two player tic tac toe game.

    ★ Modify the program so that it will announce when a player has won the game (and which player won, x or o)

    ★★ Modify the program so that it is a one player game against the computer (with the computer making its moves randomly)

    ★★★★ Modify the program so that anytime the player is a\bout to win (aka, they have 2 of 3 x's in a row, the computer will block w/ an o)
*/

//  1 = 'X'
//  0 = ' '
// -1 = 'O'

#include <iostream>
#include <random>
#include <time.h>

enum Value {
    O = -1, EMP, X
};

enum Player {
    BOT, ONE, TWO, NONE
};

void drawBoard(Value board[3][3]) {

    std::cout << "   |   |   " << std::endl;

    for(int y = 0; y < 3; y++) {
        char p1 = ((board[0][y] == EMP) ? ' ' : ((board[0][y] == X) ? 'X' : 'O'));
        char p2 = ((board[1][y] == EMP) ? ' ' : ((board[1][y] == X) ? 'X' : 'O'));
        char p3 = ((board[2][y] == EMP) ? ' ' : ((board[2][y] == X) ? 'X' : 'O'));

        std::cout << " " << p1 << " | " << p2 << " | " << p3 << " " << std::endl;
        if(y != 2) std::cout << "-----------" << std::endl;

    }

    std::cout << "   |   |   \n" << std::endl;
}

// First and second version
/*
int main() {
    Value board[3][3] = {{EMP, EMP, EMP}, {EMP, EMP, EMP}, {EMP, EMP, EMP}};

    bool gameover = false;
    Player player = ONE;
    Player winner;

    std::cout << "Welcome to TicTacToe, play against a friend or against youself if you are lonely!" << std::endl;
    std::cout << "Enter the moves using the coordinates of where you want to place you sign (es. 1 2 , or 3 2)\n" << std::endl;

    while(!gameover) {
        system("clear");
        std::cout << "\n\n" << std::endl;
        drawBoard(board);
        int moveX = 0;
        int moveY = 0;
        // Input
        if(player == ONE) {
            std::cout << "Player ONE, make your move..." << std::endl;
            std::cin >> moveX >> moveY;
            while(moveX > 3 || moveX < 1 || moveY > 3 || moveY < 1 || board[moveX-1][moveY-1] != EMP) {
                std::cout << "Invalid move, remember you can only enter the moves using coordinates of where you want to place your sign (in an empty space)" << std::endl;
                std::cout << "Player ONE, make your move... (example: 3 1)" << std::endl;
                std::cin >> moveX >> moveY;
            }
            board[moveX-1][moveY-1] = X;
            player = TWO;
        } else if(player == TWO) {
            std::cout << "Player TWO, make your move..." << std::endl;
            std::cin >> moveX >> moveY;
            while(moveX > 3 || moveX < 1 || moveY > 3 || moveY < 1 || board[moveX-1][moveY-1] != EMP) {
                std::cout << "Invalid move, remember you can only enter the moves using coordinates of where you want to place your sign (in an empty space)" << std::endl;
                std::cout << "Player ONE, make your move... (example: 3 1)" << std::endl;
                std::cin >> moveX >> moveY;
            }
            board[moveX-1][moveY-1] = O;
            player = ONE;
        }

        // Win conditions
        bool full_board = true;
        for(int i = 0; i < 3; i++) {
            if(board[i][0] + board[i][1] + board[i][2] == 3 || board[0][i] + board[1][i] + board[2][i] == 3) {
                winner = ONE;
                gameover = true;
            } else if(board[i][0] + board[i][1] + board[i][2] == -3 || board[0][i] + board[1][i] + board[2][i] == -3) {
                winner = TWO;
                gameover = true;
            }
            for(int k = 0; k < 3; k++) {
                if(board[i][k] == EMP) full_board = false;
            }
        }
        if(full_board) {
            winner = NONE;
            gameover = true;
        }
        if(board[0][0] + board[1][1] + board[2][2] == 3 || board[2][0] + board[1][1] + board[0][2] == 3) {
            winner = ONE;
            gameover = true;
        } else if(board[0][0] + board[1][1] + board[2][2] == -3 || board[2][0] + board[1][1] + board[0][2] == -3) {
            winner = TWO;
            gameover = true;
        }
    }

    system("clear");
    std::cout << "\n\n" << std::endl;
    drawBoard(board);

    if(winner == ONE) {
        std::cout << "Gameover! Player ONE won!" << std::endl;
    } else if(winner == TWO) {
        std::cout << "Gameover! Player TWO won!" << std::endl;
    } else {
        std::cout << "Gameover! No one won!" << std::endl;
    }

    return 0;
}
*/

// Third and final version
int main() {
    Value board[3][3] = {{EMP, EMP, EMP}, {EMP, EMP, EMP}, {EMP, EMP, EMP}};
    srand(time(NULL));

    bool gameover = false;
    Player player = ONE;
    Player winner;

    std::cout << "Welcome to TicTacToe, play against a friend or against youself if you are lonely!" << std::endl;
    std::cout << "Enter the moves using the coordinates of where you want to place you sign (es. 1 2 , or 3 2)\n" << std::endl;

    while(!gameover) {
        system("clear");
        std::cout << "\n\n" << std::endl;
        drawBoard(board);
        int moveX = 0;
        int moveY = 0;
        // Input
        if(player == ONE) {
            std::cout << "Player ONE, make your move..." << std::endl;
            std::cin >> moveX >> moveY;
            while(moveX > 3 || moveX < 1 || moveY > 3 || moveY < 1 || board[moveX-1][moveY-1] != EMP) {
                std::cout << "Invalid move, remember you can only enter the moves using coordinates of where you want to place your sign (in an empty space)" << std::endl;
                std::cout << "Player ONE, make your move... (example: 3 1)" << std::endl;
                std::cin >> moveX >> moveY;
            }
            board[moveX-1][moveY-1] = X;
            player = BOT;
        } else if(player == BOT) { // Bot AI
            bool already_moved = false;
            for(int i = 0; i < 3; i++) {
                if(board[i][0] + board[i][1] + board[i][2] == 2) {
                    (board[i][0] == EMP) ? board[i][0] = O : ((board[i][1] == EMP) ? board[i][1] = O : board[i][2] = O);
                    already_moved = true;
                } else if(board[0][i] + board[1][i] + board[2][i] == 2) {
                    (board[0][i] == EMP) ? board[0][i] = O : ((board[1][i] == EMP) ? board[1][i] = O : board[2][i] = O);
                    already_moved = true;
                }
            }
            if(board[0][0] + board[1][1] + board[2][2] == 2 && !already_moved) {
                (board[0][0] == EMP) ? board[0][0] = O : ((board[1][1] == EMP) ? board[1][1] = O : board[2][2] = O);
                already_moved = true;
            } else if(board[2][0] + board[1][1] + board[0][2] == 2 && !already_moved) {
                (board[2][0] == EMP) ? board[2][0] = O : ((board[1][1] == EMP) ? board[1][1] = O : board[0][2] = O);
                already_moved = true;
            }
            
            if(!already_moved) {
                do {
                    moveX = rand() % 3 + 1;
                    moveY = rand() % 3 + 1;
                } while(board[moveX-1][moveY-1] != EMP);
                board[moveX-1][moveY-1] = O;
            }
            player = ONE;
        }

        // Win conditions
        bool full_board = true;
        for(int i = 0; i < 3; i++) {
            if(board[i][0] + board[i][1] + board[i][2] == 3 || board[0][i] + board[1][i] + board[2][i] == 3) {
                winner = ONE;
                gameover = true;
            } else if(board[i][0] + board[i][1] + board[i][2] == -3 || board[0][i] + board[1][i] + board[2][i] == -3) {
                winner = BOT;
                gameover = true;
            }
            for(int k = 0; k < 3; k++) {
                if(board[i][k] == EMP) full_board = false;
            }
        }
        if(full_board) {
            winner = NONE;
            gameover = true;
        }

        if(board[0][0] + board[1][1] + board[2][2] == 3 || board[2][0] + board[1][1] + board[0][2] == 3) {
            winner = ONE;
            gameover = true;
        } else if(board[0][0] + board[1][1] + board[2][2] == -3 || board[2][0] + board[1][1] + board[0][2] == -3) {
            winner = BOT;
            gameover = true;
        }
    }

    system("clear");
    std::cout << "\n\n" << std::endl;
    drawBoard(board);

    if(winner == ONE) {
        std::cout << "Gameover! Player ONE won!" << std::endl;
    } else if(winner == BOT) {
        std::cout << "Gameover! Player BOT won!" << std::endl;
    } else if(winner == NONE) {
        std::cout << "Gameover! No one won!" << std::endl;
    }

    return 0;
}