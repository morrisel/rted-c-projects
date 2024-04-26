# Black-Jack Game


### Description:
 
The Black-Jack project implements a console version of the blackjack game.
Written in C language following the Allman (code formatting) and Google (comment style) styles.
The player competes against the computer (dealer), placing bets and trying to get cards so that 
the sum of their values is as close to 21 as possible without exceeding it.


### Project Structure:

This C program simulates a game of Blackjack, allowing you to play against a dealer.

##### Features include -
   Standard Blackjack game mechanics (hitting, standing, dealer logic)
   Betting system to track cash balance
   Representation of cards and hands

##### The project consists of the following files -
   - `black-jack.c`: The main program file containing the main game loop.
   - `card.c` and `card.h`: Files implementing functions for working with cards and the deck.
   - `gamestate.c` and `gamestate.h`: Files containing functions for managing the game state.


### Compilation:

To compile the program, you'll need a C89-compatible (ANSI Standart) C compiler like GCC:
To compile the program, you can use the following commands:

#### Compilation with basic requirements flags:

```bash
gcc -std=c89 -pedantic -Wall -Wextra -Wconversion -Wno-main *.c -o out_black-jack 
```

#### Compilation with the extra flags and additional features:

##### compilation:
```bash
gcc -std=c89 -c -g -O0 -pedantic -Wall -Wextra -Wconversion -Wno-main -Wshadow *.c
```
##### linking:
```bash
gcc *.o -o out_black-jack -lm
```

#### Functionality:
	The program allows the player to interact with the blackjack game, including the following actions:
	- Placing a bet.
	- Dealing initial cards.
	- Checking for a blackjack.
	- Deciding whether to hit or stand.
	- Determining win or loss.


#### Code Style:
	- Allman Style indentation.
	- Google Style for comments.

#### References:
- Google Style: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- Indentation Style: &nbsp;[Indentation Style](https://en.wikipedia.org/wiki/Indentation_style)



---
#### Additional Information
	Complexity: Simple
	Time complexity: O(1)
	Memory complexity: O(1)

#### Comes in future version
---
	Adding support for calculating the sum of cards.
	Adding the ability to win or lose.
	Extending the game functionality.
