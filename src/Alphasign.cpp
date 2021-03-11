#include "Alphasign.h"

Allocation::Allocation(char label, FileType fileType, Lock lock, uint16_t size, const char *startTime, const char *stopTime)
{
  this->label = label;
  this->fileType = fileType;
  this->lock = (fileType == FileType::STRING_FILE) ? Lock::LOCKED() : lock;
  this->size = size;
  strncpy(this->startTime, startTime, 2);
  this->stopTime[2] = '\0';
  strncpy(this->stopTime, stopTime, 2);
  this->stopTime[2] = '\0';
}

void Alphasign::writeText(const char* message, char label)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_TEXT));
  write(label);
  write(message);
  endPacket();
}

void Alphasign::writeText(const char* message, char label, DisplayPosition position, DisplayMode mode)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_TEXT));
  write(label);
  write(ESC);
  write(static_cast<char>(position));
  if ((static_cast<char>(mode)) < 'a') write('n');
  write(static_cast<char>(mode));
  write(message);
  endPacket();
}

void Alphasign::writeString(const char* message, char label)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_STRING));
  write(label);
  write(message);
  endPacket();
}

void Alphasign::clearMemory(void)
{
  writeSpecial('$');
}

void Alphasign::softReset(void)
{
  writeSpecial(',');
}

void Alphasign::setTimeFormat(TimeFormat format)
{
  writeSpecial('\'', format.getCode());
}

void Alphasign::setTimeOfDay(const char *buffer)
{
  writeSpecial(' ', buffer, 4);
}

void Alphasign::tone(uint8_t frequency, uint8_t duration, uint8_t count)
{
  if (frequency > 254) frequency = 254;
  if (duration < 1) duration = 1;
  else if (duration > 15) duration = 15;
  if (count > 15) count = 15;
  char buffer[5];
  sprintf(buffer, "%02X%X%X", frequency, duration, count);
  writeSpecial('(', buffer, 5);
}

void Alphasign::allocate(const Allocation* *allocations, size_t size)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_SPECIAL));
  write('$');
  for (int i = 0; i < size; i++ )
  {
    write(allocations[i]->label);
    write(static_cast<char>(allocations[i]->fileType));
    write(allocations[i]->lock.getCode());
    char buffer[5];
    sprintf(buffer, "%04.4X", allocations[i]->size);
    write(buffer, 4);
    write(allocations[i]->startTime, 2);
    write(allocations[i]->stopTime, 2);
  }
  endPacket();
}

void Alphasign::writeSpecial(char code)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_SPECIAL));
  write(code);
  endPacket();
}

void Alphasign::writeSpecial(char code, char option)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_SPECIAL));
  write(code);
  write(option);
  endPacket();
}

void Alphasign::writeSpecial(char code, const char* option, size_t size)
{
  startPacket();
  write(static_cast<char>(CommandCode::WRITE_SPECIAL));
  write(code);
  write(option, size);
  endPacket();
}

void Alphasign::startPacket(void)
{
  write("\0\0\0\0\0\0\0\0\0\0", 10);
  write(SOH);
  write(static_cast<char>(_signType));
  write(_address);
  write(STX);
}

void Alphasign::endPacket(void)
{
  write(EOT);
}

size_t Alphasign::write(uint8_t b)
{
  if (_serial == NULL) return 0;

  if (b >= 0x20) return _serial->write(b);
  
  if (_transmissionFormat == TransmissionFormat::TWO_BYTE)
  {
    if (_serial->write(']'))
    {
      if (_serial->write(b + 0x20)) return 2;
      else return 1;
    }
    else return 0;
  }
  else if (_transmissionFormat == TransmissionFormat::THREE_BYTE)
  {
    if (_serial->write('_'))
    {
      if (_serial->write((b >> 4) + 0x30))
      {
        if (_serial->write((b & 0xf) + 0x30)) return 3;
        else return 2;
      }
      return 1;
    }
    else return 0;
  }
  else return _serial->write(b);
}

size_t Alphasign::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size-- > 0)
  {
    if (write(*buffer++)) n++;
    else break;
  }
  return n;
}


