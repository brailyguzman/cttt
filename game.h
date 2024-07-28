#ifndef GAME_H
#define GAME_H

struct TicTacToe {
    char user;
    char cpu;
    char board[3][3];
};

typedef struct TicTacToe Game;

void set_clear_cmd();
void clear_console();
void init_board(Game *game);
void print_board(Game *game);
int *user_input(Game *game);
void user_turn(Game *game);
int *cpu_position(Game *game);
void cpu_turn(Game *game);
int is_draw(Game *game);
int won_game(Game *game, char player);

#endif