#include "Arduino.h"

void setup() {
    pinMode(PB8, OUTPUT);
    return;
}

void loop() {
    digitalWrite(PB8, HIGH);
    delay(1000);
    digitalWrite(PB8, LOW);
    delay(1000);
    return;
}

