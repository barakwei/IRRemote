/*
 * IRRemote for Particle Photon
 * Version 0.2
 * Moved to implementation based on AnalysIR - 
 * https://www.analysir.com/blog/2015/09/01/simple-infrared-pwm-on-arduino-part-3-hex-ir-signals/
 * by Barak Weiss (2016)
 * Ported to Photon by Mateusz Świetlicki (2015)
 * API Based on IRremote by Ken Shirriff
 */

#include "application.h"
#include "IRremote.h"

IRsend::IRsend(int irPin) : _irPin(irPin) {};

void IRsend::sendRaw(unsigned int buf[], int len, int hz)
{
    enableIROut(hz);
    _totalSignalTime = micros();
    for (int i = 0; i < len; i++) {
      if (i & 1) {
        space(buf[i]);
      } 
      else {
        mark(buf[i]);
      }
    }
    space(0); // Just to be sure
}

void IRsend::mark(int time) {
    _totalSignalTime += time;
    unsigned long startTime = micros();
    long duration = _totalSignalTime - startTime;
    
    // Sends an IR mark (frequency burst output) for the specified number of microseconds.
    while ((micros() - startTime) < duration) { // just wait here until time is up
      digitalWrite(_irPin, HIGH); // this takes about 3 microseconds to happen
      delayMicroseconds(_burstWait);
      digitalWrite(_irPin, LOW); // this also takes about 3 microseconds
      delayMicroseconds(_burstWait);
    }
}

void IRsend::space(int time) {
    _totalSignalTime += time;
    unsigned long startTime = micros();
    long duration = _totalSignalTime - startTime;
  
    // Sends an IR space (no output) for the specified number of microseconds.
    digitalWrite(_irPin, LOW); // Takes about 3 microsecondes
    if (duration > 3) {
      delayMicroseconds(duration - 3);
    }
}

void IRsend::enableIROut(int khz) {
    // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
    // MAX frequency is 166khz.
    pinMode(_irPin, OUTPUT);
    digitalWrite(_irPin, LOW);
  
    // This is the time to wait with the IR LED on and off to make the frequency, in microseconds.
    // The - 3.0 at the end is because digitalWrite() takes about 3 microseconds. Info from:
    // https://github.com/eflynch/sparkcoreiremitter/blob/master/ir_emitter/ir_emitter.ino
    _burstWait = round(1.0 / khz * 1000.0 / 2.0 - 3.0);
}
