// these constants won't change:
const int analogPin1 = A0;   // the pin that the potentiometer is attached to
const int analogPin2 = A1;   // the pin that the potentiometer is attached to
const int ledCount1 = 9;    // the number of LEDs in the bar graph
const int ledCount2 = 5;    // the number of LEDs in the bar graph

int ledPins1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};   // an array of pin numbers to which LEDs are attached
int ledPins2[] = { 9, 10, 11,12, 13}; 

void setup() {
  // loop over the pin array and set them all to output:
  for (int thisLed1 = 0; thisLed1 < ledCount1; thisLed1++) {
    pinMode(ledPins1[thisLed1], OUTPUT);
  }
  for (int thisLed2 = 0; thisLed2 < ledCount2; thisLed2++) {
    pinMode(ledPins2[thisLed2], OUTPUT);
  }
}

void loop() {
  // read the potentiometer:
  int sensorReading1 = analogRead(analogPin1);
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel1 = map(sensorReading1, 0, 1023, 0, ledCount1);
  
  int sensorReading2 = analogRead(analogPin2);
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel2 = map(sensorReading2, 0, 1023, 0, ledCount2);

  // loop over the LED array:
    for (int thisLed1 = 0; thisLed1 < ledCount1; thisLed1++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed1 < ledLevel1) {
      digitalWrite(ledPins1[thisLed1], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins1[thisLed1], LOW);
      }
  }
    for (int thisLed2 = 0; thisLed2 < ledCount2; thisLed2++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed2 < ledLevel2) {
      digitalWrite(ledPins2[thisLed2], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins2[thisLed2], LOW);
      }
  }
  delay (50);
}
