#ifndef PUSHBTN_H
#define PUSHBTN_H

#define PUSHBTN_PIN 14

void init_pushbtn()
{
  pinMode(PUSHBTN_PIN, INPUT_PULLUP);
}

/**
 * @returns true if the button is currently pressed
 */
bool btn_is_pressed()
{
  // Inverted because of INPUT_PULLUP
  return !digitalRead(PUSHBTN_PIN);
}

#endif