// This is a two player game
// It is played with 4 leds (on pins 4,5,6,7) and two switches (pins 8 and 9)
// The objective is to press the switch when the green led (pin 5) is lit
// Player 1 uses switch 1 and player switch 2
// A hit blinks the hit led again and the game speeds up
// until one of the players makes ten hits. The game restarts.
// Message on seroial monitor shows the player points at game end.

// Pin assignment

int switch1Pin = 8;  // switch for player 1
int switch2Pin = 9;  // switch for player 2

int led1Pin = 4;
int led2Pin = 5;    // this must be the green led
int led3Pin = 6;
int led4Pin = 7;

// Game parameters 
int gamePoints = 10;  // Points needed to win the game
int blinkSpeed = 25;

int startDelay = 500;  // Delay between LEDs at the start
int decrement = 50;    // Speed at which game speeds up
int threshold = 10;

int switch1;
int switch2;
int player1Points = 0;
int player2Points = 0;
int currentDelay;

void setup() {
  // put your setup code here, to run once:
  pinMode (switch1Pin, INPUT);
  pinMode (switch2Pin, INPUT);
  
  pinMode (led1Pin, OUTPUT);
  pinMode (led2Pin, OUTPUT);
  pinMode (led3Pin, OUTPUT);
  pinMode (led4Pin, OUTPUT);
  currentDelay = startDelay;
  resetGame ();
  Serial.begin (9600);
}
void blinkLed (int led) {
  for (int i = 1; i < 3; i++) {
    digitalWrite (led, HIGH);
    delay (blinkSpeed);
    digitalWrite (led, LOW);
    delay (blinkSpeed);
  }
}
void resetGame () {
  Serial.println("=====Starting new game====");
  Serial.print (player1Points);
  Serial.print ("\t");
  Serial.println (player2Points);
  
  currentDelay = 600;
  player1Points = 0;
  player2Points = 0;
  return;
}
void speedUp () {
  if (currentDelay > threshold) {
    currentDelay -= decrement;
  }
}
void checkSwitches () {
   switch1 = digitalRead (switch1Pin);
   switch2 = digitalRead (switch2Pin);
}
void loop() {
  // put your main code here, to run repeatedly:
  blinkLed (led1Pin);
  checkSwitches();
  if (switch1 or switch2) {
    blinkLed (led1Pin);
  }
  delay (currentDelay);
  blinkLed (led2Pin);
  checkSwitches();
  if (switch1 or switch2) {
    speedUp();
    blinkLed (led2Pin);
    if (switch1) {
      player1Points += 1;
    } 
    if (switch2) {
      player2Points += 1;
    }
    if ((player1Points == gamePoints) or (player2Points == gamePoints)) {
      resetGame();
    }
  }
  delay (currentDelay);
  blinkLed (led3Pin);
  checkSwitches();
  if (switch1 or switch2) {
    blinkLed (led3Pin);
  }
  delay (currentDelay);
  blinkLed (led4Pin);
  checkSwitches();
  if (switch1 or switch2) {
    blinkLed (led4Pin);
  }
  delay (currentDelay);
}
