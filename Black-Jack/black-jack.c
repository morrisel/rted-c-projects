/* The program writed in ANSI standart */
/* gcc -std=c89 -pedantic -Wall -Wextra -Wconversion -Wno-main *.c -o out_black-jack */
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "gamestate.h"

void main(void)
{
	/* Initialize game state */
	struct GameState game;
	init_cardlist(&game.deck);
	fill_deck(&game.deck);
	init_cardlist(&game.dealer_hand);
	init_cardlist(&game.player_hand);
	set_cash(&game, 1000);
	set_pot(&game, 0);

	/* Main game loop */
	while(1)
	{
		betting_phase(&game);
		initial_deal_phase(&game);
		print_game_state(&game);
		blackjack_check_phase(&game);
		hit_or_stand_phase(&game);
		print_game_state(&game);
		if (calculate_hand_value(&game.player_hand) <= 21)
		{
			dealer_draw_phase(&game);
			print_game_state(&game);
		}
		reset_cards_phase(&game);
	}
	return ;
}


/* compilation: */
/* gcc -std=c89 -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_black-jack */
/* gcc -ansi -pedantic -Wall -Wextra -Wconversion -g black-jack.c -o out_black-jack */
/* gcc -std=c89 -Wall -Wextra -Wconversion black-jack.c -o out_black-jack */
/* gcc -std=c89 -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_blackjack */

/* gcc -std=c89 -E -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_black-jack.i */
/* gcc -std=c89 -S -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_black-jack.s */

/* gcc -std=c89 -c -g -O0 -pedantic -Wall -Wextra -Wconversion -Wno-main -Wshadow black-jack.c */
/* gcc black-jack.o -o out_black-jack -lm */

/* --> before c89 compilers wokrs without keyword typedef. */
