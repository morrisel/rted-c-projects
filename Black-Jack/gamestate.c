/** gamestate.c                                                               *
 *  -----------                                                               *
 *                                                                            *
 *  - This file implements functions for managing the game state in           *
 *    a Blackjack game.                                                       *
 *                                                                            *
 *  - It includes functions to initialize, reset, deal initial cards,         *
 *    update scores, determine winners, and clean up the game state.          *
 *                                                                            *
 * -------------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include "gamestate.h"
#include "card.h"

/* Sets the cash amount in the game state */
void set_cash(struct GameState *state, int cash)
{
	/* state->cash.set_cash(&state->cash, cash); */
	state->cash.cash = cash;
}

/* Sets the pot amount in the game state */
void set_pot(struct GameState *state, int pot)
{
	/* state->pot.set_pot(&state->pot, pot); */
	state->pot.pot = pot;
}

/* Prints the current game state */
void print_game_state(struct GameState *state )
{
	printf("Dealer's hand:\n");
	print_cards("dealer", &state->dealer_hand, 1); 
	printf("\nPlayer's hand:\n");
	print_cards("player", &state->player_hand, 0); 
	printf("\nCash: %d\n", state->cash.cash);
	printf("Pot: %d\n", state->pot.pot);
}

/* Executes the betting phase */
void betting_phase(struct GameState *state )
{
	int bet;
	printf("Current cash: %d\n", state->cash.cash);
	printf("Current pot: %d\n", state->pot.pot);
	if (state->pot.pot == 0 && state->cash.cash < 10)
	{
		printf("You are out of cash! Game Over.\n");
		exit(EXIT_SUCCESS);
	}
	printf("Enter your bet (must be multiples of 10): ");
	scanf("%d", &bet);
	if (bet < 0 || bet % 10 != 0 || (bet == 0 && state->pot.pot == 0))
	{
		puts("Invalid bet! Please enter a valid bet.");
		betting_phase(state);
	}
	else if (bet > state->cash.cash)
	{
		puts("You don't have enough cash for this bet!");
		betting_phase(state);
	}
	else
	{
		set_pot(state, state->pot.pot + bet);
		set_cash(state, state->cash.cash - bet);
	}
}

/* Executes the initial deal phase */
void initial_deal_phase(struct GameState *state )
{
	card_push(&state->player_hand, card_draw(&state->deck));
	card_push(&state->player_hand, card_draw(&state->deck));
	card_push(&state->dealer_hand, card_draw(&state->deck));
	card_push(&state->dealer_hand, card_draw(&state->deck));
}

/* Checks for a blackjack */
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

/* Executes the hit or stand phase */
void hit_or_stand_phase(struct GameState *state )
{
	char choice[10];
	while (1)
	{
		printf("Do you want to hit or stand? (hit/stand): ");
		scanf("%s", choice);
		if (strcmp(choice, "hit") == 0)
		{
			int player_value;
			card_push(&state->player_hand, card_draw(&state->deck));
			player_value = calculate_hand_value(&state->player_hand);
			printf("Player's hand value: %d\n", player_value);
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

/* Executes the dealer draw phase */
void dealer_draw_phase(struct GameState *state )
{
	int dealer_value = calculate_hand_value(&state->dealer_hand);
	while (dealer_value < 17)
	{
		card_push(&state->dealer_hand, card_draw(&state->deck));
		dealer_value = calculate_hand_value(&state->dealer_hand);
	}
}

/* Resets the cards for a new round */
void reset_cards_phase(struct GameState *state )
{
	init_cardlist(&state->deck);
	clear_cardlist(&state->player_hand);
	clear_cardlist(&state->dealer_hand);
	fill_deck(&state->deck);
}
