#ifndef MAIN_H
#define MAIN_H

// Internal Oscillator auf 8MHZ setzen
#define _XTAL_FREQ  (8000000)
#define FOSC        (_XTAL_FREQ)
#define FCY         (_XTAL_FREQ / 2)

// DEBUG-LED festlegen
#define LDEBUG      LATAbits.LATA0

// Ground-Pins
#define GND_BIN     LATBbits.LATB15  //Ground-Pin für die Binär-Anzeige
#define GND_NUM1    LATBbits.LATB11
#define GND_NUM2    LATBbits.LATB13
#define GND_NUM3    LATBbits.LATB12
#define GND_NUM4    LATBbits.LATB14

// Dauer in us die zwischen den Zyklen gewartet wird
#define FREQ_SLEEP  500

#include <xc.h> 

#endif