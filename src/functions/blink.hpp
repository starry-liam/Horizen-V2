#ifndef BLINK_HPP
#define BLINK_HPP

#include <Arduino.h>


void led(int del, int amt) {
    int j = 0;
    while (j != amt) {
      digitalWrite(LED, HIGH);
      delay(del);
      digitalWrite(LED, LOW);
      delay(del);
      j += 1;
    }
}

#endif