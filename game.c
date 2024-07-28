#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char clear_cmd[6];

void set_clear_cmd() {
    #ifdef _WIN32
        snprintf(clear_cmd, sizeof(clear_cmd), "cls");
    #else
        snprintf(clear_cmd, sizeof(clear_cmd), "clear");
    #endif
}

void clear_console() {
    system(clear_cmd);
}

void init_board(Game *game) {
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 3; y++) {
            game->board[i][y] = '*';
        }
    }
}

void print_board(Game *game) {
    for (int i = 0; i < 3; i++) {
        printf("|  %c  |  %c  |  %c  |\n", game->board[i][0], game->board[i][1], game->board[i][2]);
    }
}

int *user_input(Game *game) {
    static int position[2];
    int row, col;

    while (1) {
        printf("Enter Row: ");
        scanf("%d", &row);

        printf("Enter Col: ");
        scanf("%d", &col);

        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            if (game->board[row][col] == '*') {
                position[0] = row;
                position[1] = col;
                break;
            } else {
                clear_console();
                printf("Position is already taken. Try again\n");
                print_board(game);
            }
        } else {
            printf(
                "Invalid position. Row and Column must be between 0 and 2. "
                "Try again.\n");
        }
    }

    return position;
}

void user_turn(Game *game) {
    int *position = user_input(game);
    game->board[position[0]][position[1]] = game->user;
}

int *cpu_position(Game *game) {
    static int position[2];

    // If the middle position is available, the cpu will try to take it.
    if (game->board[1][1] == '*') {
        position[0] = 1;
        position[1] = 1;
        return position;
    }

    // First Horizontal
    if (game->board[0][0] == '*' && game->board[0][1] == game->cpu && game->board[0][2] == game->cpu) {
        position[0] = 0;
        position[1] = 0;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[0][1] == '*' && game->board[0][2] == game->cpu) {
        position[0] = 0;
        position[1] = 1;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[0][1] == game->cpu && game->board[0][2] == '*') {
        position[0] = 0;
        position[1] = 2;

        return position;
    }

    // Second Horizontal
    if (game->board[1][0] == '*' && game->board[1][1] == game->cpu && game->board[1][2] == game->cpu) {
        position[0] = 1;
        position[1] = 0;

        return position;
    } else if (game->board[1][0] == game->cpu && game->board[1][1] == '*' && game->board[1][2] == game->cpu) {
        position[0] = 1;
        position[1] = 1;

        return position;
    } else if (game->board[1][0] == game->cpu && game->board[1][1] == game->cpu && game->board[1][2] == '*') {
        position[0] = 1;
        position[1] = 2;

        return position;
    }

    // Third Horizontal
    if (game->board[1][0] == '*' && game->board[1][1] == game->cpu && game->board[1][2] == game->cpu) {
        position[0] = 1;
        position[1] = 0;

        return position;
    } else if (game->board[1][0] == game->cpu && game->board[1][1] == '*' && game->board[1][2] == game->cpu) {
        position[0] = 1;
        position[1] = 1;

        return position;
    } else if (game->board[1][0] == game->cpu && game->board[1][1] == game->cpu && game->board[1][2] == '*') {
        position[0] = 1;
        position[1] = 2;

        return position;
    }

    // First Diagonal
    if (game->board[0][0] == '*' && game->board[1][1] == game->cpu && game->board[2][2] == game->cpu) {
        position[0] = 0;
        position[1] = 0;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[1][1] == '*' && game->board[2][2] == game->cpu) {
        position[0] = 1;
        position[1] = 1;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[1][1] == game->cpu && game->board[2][2] == '*') {
        position[0] = 2;
        position[1] = 2;

        return position;
    }

    // Second Diagonal
    if (game->board[0][2] == '*' && game->board[1][1] == game->cpu && game->board[2][0] == game->cpu) {
        position[0] = 0;
        position[1] = 2;

        return position;
    } else if (game->board[0][2] == game->cpu && game->board[1][1] == '*' && game->board[2][0] == game->cpu) {
        position[0] = 1;
        position[1] = 1;

        return position;
    } else if (game->board[0][2] == game->cpu && game->board[1][1] == game->cpu && game->board[2][0] == '*') {
        position[0] = 2;
        position[1] = 0;

        return position;
    }

    // First Vertical
    if (game->board[0][0] == '*' && game->board[1][0] == game->cpu && game->board[2][0] == game->cpu) {
        position[0] = 0;
        position[1] = 0;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[1][0] == '*' && game->board[2][0] == game->cpu) {
        position[0] = 1;
        position[1] = 0;

        return position;
    } else if (game->board[0][0] == game->cpu && game->board[1][0] == game->cpu && game->board[2][0] == '*') {
        position[0] = 2;
        position[1] = 0;

        return position;
    }

    // Second Vertical
    if (game->board[0][1] == '*' && game->board[1][1] == game->cpu && game->board[2][1] == game->cpu) {
        position[0] = 0;
        position[1] = 1;

        return position;
    } else if (game->board[0][1] == game->cpu && game->board[1][1] == '*' && game->board[2][1] == game->cpu) {
        position[0] = 1;
        position[1] = 1;

        return position;
    } else if (game->board[0][1] == game->cpu && game->board[1][1] == game->cpu && game->board[2][1] == '*') {
        position[0] = 2;
        position[1] = 1;

        return position;
    }

    // Third Vertical
    if (game->board[0][2] == '*' && game->board[1][2] == game->cpu && game->board[2][2] == game->cpu) {
        position[0] = 0;
        position[1] = 2;

        return position;
    } else if (game->board[0][2] == game->cpu && game->board[1][2] == '*' && game->board[2][2] == game->cpu) {
        position[0] = 1;
        position[1] = 2;

        return position;
    } else if (game->board[0][2] == game->cpu && game->board[1][2] == game->cpu && game->board[2][2] == '*') {
        position[0] = 2;
        position[1] = 2;

        return position;
    }

    while (1) {
        int generatedRow = rand() % 3;
        int generatedCol = rand() % 3;

        if (game->board[generatedRow][generatedCol] == '*') {
            position[0] = generatedRow;
            position[1] = generatedCol;
            break;
        }
    }

    return position;
}

void cpu_turn(Game *game) {
    int *position = cpu_position(game);
    game->board[position[0]][position[1]] = game->cpu;
}

int is_draw(Game *game) {
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 3; y++) {
            if (game->board[i][y] == '*') {
                return 0;
            }
        }
    }

    return 1;
}

int won_game(Game *game, char player) {
    // First Horizontal
    if (game->board[0][0] == player && game->board[0][1] == player && game->board[0][2] == player) {
        return 1;
    }
    // Second Horizontal
    if (game->board[1][0] == player && game->board[1][1] == player && game->board[1][2] == player) {
        return 1;
    }
    // Third Horizontal
    if (game->board[2][0] == player && game->board[2][1] == player && game->board[2][2] == player) {
        return 1;
    }

    // First Vertical
    if (game->board[0][0] == player && game->board[1][0] == player && game->board[2][0] == player) {
        return 1;
    }
    // Second Vertical
    if (game->board[0][1] == player && game->board[1][1] == player && game->board[2][1] == player) {
        return 1;
    }
    // Third Vertical
    if (game->board[0][2] == player && game->board[1][2] == player && game->board[2][2] == player) {
        return 1;
    }

    // First Diagonal
    if (game->board[0][0] == player && game->board[1][1] == player && game->board[2][2] == player) {
        return 1;
    }
    // Second Diagonal
    if (game->board[0][2] == player && game->board[1][1] == player && game->board[2][0] == player) {
        return 1;
    }

    return 0;
}