# Arduino-Alphasign

This is an Arduino library to control AlphaSign matrix displays.

### Disclaimer
It is intended to use with different types of such displays, but as I only have one display for testing, it may or may not work with others.

I used it only with an ESP8266, so I can't guarantee that it works for other boards.

## Installing

To install the library you have to download the source. Click "Code" above and then "Download ZIP". After uncompressing, change the name of the resulting folder (it should contain this README.md file) to Alphasign and move it to your Arduino library folder.

## Usage

The library only implements a small facade to access AlphaSign matrix displays. To understand, how to work with such displays, you need a description of the AlphaSign Communications Protocol, which is freely downloadable (at time of this writing) from [Adaptive Displays](https://www.adaptivedisplays.com)

First include Alphasign.h.

```c
#include <Alphasign.h>
```

Then you have to create an Alphasign instance.

```c
Alphasign sign;
```

This will use the ALL sign type and address "00". Alternatively you can specify a sign type and an address in the constructor.

The library uses a Print stream for writing data to a sign. Usually this will be a serial interface. You have to initialise the serial interface according to the requirements of your actual display. Call the `begin` method of the Alphasign instance to connect it with the stream.

```c
  Serial1.begin(4800, SERIAL_8N1);
  sign.begin(Serial1);
```

If you want to use an ASCII printable transmission format (e.g. for debugging), use `setTransmissionFormat`.

```c
  sign.setTransmissionFormat(TransmissionFormat::THREE_BYTE);
```

Now your Alphasign instance is prepared to transfer data to the sign.

## License

This library is licensed under the BSD-style license found in the LICENSE file
