#ifndef LED_UTILS_H
#define LED_UTILS_H

#include <String.h>

// This is used to change the LED colors for diffrent game modes, 
// they can be changed through the provided LED_Changer HTML.
int setRGB(String command); 

// This randomizes the colors of the LEDs
void randomizeColors();

// Used to represent the start of a new round for fast game modes such as LEDREACT
void roundStart();

// This is used to set all of the LEDs to one color
void allLEDS(int G, int R, int B);

// This is used to indicate a game where the user loses
void gamelose();

// Used to represent when the player wins a round in the Memory game mode or the ReactAndMemory game mode
void roundWin();

// Used to calculate Time Limits for each game mode(if needed)
float calculateTimeLimit(int rounds, float baseTime);

// Compares two arrays to check whether they are the same or not, and returns True or False
bool compareArrays(int LEDSequence[], int playerGuess[], int size);

void checkButtonPress(unsigned long debounceDelay);
#endif