/* The program writed in ANSI standart */
/* gcc -std=c89 -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_black-jack */
#include <stdio.h>
#include <stdlib.h>

/* --- Card representation --- */
/* struct members declarations */
struct Card;
struct CardList;
struct GameStateAccessor;
struct GameState;


int main(void)
{
	puts("Hello");

	puts("World");


	return 0;
}



/* compilation: */
/* gcc -ansi -pedantic -Wall -Wextra -Wconversion -g black-jack.c -o out_black-jack */
/* gcc -std=c89 -Wall -Wextra -Wconversion black-jack.c -o out_black-jack */
/* gcc -std=c89 -Wall -Wextra -Wconversion -Wno-main black-jack.c -o out_blackjack */


/* gcc -std=c89 -c -g -O0 -pedantic -Wall -Wextra -Wconversion -Wno-main -Wshadow black-jack.c */
/* gcc black-jack.o -o out_black-jack -lm */

/* --> before c89 compilers wokrs without keyword typedef. */
