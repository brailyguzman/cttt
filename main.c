#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

int main() {
    set_clear_cmd();
    srand(time(NULL));

    Game game;
    game.user = 'X';
    game.cpu = 'O';

    init_board(&game);
    while (1) {
        while (1) {
            int draw;
            int won;

            clear_console();
            print_board(&game);
            user_turn(&game);

            won = won_game(&game, game.user);

            if (won == 1) {
                printf("You won the game!\n");
                break;
            }
            draw = is_draw(&game);

            if (draw == 1) {
                printf("The game was a draw!\n");
                break;
            }

            clear_console();
            cpu_turn(&game);
            print_board(&game);

            won = won_game(&game, game.cpu);

            if (won == 1) {
                printf("The CPU won!\n");
                break;
            }

            draw = is_draw(&game);

            if (draw == 1) {
                printf("The game was a draw!\n");
                break;
            }
        }

        char playAgain;
        printf("Play Again (Y/N): ");
        scanf(" %c", &playAgain);

        if (toupper(playAgain) == 'N') {
            break;
        }
    }

    return 0;
}