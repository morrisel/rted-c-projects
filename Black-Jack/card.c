#include <stdio.h>
#include "card.h"


void init_cardlist(struct CardList *cardlist ) 
{
	cardlist->head = NULL;  /* Initialize the head pointer to NULL */
	cardlist->len = 0;      /* Initialize the length to 0 */
}

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

struct Card *card_new_int(int rank , int suit )
{
	struct Card *new_card = malloc(sizeof(struct Card));
	if (new_card == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for a new card\n");
		exit(EXIT_FAILURE);
	}
	new_card->data = (unsigned char)(((unsigned char)suit << 4) | ((unsigned char)rank & 0xF));
	new_card->next = NULL;
	return new_card;
}

void card_push(struct CardList *cardlist , struct Card *card )
{
	if(cardlist->head == NULL)
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

void fill_deck(struct CardList *deck )
{
	char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', '1', '0', 'J', 'Q', 'K', 'A'};
	char suits[] = {'H', 'D', 'C', 'S'};
	int i = 0;
	int j = 0;
	for (i = 0; i < 13; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			struct Card *new_card;

			if (ranks[i] >= '2' && ranks[i] <= '9')
			{
				new_card = card_new_char((unsigned char)ranks[i], (unsigned char)suits[j]);
			}
			else
			{
				new_card = card_new_char(10, (unsigned char)suits[j]);
			}

			card_push(deck, new_card);
		}
	}
}

void clear_cardlist(struct CardList *cardlist) 
{
	struct Card *current_card =  cardlist->head;
	struct Card *next_card                     ;
	while (current_card != NULL)
	{
		next_card = current_card->next;
		free(current_card);
		current_card = next_card;
	}
	cardlist->head = NULL;
	cardlist->len = 0;
}

int get_rank(struct Card *card) 
{
	unsigned char data = card->data;
	int rank = (data >> 4) & 0x0F;
	return rank;    
}

struct Card *card_remove_at( struct CardList  *cardlist , 
                             size_t           index )
{
	size_t i;
	if (cardlist->head == NULL || index >= cardlist->len)
	{
		return NULL;
	}
	if (index == 0)
	{
		struct Card *removed_card = cardlist->head;
		cardlist->head     = cardlist->head->next; 
		removed_card->next = NULL;                 
		cardlist->len--;                           
		return removed_card;                       
	}
	struct Card *prev_card = cardlist->head;
	for (i=0; i < index; i++)
	{
		prev_card = prev_card->next;
	}
	if (prev_card->next == NULL)
	{
		return NULL;   
	}
	struct Card *removed_card = prev_card->next;       
	prev_card->next =           prev_card->next->next; 
	removed_card->next =        NULL;                  
	cardlist->len--;                                   
	return removed_card;                               
}

struct Card *card_draw(struct CardList *cardlist) 
{
	if (cardlist->len == 0 || cardlist->head == NULL)
	{
		return NULL;
	}
	struct Card *drawn_card = cardlist->head;
	cardlist->head = drawn_card->next;
	cardlist->len--;
	drawn_card->next = NULL;
	return drawn_card;
}

void print_cards(const char *player , struct CardList *hand , int hide_second) 
{
	printf("%s: ", player);   
	struct Card *current_card = hand->head;    
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

int calculate_hand_value(struct CardList *hand __attribute__((unused)))
{
	struct Card *current_card = hand->head;
	int total_value           =          0;
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
