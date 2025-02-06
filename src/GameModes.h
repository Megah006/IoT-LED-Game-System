#ifndef GAME_MODES_H
#define GAME_MODES_H

// The LEDREACT function is a game mode where one of the 5 LEDs are turned on by random,
// and the user has to press the corrosiponding button in time.
// If the user doesn't click the button in time, they lose and the gamelose function plays, 
// the time decreases every round using the calculateTimeLimit function
void LEDREACT();

// This game mode is a memory game, The goal is to memorize a sequence of random LEDs, 
// with the number of LEDs in the sequence increasing with each round. 
// Each time the player correctly repeats the sequence, 
// they move on to the next round, where the sequence stays the same, but one additional random LED is added to the end.
void MEMORYGAME();

// This game mode combines the reaction game and the memory game.
// This works by showing a sequence of LED's, then the player has to click the corresponding buttons in time
// The diffculty increases, by reducing reaction time every round as well as increaing the led sequence every 10 rounds (up to thirty).
void ReactANDMemoryGame();

// This game mode(Whack A Mole) is simliar to the LEDREACT game mode, execpt there is one hard time limit and the goal
// is to hit as many buttons as you can in the alloted time (25 seconds).
void WhackAMole();

#endif // GAME_MODES_H