/*
 * Copyright (c) 2021, Horst Eff
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license
 * found in the LICENSE file in the root directory of this
 * source tree.
 */

#ifndef Alphasign_h
#define Alphasign_h

#include "Arduino.h"

#include <inttypes.h>

#define SOH '\x01'
#define STX '\x02'
#define ETX '\x03'
#define EOT '\x04'
#define ESC '\x1b'

enum class SignType : char
{
  ALL_WITH_VISUAL_VERIFICATION     = '!',
  SERIAL_CLOCK                     = '"',
  ALPHA_VISION                     = '#',
  FULL_MATRIX_ALPHAVISION          = '$',
  CHARACTER_MATRIX_ALPHAVISION     = '%',
  LINE_MATRIX_ALPHAVISION          = '&',
  RESPONSE                         = '0',
  ONE_LINE                         = '1',
  TWO_LINE                         = '2',
  ALL_                             = '?',
  _430I                            = 'C',
  _440I                            = 'D',
  _460I                            = 'E',
  ALPHAECLIPSE_3600_DISPLAY_DRIVER = 'F',
  ALPHAECLIPSE_3600_TURBO_ADAPTER  = 'G',
  LIGHT_SENSOR                     = 'L',
  _790I                            = 'U',
  ALPHAECLIPSE_3600                = 'V',
  ALPHAECKIPSE_TIME_TEMP           = 'W',
  ALPHAPREMIERE_4000_9000          = 'X',
  ALL                              = 'Z',
  BETABRIGHT                       = '^',
  _4120C                           = 'a',
  _4160C                           = 'b',
  _4200C                           = 'c',
  _4240C                           = 'd',
  _215R                            = 'e',
  _215C                            = 'f',
  _4120R                           = 'g',
  _4160R                           = 'h',
  _4200R                           = 'i',
  _4240R                           = 'j',
  _300                             = 'k',
  _7000                            = 'l',
  MATRIX_SOLAR_96X16               = 'm',
  MATRIX_SOLAR_128X16              = 'n',
  MATRIX_SOLAR_160X16              = 'o',
  MATRIX_SOLAR_192X16              = 'p',
  PPS                              = 'q',
  DIRECTOR                         = 'r',
  _1005                            = 's',
  _4080C                           = 't',
  _210C_220C                       = 'u',
  ALPHAECLIPSE_3500                = 'v',
  ALPHAECLIPSE_1500_TIME_TEMP      = 'w',
  TEMPERATURE_PROBE                = 'y',
  ALL_WITH_26_MEMORY_FILES         = 'z'
};

enum class TransmissionFormat
{
  ONE_BYTE,
  TWO_BYTE,
  THREE_BYTE
};

enum class CommandCode : char
{
  WRITE_TEXT            = 'A',  // Write TEXT file (p18)
  READ_TEXT             = 'B',  // Read TEXT file (p19)
  WRITE_SPECIAL         = 'E',  // Write SPECIAL FUNCTION commands (p21)
  READ_SPECIAL          = 'F',  // Read SPECIAL FUNCTION commands (p29)
  WRITE_STRING          = 'G',  // Write STRING (p37)
  READ_STRING           = 'H',  // Read STRING (p38)
  WRITE_SMALL_DOTS      = 'I',  // Write SMALL DOTS PICTURE file (p39)
  READ_SMALL_DOTS       = 'J',  // Read SMALL DOTS PICTURE file (p41)
  WRITE_RGB_DOTS        = 'K',  // Write RGB DOTS PICTURE file (p44)
  READ_RGB_DOTS         = 'L',  // Read RGB DOTS PICTURE file (p46)
  WRITE_LARGE_DOTS      = 'M',  // Write LARGE DOTS PICTURE file (p42)
  READ_LARGE_DOTS       = 'N',  // Read LARGE DOTS PICTURE file (p43)
  WRITE_ALPHAVISION     = 'O',  // Write ALPHAVISION BULLETIN (p48)
  SET_TIMEOUT           = 'T'   // Set Timeout Message (p118) (Alpha 2.0/3.0)
};

enum class DisplayPosition : char
{
  MIDDLE_LINE = ' ',
  TOP_LINE    = '"',
  BOTTOM_LINE = '&',
  FILL        = '0',
  LEFT        = '1',
  RIGHT       = '2'
};

enum class DisplayMode : char
{
  // Normal display modes
  ROTATE            = 'a',
  HOLD              = 'b',
  FLASH             = 'c',
  ROLL_UP           = 'e',
  ROLL_DOWN         = 'f',
  ROLL_LEFT         = 'g',
  ROLL_RIGHT        = 'h',
  WIPE_UP           = 'i',
  WIPE_DOWN         = 'j',
  WIPE_LEFT         = 'k',
  WIPE_RIGHT        = 'l',
  SCROLL            = 'm',
  AUTOMODE          = 'o',
  ROLL_IN           = 'p',
  ROLL_OUT          = 'q',
  WIPE_IN           = 'r',
  WIPE_OUT          = 's',
  COMPRESSED_ROTATE = 't',
  EXPLODE           = 'u',
  CLOCK             = 'v',

  // Special modes
  TWINKLE           = '0',
  SPARKLE           = '1',
  SNOW              = '2',
  INTERLOCK         = '3',
  SWITCH            = '4',
  SLIDE             = '5',
  SPRAY             = '6',
  STARBURST         = '7',
  WELCOME           = '8',
  SLOT_MACHINE      = '9',
  NEWS_FLASH        = 'A',
  TRUMPET_ANIMATION = 'B',
  CYCLE_COLORS      = 'C',

  // Special graphics
  THANK_YOU         = 'S',
  NO_SMOKING        = 'U',
  DONT_DRINK_DRIVE  = 'V',
  RUNNING_ANIMAL    = 'W',
  FISH_ANIMATION    = 'W',
  FIREWORKS         = 'X',
  TURBO_CAR         = 'Y',
  BALLOON_ANIMATION = 'Y',
  CHERRY_BOMB       = 'Z'
};

//enum class TimeFormat : char
//{
//  AM_PM             = 'S',
//  _24_HOUR          = 'M'
//};

class CharCode
{
  public:
    char getCode(void) const { return code; }
  protected:
    CharCode(char code) { this->code = code; }
    CharCode(const CharCode &other) { this->code = other.code; }
  private:
    char code;
};

class TimeFormat : public CharCode
{
  public:
    static const TimeFormat AM_PM() { return TimeFormat('S'); }
    static const TimeFormat _24_HOUR() { return TimeFormat('M'); }
    TimeFormat(const TimeFormat &other) : CharCode(other) {}

  private:
    TimeFormat(char code) : CharCode(code) {}
};

enum class FileType : char
{
  TEXT_FILE         = 'A',
  STRING_FILE       = 'B',
  DOTS_PICTURE_FILE = 'D'
};

class Lock : public CharCode
{
  public:
    static const Lock UNLOCKED() { return Lock('U'); }
    static const Lock LOCKED() { return Lock('L'); }
    Lock(const Lock &other) : CharCode(other) {}

  private:
    Lock(char code) : CharCode(code) {}
};

class Allocation
{
  public:
    Allocation(char label, FileType fileType, Lock lock, uint16_t size, const char *startTime, const char *stopTime);
    char label;
    FileType fileType;
    Lock lock = Lock::LOCKED();
    uint16_t size;
    char startTime[3];
    char stopTime[3];
};


class Alphasign
{
  public:
    Alphasign(SignType signType = SignType::ALL, const char *address = "00") { _signType = signType; _address = address; _serial = NULL; _transmissionFormat = TransmissionFormat::ONE_BYTE; }
    void begin(Print &serial) { _serial = &serial; }
    void setTransmissionFormat(TransmissionFormat format) { _transmissionFormat = format; }
    TransmissionFormat getTransmissionFormat() { return _transmissionFormat; }
    void writeText(const char* message, char label);
    void writeText(const char* message, char label, DisplayPosition position, DisplayMode mode);
    void writeString(const char* message, char label);
    void clearMemory(void);
    void softReset(void);
    void setTimeFormat(TimeFormat format);
    void tone(uint8_t frequency, uint8_t duration, uint8_t count);
    void setTimeOfDay(const char *buffer);
    void allocate(const Allocation* *allocations, size_t size);

  private:
    SignType _signType;
    const char *_address;
    TransmissionFormat _transmissionFormat;
    Print* _serial;
    size_t write(uint8_t b);
    size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *buffer, size_t size) { return write((const uint8_t *)buffer, size); }
    size_t write(const char *str) { return write((const uint8_t *)str, strlen(str)); }
    void writeSpecial(char code);
    void writeSpecial(char code, char option);
    void writeSpecial(char code, const char* option, size_t size);
    void startPacket(void);
    void endPacket(void);
};

#endif  // Alphasign_h
