#include <stdio.h>
#include <string.h>
#include "gamestate.h"
#include "card.h"


void set_cash(struct GameState *state, int cash)
{
	state->cash.set_cash(&state->cash, cash);
}

void set_pot(struct GameState *state, int pot)
{
	state->pot.set_pot(&state->pot, pot);
}

void print_game_state(struct GameState *state )
{
	printf("Dealer's hand:\n");
	print_cards("dealer", &state->dealer_hand, 1); 
	printf("\nPlayer's hand:\n");
	print_cards("player", &state->player_hand, 0); 
	printf("\nCash: %d\n", state->cash.cash);
	printf("Pot: %d\n", state->pot.pot);
}

void betting_phase(struct GameState *state )
{
	printf("Current cash: %d\n", state->cash.cash);
	printf("Current pot: %d\n", state->pot.pot);
	int bet;
	printf("Enter your bet (must be multiples of 10): ");
	scanf("%d", &bet);
	set_pot(state, state->pot.pot + bet);
	set_cash(state, state->cash.cash - bet);
}

void initial_deal_phase(struct GameState *state )
{
	card_push(&state->player_hand, card_draw(&state->deck));
	card_push(&state->player_hand, card_draw(&state->deck));
	card_push(&state->dealer_hand, card_draw(&state->deck));
	card_push(&state->dealer_hand, card_draw(&state->deck));
}

void blackjack_check_phase(struct GameState *state )
{
	int player_value = calculate_hand_value(&state->player_hand);
	if (player_value == 21)
	{
		printf("Blackjack! You win!\n");
		set_cash(state, state->cash.cash + state->pot.pot + (state->pot.pot / 2)); 
		set_pot(state, 0);    
		reset_cards_phase(state);
	}
}

void hit_or_stand_phase(struct GameState *state )
{
	char choice[10];
	while (1)
	{
		printf("Do you want to hit or stand? (hit/stand): ");
		scanf("%s", choice);
		if (strcmp(choice, "hit") == 0)
		{
			card_push(&state->player_hand, card_draw(&state->deck));
			int player_value = calculate_hand_value(&state->player_hand);
			if (player_value > 21)
			{
				printf("Bust! You lose!\n");
				set_pot(state, 0);    
				reset_cards_phase(state);
				break;
			}
		}
		else if (strcmp(choice, "stand") == 0)
		{
			dealer_draw_phase(state);    
			break;
		}
		else
		{
			printf("Invalid choice. Please enter 'hit' or 'stand'.\n");
		}
	}
}

void dealer_draw_phase(struct GameState *state )
{
	int dealer_value = calculate_hand_value(&state->dealer_hand);
	while (dealer_value < 17)
	{
		card_push(&state->dealer_hand, card_draw(&state->deck));
		dealer_value = calculate_hand_value(&state->dealer_hand);
	}
}

void reset_cards_phase(struct GameState *state )
{
	init_cardlist(&state->deck);
	clear_cardlist(&state->player_hand);
	clear_cardlist(&state->dealer_hand);
}

