#ifndef GLOBALS_H
#define GLOBALS_H

#include "Particle.h"
#include "neopixel.h"
#include <cstdlib>

// Constants
const int NUM_BUTTONS = 5; // number of buttons
const int NUM_LEDS = 5; // number of leds
const int Button5 = D7;
const int Button4 = D6;
const int Button3 = D5;
const int Button2 = D3; 
const int Button1 = D9;
const int OutOfBoundsButton = 6; // this is used when I want no input, such as in lobby mode, or every time the program is idling
const float INITIAL_TIME_LIMIT = 10;
const int buttonPins[] = {Button1, Button2, Button3, Button4, Button5};

// Debounce variables
extern long lastDebounceTime;
extern unsigned long debounceDelayMODE1; // used for less precise game modes
extern unsigned long debounceDelayMODE2; // used when it needs to be more precise

//Used for the LED colors
extern int G;
extern int R;
extern int B;

//Used for the different game modes
extern int mode;
extern float reactionTimeLimit;
extern int startTime; // used amount of time for each game mode
extern int LEDSequence[100]; // Used for the real guesses
extern int playerGuess[100]; // Used for the players guesses
extern int LEDmemory;
extern int AmountOfPlayerGuesses;
extern int ReactMemGameLEDs;
extern int wins; // Used to calculate each individual win, may be reset every round
extern int rounds; // Used to represent the current round the player is in, only reset, when the player loses 
extern int randomLED; // Used to represent a random LED that will be turned on
extern int buttonClicked; // Used to show the button the player pressed 

// HTML variables for high scores
extern int HighestMode1Wins;
extern int HighestMode2Wins;
extern int HighestMode4Wins;
extern int HighestMode5Wins;

// NeoPixel setup
#define PIXEL_PIN SPI 
extern int PIXEL_TYPE;
extern Adafruit_NeoPixel strip;

#endif 