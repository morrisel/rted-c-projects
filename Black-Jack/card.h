#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

struct Card
{
	unsigned char data;
	struct Card *next;
};

struct CardList
{
	struct Card *head;
	size_t len;
};

void init_cardlist(struct CardList *cardlist );

struct Card *card_new_char(unsigned char rank , unsigned char );
struct Card *card_new_int(int rank , int suit );

void card_push(struct CardList *cardlist , struct Card *card );
void fill_deck(struct CardList *deck );
void clear_cardlist(struct CardList *cardlist );

int get_rank(struct Card *card );

struct Card *card_remove_at(struct CardList *cardlist , size_t index );
struct Card *card_draw(struct CardList *cardlist );

void print_cards(const char *player, struct CardList *hand , int hide_second );

int calculate_hand_value(struct CardList *hand );

#endif /* CARD_H */
