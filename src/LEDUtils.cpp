#include "Globals.h"
#include "LEDUtils.h"

int setRGB(String command) {
    int r, g, b;
    if (sscanf(command, "%d,%d,%d", &r, &g, &b) != 3) {
        return -1; // Return error if parsing fails
    }
    R = r;
    G = g;
    B = b;
    return 1;
}

void randomizeColors(){
  G = rand() % 256;
  R = rand() % 256;
  B = rand() % 256;
}

void roundStart(){
  srand(millis());
  randomizeColors();
  for(int i = 0; i <= 4; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(G, R, B));
    strip.show();
    delay(120);
  }
}

void allLEDS(int G, int R, int B) { 
  for (int i = 0; i <= 4; i++) {
    strip.setPixelColor(i, strip.Color(G, R, B));
  }
}

void gamelose(){ 
  for (int i = 0; i <= 4; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(120);
  }
  for (int i = 4; i >= 0; i--) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(120);
  }
  for (int i = 0; i <= 4; i++) { // Repeatedly sets all the LED's Red and Cyan 
    strip.clear();
    allLEDS(0,255,0); //Sets all LEDS to red
    strip.show();
    delay(120);
    strip.clear();
    allLEDS(170,0,170); // Sets all LEDS to cyan
    strip.show();
    delay(120);

  }
}

float calculateTimeLimit(int rounds, float baseTime) {
  if(baseTime <= 0.25){
    return baseTime;
  }
  if (rounds <= 10) {
    // Decrease by 10% per round up to round 10
    return baseTime * 0.8;
  }
  else if (rounds <= 25) {
    // Decrease by 5% per round from round 11 to 25
    return baseTime * 0.85;
  }
  else {
    // Decrease by 2% per round from round 26 onward
    return baseTime * 0.95;
  }
}

void roundWin(){
  for (int i = 0; i <= 4; i++) {
    strip.clear();
    allLEDS(255,0,0);
    strip.show();
    delay(120);
    strip.clear();
    allLEDS(170,0,170);
    strip.show();
    delay(120);
  }
}

bool compareArrays(int LEDSequence[], int playerGuess[], int size) { 
  for (int i = 0; i < size; i++) {
    if (LEDSequence[i] != playerGuess[i]) {
      return false; 
    }
  }
  return true;
}

void checkButtonPress(unsigned long debounceDelay) {
  if (millis() - lastDebounceTime > debounceDelay) {
    for (int i = 0; i < 5; i++) { // Loop through the buttons
      if (digitalRead(buttonPins[i]) == HIGH) { 
        buttonClicked = i;
        lastDebounceTime = millis();
      }
    }
  }
}