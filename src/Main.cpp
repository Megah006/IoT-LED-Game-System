#include "Particle.h"
#include "Globals.h"
#include "LEDUtils.h"
#include "GameModes.h"

void setup() {
  pinMode(Button1, INPUT_PULLDOWN);
  pinMode(Button2, INPUT_PULLDOWN);
  pinMode(Button3, INPUT_PULLDOWN);
  pinMode(Button4, INPUT_PULLDOWN);
  pinMode(Button5, INPUT_PULLDOWN);
  strip.begin();
  strip.show();
  // Below is used to send high scores to the HTML
  Particle.variable("most-MODE1-wins", HighestMode1Wins);
  Particle.variable("most-MODE2-wins", HighestMode2Wins);
  Particle.variable("most-MODE4-wins", HighestMode4Wins);
  Particle.variable("most-MODE5-wins", HighestMode5Wins);
  Particle.function("setRGB", setRGB);
  srand(millis());
  randomLED = rand() % NUM_LEDS;
  strip.setPixelColor(randomLED, strip.Color(0, 0, 255));
  strip.show();
}

void loop() {
  if(mode == 0){ // Mode 0 represents the lobby where the player can choose which game mode they'd like
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // Sets first LED green
    strip.setPixelColor(1, strip.Color(0, 170, 170)); // Sets second LED purple
    strip.setPixelColor(2, strip.Color(G, R, B)); // Sets thrid LED to current GRB settings
    strip.setPixelColor(3, strip.Color(0, 0, 200)); // Sets fourth LED blue
    strip.setPixelColor(4, strip.Color(0, 255, 0)); // Sets fifth LED red
    strip.show();
    if (millis() - lastDebounceTime > debounceDelayMODE2) {
      // Check each button with a loop
      for (int i = 0; i < NUM_BUTTONS; i++) {
        if (digitalRead(buttonPins[i]) == HIGH) {
          mode = i + 1;  // Set the mode based on button pressed
          lastDebounceTime = millis(); 
        }
      }
    }
  }
  if(mode == 1){ // Mode 1 starts the reaction game mode
    rounds = 0;
    LEDREACT();
  }
  while(mode == 2){ // Mode 2 starts the memory game mode
    MEMORYGAME();
  }
  if(mode == 3){ // Mode 3 randomizes the color of the LED's, this may not work for some game modes since they already randomize colors
    randomizeColors();
    mode = 0;
  }
  while(mode == 4){ // Mode 4 starts the react and memory game
    ReactANDMemoryGame();
  }
  if(mode == 5){ // Mode 5 starts Whack a Mole 
    wins = -1;
    reactionTimeLimit = 30;
    WhackAMole();

  }
  checkButtonPress(debounceDelayMODE1);
}
