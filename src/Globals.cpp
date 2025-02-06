#include "Globals.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

//Used for Debounce logic
long lastDebounceTime = 0;
unsigned long debounceDelayMODE1 = 50;
unsigned long debounceDelayMODE2 = 250;

//Used for the LED colors
int G = 255;
int R = 255;
int B = 255;

//Used for the different game modes
int mode = 0;
float reactionTimeLimit = INITIAL_TIME_LIMIT;
int startTime = 0;
int LEDSequence[100] = {0};
int playerGuess[100] = {0};
int LEDmemory = 0;
int AmountOfPlayerGuesses = 0;
int ReactMemGameLEDs = 0;
int wins = 15;
int rounds = 1;
int randomLED = rand() % NUM_LEDS;
int buttonClicked = OutOfBoundsButton;

// Used for the HTML
int HighestMode1Wins = 0;
int HighestMode2Wins = 0;
int HighestMode4Wins = 0;
int HighestMode5Wins = 0;

// Used for all LED logic
int PIXEL_TYPE = WS2812;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE);