#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "card.h"

struct GameStateAccessor
{
	int cash;
	int pot;

	void (*set_cash)(struct GameStateAccessor *accessor, int value);
	void (*set_pot)(struct GameStateAccessor *accessor, int value);
};

struct GameState
{
	struct CardList deck;
	struct CardList dealer_hand;
	struct CardList player_hand;

	struct GameStateAccessor cash;
	struct GameStateAccessor pot;
};


void set_cash(struct GameState *state, int cash);
void set_pot(struct GameState *state, int pot);

void print_game_state(struct GameState *state); 
void betting_phase(struct GameState *state );
void initial_deal_phase(struct GameState *state );
void blackjack_check_phase(struct GameState *state );
void hit_or_stand_phase(struct GameState *state );

void dealer_draw_phase(struct GameState *state );
void reset_cards_phase(struct GameState *state );

#endif /* GAMESTATE_H */

