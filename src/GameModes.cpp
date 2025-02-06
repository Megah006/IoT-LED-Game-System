#include "GameModes.h"
#include "Globals.h"
#include "LEDUtils.h"

void LEDREACT(){  
  if(wins == 15){
    rounds += 1;
    if(rounds > HighestMode1Wins){HighestMode1Wins = rounds;}
    roundStart();
    wins = 0;
    strip.clear();
    strip.setPixelColor(randomLED, strip.Color(G, R, B));
    strip.show();
    reactionTimeLimit = calculateTimeLimit(rounds, reactionTimeLimit);
    startTime = millis();
    Serial.println(rounds);
  }
  if(buttonClicked == randomLED){
    srand(millis());
    strip.clear();
    randomLED = rand() % 5;
    strip.setPixelColor(randomLED, strip.Color(G, R, B));
    strip.show();
    buttonClicked = OutOfBoundsButton;
    wins += 1;
    startTime = millis();
  }
  if (millis() - startTime > reactionTimeLimit * 1000) {
    gamelose();
    rounds = 1;
    wins = 15;
    reactionTimeLimit = INITIAL_TIME_LIMIT;
    strip.clear();
    mode = 0;
    startTime = millis();
  }
}

void MEMORYGAME(){
  if(rounds == 1){
    roundWin();
  }
  srand(millis());
  if(rounds > 1){
    for(int i = 0; i < rounds - 1; i++){
      strip.clear();
      strip.show();
      delay(500);
      strip.setPixelColor(LEDSequence[i], strip.Color(G, R, B));
      strip.show();
      delay(500);
    }
  }
  LEDmemory = rand() % 5;
  strip.clear();
  strip.show();
  delay(500);
  strip.setPixelColor(LEDmemory, strip.Color(G, R, B));
  strip.show();
  delay(750);
  strip.clear();
  strip.show();
  LEDSequence[rounds-1] = LEDmemory;
  AmountOfPlayerGuesses = 0;
  while (AmountOfPlayerGuesses < rounds) {
    buttonClicked = OutOfBoundsButton; // Reset buttonClicked
    while (buttonClicked == OutOfBoundsButton) {
      checkButtonPress(debounceDelayMODE2); // Wait for a button press
    }
    playerGuess[AmountOfPlayerGuesses] = buttonClicked; // Store player's guess
    strip.clear();
    strip.setPixelColor(buttonClicked, strip.Color(G, R, B));
    strip.show();
    AmountOfPlayerGuesses++; 
    if(!compareArrays(LEDSequence, playerGuess, AmountOfPlayerGuesses )){
      AmountOfPlayerGuesses = rounds;
      playerGuess[0] = 7;
    }
  }
  if(compareArrays(LEDSequence, playerGuess, rounds )){
    roundWin();
    rounds++;
  }
  else{
    if(rounds > HighestMode2Wins){HighestMode2Wins = rounds;}
    gamelose();
    for(int i = 0; i < rounds; i++){
      strip.clear();
      strip.show();
      delay(500);
      strip.setPixelColor(LEDSequence[i], strip.Color(0, 255, 0));
      strip.show();
      delay(500);
    }
    // reset the memory so it can be used again
    memset(LEDSequence, 0, sizeof(LEDSequence));
    memset(playerGuess, 0, sizeof(playerGuess));
    strip.clear();
    rounds = 1;
    mode = 0;
    startTime = millis();
  }
}

void ReactANDMemoryGame(){
  if(rounds == 1){
    roundWin();
    reactionTimeLimit = 20; // This represents the time the player has to compelete the round
  }
  if(rounds <= 10){
    ReactMemGameLEDs = 5;
  }
  else if(rounds <= 20){
    ReactMemGameLEDs = 7;
  }
  else{
    ReactMemGameLEDs = 10;
  }
  for(int i = 0; i < ReactMemGameLEDs; i++){
    LEDmemory = rand() % 5;
    LEDSequence[i] = LEDmemory;
  }
  for(int i = 0; i < ReactMemGameLEDs; i++){
    strip.clear();
    strip.show();
    delay(400);
    strip.setPixelColor(LEDSequence[i], strip.Color(G, R, B));
    strip.show();
    delay(400);
  }
  strip.clear();
  strip.show();
  AmountOfPlayerGuesses = 0;
  startTime = millis();
  while(AmountOfPlayerGuesses < ReactMemGameLEDs) {
    buttonClicked = OutOfBoundsButton; // Reset buttonClicked
    while (buttonClicked == OutOfBoundsButton) {
      checkButtonPress(debounceDelayMODE2); // Wait for a button press
      if(millis() - startTime > reactionTimeLimit * 1000){
        buttonClicked = 7;
        AmountOfPlayerGuesses = ReactMemGameLEDs;
        playerGuess[0] = 7;
      }
    }
    playerGuess[AmountOfPlayerGuesses] = buttonClicked; // Store player's guess
    strip.clear();
    strip.setPixelColor(buttonClicked, strip.Color(G, R, B));
    strip.show();
    AmountOfPlayerGuesses++; 
    if(!compareArrays(LEDSequence, playerGuess, AmountOfPlayerGuesses)){
      AmountOfPlayerGuesses = ReactMemGameLEDs;
      playerGuess[0] = 7;
    }
  }
  if(compareArrays(LEDSequence, playerGuess, AmountOfPlayerGuesses)){
    roundWin();
    rounds++;
    reactionTimeLimit = calculateTimeLimit(rounds, reactionTimeLimit);
  }
  else{
    if(rounds > HighestMode4Wins){HighestMode4Wins = rounds;}
    gamelose();
    for(int i = 0; i < 5; i++){
      strip.clear();
      strip.show();
      delay(500);
      strip.setPixelColor(LEDSequence[i], strip.Color(0, 255, 0));
      strip.show();
      delay(500);
    }
    memset(LEDSequence, 0, sizeof(LEDSequence));
    memset(playerGuess, 0, sizeof(playerGuess));
    strip.clear();
    rounds = 1;
    mode = 0;
    reactionTimeLimit = INITIAL_TIME_LIMIT;
    startTime = millis();
  }
}

void WhackAMole(){
  if(rounds == 1){
    rounds = OutOfBoundsButton;
    roundStart();
    randomLED = rand() % 5;
    strip.clear();
    strip.setPixelColor(randomLED, strip.Color(G, R, B));
    strip.show();
    srand(millis());
    startTime = millis();
    wins = 0;
  }
  if(buttonClicked == randomLED){
    wins += 1;
    strip.clear();
    randomLED = rand() % 5;
    strip.setPixelColor(randomLED, strip.Color(G, R, B));
    strip.show();
    buttonClicked = OutOfBoundsButton;
    if(wins > HighestMode1Wins){HighestMode1Wins = wins;}
  }
  if(millis() - startTime > reactionTimeLimit * 1000){
    gamelose();
    rounds = 1;
    wins = 15;
    reactionTimeLimit = INITIAL_TIME_LIMIT;
    mode = 0;
    startTime = millis();
    
  }

}