/*
 * Copyright (c) 2021, Horst Eff
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license
 * found in the LICENSE file in the root directory of this
 * source tree.
 */

#include <Alphasign.h>

Alphasign sign;

// Clears and sets memory configuration
void allocate()
{
  Allocation aTextFile('A', FileType::TEXT_FILE, Lock::UNLOCKED(), 200, "FF", "FF");
  Allocation aStringFile('1', FileType::STRING_FILE, Lock::LOCKED(), 10, "00", "00");
  const Allocation* allocations[] = { &aTextFile, &aStringFile };
  sign.allocate(allocations, 2);
}

// Sends a text file containing signs time of day and the contents of string file labeled 'l'
void setText()
{
  sign.writeText("\x13 - \x10""1", 'A', DisplayPosition::MIDDLE_LINE, DisplayMode::HOLD);
}

// Updates the contents of string file labeled 'l'
void setString(char *s)
{
  sign.writeString(s, '1');
}

// Updates signs time of day
void setTime(char *time)
{
  sign.setTimeOfDay(time);
}

void setup() {
  Serial.begin(115200);
#ifndef ESP8266
  while (!Serial);
#endif

  Serial.println();
  Serial.println();
  Serial.println("Bootup");

#ifdef ESP8266
  // Second serial interface on ESP8266 is for sending only
  Serial1.begin(4800, SERIAL_8N1, SERIAL_TX_ONLY);
#else
  Serial1.begin(4800, SERIAL_8N1);
#endif
  delay(10);

  sign.begin(Serial1);
// change transmission format here if needed (default is ONE_BYTE)
//  sign.setTransmissionFormat(TransmissionFormat::THREE_BYTE);

  Serial.println("Device started");

  Serial.println();
  Serial.print("(a, x, tHHMM, s?????????)> ");
  Serial.flush();
  Serial.setTimeout(5000);
}

void loop() {
  if (Serial.available())
  {
    char buffer[100];
    size_t read = Serial.readBytesUntil('\r', buffer, 100);
    buffer[read] = 0;
    Serial.println();
    Serial.print("Read: ");
    Serial.println(buffer);

    if (read == 1)
    {
      if (buffer[0] == 'a')
      {
        allocate();
      }
      else if (buffer[0] == 'x')
      {
        setText();
      }
    }
    else if (read == 5 && buffer[0] == 't')
    {
      char time[5];
      strncpy(time, buffer + 1, 4);
      time[4] = 0;
      setTime(time);
    }
    else if (read > 1 && buffer[0] == 's' && read <= 10)
    {
      char s[10];
      strncpy(s, buffer + 1, read-1);
      s[read-1] = 0;
      setString(s);
    }

    Serial.println();
    Serial.print("(a, x, tHHMM, s?????????)> ");
    Serial.flush();
  }
}
