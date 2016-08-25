/*
 * IRRemote for Particle Photon
 * Version 0.2
 * Moved to implementation based on AnalysIR - 
 * https://www.analysir.com/blog/2015/09/01/simple-infrared-pwm-on-arduino-part-3-hex-ir-signals/
 * by Barak Weiss (2016)
 * Ported to Photon by Mateusz Świetlicki (2015)
 * API Based on IRremote by Ken Shirriff
 */

#ifndef IRremote_h
#define IRremote_h

class IRsend
{
public:
    IRsend(int irPin);
    void sendRaw(unsigned int buf[], int len, int hz);

private:
    void enableIROut(int khz);
    void mark(int usec);
    void space(int usec);

    const int _irPin;
    int _burstWait;
    unsigned long _totalSignalTime;
};

#endif /* IRremote_h */
