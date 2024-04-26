/** card.c                                                                    *
 *  -------                                                                   *
 *                                                                            *
 *  - This file implements functions for managing a deck of cards.            *
 *                                                                            *
 *  - It includes functions to initialize, create, manipulate, and print      *
 *    card lists.                                                             *
 *                                                                            *
 * -------------------------------------------------------------------------- */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "card.h"

/* Initializes random seed based on size of time_t */
void initialize_random_seed()
{
	switch (sizeof(time_t))
	{
		case 2: /* time_t 16 bit */
		case 4: /* time_t 32 bit */
			srand((unsigned int)time(NULL));
			break;
		case 8: /* time_t 64 bit */
			srand((unsigned int)(time(NULL) & 0xFFFFFFFF)); /* takes lowest 32 bits of time */
			break;
		default:
			srand((unsigned int)time(NULL));
			break;
	}
}

/* Initializes card list */
void init_cardlist(struct CardList *cardlist ) 
{
	if (cardlist == NULL)
	{
		fprintf(stderr, "Invalid card list\n");
		exit(EXIT_FAILURE);
	}
	cardlist->head = NULL;  /* Initialize the head pointer to NULL */
	cardlist->len = 0;      /* Initialize the length to 0 */
}

/* Creates a new card with char rank and suit */
struct Card *card_new_char(unsigned char rank , unsigned char suit )
{
	struct Card *new_card = malloc(sizeof(struct Card));
	if (new_card == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for a new card\n");
		exit(EXIT_FAILURE);
	}
	new_card->data = (unsigned char)((((unsigned char)suit & 0xF) << 4) | ((unsigned char)rank & 0xF));
	new_card->next = NULL;
	return new_card;
}

/* Creates a new card with int rank and suit */
struct Card *card_new_int(int rank , int suit )
{
	struct Card *new_card = malloc(sizeof(struct Card));
	if (new_card == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for a new card\n");
		exit(EXIT_FAILURE);
	}
	new_card->data = (unsigned char)((((unsigned char)suit & 0xF) << 4) | ((unsigned char)rank & 0xF));
	new_card->next = NULL;
	return new_card;
}

/* Pushes a card onto the card list */
void card_push(struct CardList *cardlist , struct Card *card )
{
	if (cardlist == NULL)
	{
		fprintf(stderr, "Invalid card list\n");
		exit(EXIT_FAILURE);
	}
	if (cardlist->head == NULL)
	{
		cardlist->head = card;
	}
	else
	{
		struct Card *current = cardlist->head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = card;
	}
	cardlist->len++;
}

/* Fills the deck with cards */
void fill_deck(struct CardList *deck )
{
	char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', '1', '0', 'J', 'Q', 'K', 'A'};
	char suits[] = {'H', 'D', 'C', 'S'};
	int i = 0;
	int j = 0;
	if (deck == NULL)
	{
		fprintf(stderr, "Invalid deck\n");
		exit(EXIT_FAILURE);
	}
	initialize_random_seed();
	for (i = 0; i < 13; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			struct Card *new_card;

			/* if (ranks[i] >= '2' && ranks[i] <= '9') */
			/* If rank is between '2' and '9', convert to integer */
			if (ranks[i] >= '1' && ranks[i] <= '9')
			{
				new_card = card_new_char((unsigned char)ranks[i], (unsigned char)suits[j]);
			}
			else
			{
				/* For '10', 'J', 'Q', 'K', 'A', use specific values */
				new_card = card_new_char(10, (unsigned char)suits[j]);
			}
			card_push(deck, new_card);
		}
	}
}

/* Clears the card list */
void clear_cardlist(struct CardList *cardlist) 
{
	struct Card *current_card =  cardlist->head;
	struct Card *next_card                     ;
	if (cardlist == NULL)
	{
		fprintf(stderr, "Invalid card list\n");
		exit(EXIT_FAILURE);
	}
	while (current_card != NULL)
	{
		next_card = current_card->next;
		free(current_card);
		current_card = next_card;
	}
	cardlist->head = NULL;
	cardlist->len = 0;
}

/* Removes a card at given index from the card list */
int get_rank(struct Card *card) 
{
	unsigned char data = card->data;
	int rank = (data >> 4) & 0x0F;
	if (card == NULL)
	{
		fprintf(stderr, "Invalid card\n");
		return -1;
	}
	return rank;    
}

/* Removes a card at given index from the card list */
struct Card *card_remove_at( struct CardList  *cardlist , 
		size_t           index )
{
	size_t i;
	struct Card *prev_card = cardlist->head;
	struct Card *removed_card_local;       
	if (cardlist == NULL || cardlist->head == NULL || index >= cardlist->len)
	{
		fprintf(stderr, "Invalid card list or index\n");
		exit(EXIT_FAILURE);
	}
	if (index == 0)
	{
		struct Card *removed_card = cardlist->head;
		cardlist->head     = cardlist->head->next; 
		removed_card->next = NULL;                 
		cardlist->len--;                           
		return removed_card;                       
	}
	for (i=0; i < index; i++)
	{
		prev_card = prev_card->next;
	}
	if (prev_card->next == NULL)
	{
		fprintf(stderr, "Invalid index\n");
		exit(EXIT_FAILURE);
	}
	removed_card_local = prev_card->next;       
	prev_card->next =           prev_card->next->next; 
	removed_card_local->next =        NULL;                  
	cardlist->len--;                                   
	return removed_card_local;                               
}

/* Draws a card from the card list */
struct Card *card_draw(struct CardList *cardlist) 
{
	struct Card *drawn_card = cardlist->head;
	if (cardlist == NULL || cardlist->len == 0 || cardlist->head == NULL)
	{
		fprintf(stderr, "Invalid card list or empty deck\n");
		exit(EXIT_FAILURE);
	}
	cardlist->head = drawn_card->next;
	cardlist->len--;
	drawn_card->next = NULL;
	return drawn_card;
}

/* Prints cards in a hand */
void print_cards(const char *player , struct CardList *hand , int hide_second) 
{
	struct Card *current_card = hand->head;    
	if (player == NULL || hand == NULL)
	{
		fprintf(stderr, "Invalid player or hand\n");
		exit(EXIT_FAILURE);
	}
	printf("%s: ", player);   
	while (current_card != NULL)
	{
		if (hide_second && current_card == hand->head->next)
		{
			printf("?? ");
		}
		else
		{
			printf("%c%c ", (current_card->data >> 4) + '0', (current_card->data & 0xF) + '0');
		}
		current_card = current_card->next;   
	}
	puts("");
}

/* Calculates the value of a hand */
int calculate_hand_value(struct CardList *hand ) 
{
	struct Card *current_card = hand->head;
	int total_value           =          0;
	if (hand == NULL || hand->head == NULL)
	{
		fprintf(stderr, "Invalid hand\n");
		exit(EXIT_FAILURE);
	}
	while (current_card != NULL)
	{
		int rank_value;
		switch (current_card->data & 0xF)
		{
			case 1:     
				rank_value = total_value + 11 <= 21 ? 11 : 1;
				break;
			case 10:    
			case 11:
			case 12:
				rank_value = 10;
				break;
			default:    
				rank_value = (current_card->data & 0xF);
				break;
		}
		total_value += rank_value;            
		current_card = current_card->next;    
	}
	return total_value;    
}
