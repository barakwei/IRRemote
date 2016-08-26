# IRRemote for Particle Photon
This is an [IRremote](https://github.com/z3t0/Arduino-IRremote)-compatible library designed for use with Particle (Spark) Core or Photon.
The library supports sending only raw buffers.

### Usage:
```c++
#include "IRremote.h"

unsigned int rawCode[] = { 9000, 4500, 560, 1680 };

IRsend irsend(D3);

void loop() {
    int rawSize = sizeof(rawCode)/sizeof(unsigned int);
    irsend.sendRaw(rawCode, rawSize, 38);
}
```
