#include "main.h"
#include "system_config.h"
#include "binary_display.h"
#include "numeric_display.h"
#include <libpic30.h>

/**
 * Diese Funktion wird aufgerufen, wenn Timer1 auslöst
 */
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void);

/**
 * Initialisiert interne Variablen / Register
 * mit bestimmten Werten
 */
void _initInternal()
{
  //0-000-0-000, S.99, 000 - 8MHZ
  CLKDIV = 0b0000000000000000;
}

/**
 * Initialisiert den Zustand der Pins.
 * Schaltet ALLE Pins auf OUTPUT, resettet den Zustand dieser
 */
void _initPins()
{  
  // Alle IO-Ports auf digital schalten
  AD1PCFG = 0xFFFF;
  
  // TRISA und TRISB auf Output, da wir explizit die Inputs festlegen
  TRISA = 0x0000;
  TRISB = 0x0000;
  
  // Reset
  LATA = 0x0000;
  LATB = 0x0000;
}

/**
 * Führt die Anzeige-Loop aus, die nacheinander
 * alle nötigen Anzeigen durchgeht und diese "aktualisiert"
 */
void _doMultiplexingLoop()
{
  GND_BIN = 1;
  bdisplay_loop();
  __delay_ms(FREQ_SLEEP);
  GND_BIN = 0;
  
  GND_NUM1 = 1;
  ndisplay_loop(0);
  __delay_ms(FREQ_SLEEP);
  GND_NUM1 = 0;
  
  GND_NUM2 = 1;
  ndisplay_loop(1);
  __delay_ms(FREQ_SLEEP);
  GND_NUM2 = 0;
  
  GND_NUM3 = 1;
  ndisplay_loop(2);
  __delay_ms(FREQ_SLEEP);
  GND_NUM3 = 0;

  GND_NUM4 = 1;
  ndisplay_loop(3);
  __delay_ms(FREQ_SLEEP);
  GND_NUM4 = 0;
}

/**
 * Initialisiert den Timer
 */
void _initTimer()
{
  T1CON = 0;            //Vorherige Konfiguration löschen
  T1CONbits.TCKPS = 3;  //Timer1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256) -> 8MHz / 256 = 31.250kHz 
  PR1 = 0x3D09;         //31.250kHz / 15.625 (0x3D09) = 2 (schaltet bei 1Hz um -> 2Hz)
  IPC0bits.T1IP = 5;    //Priorität (max. 0xFFFF)
  T1CONbits.TON = 1;    //Timer einschalten
  IFS0bits.T1IF = 0;    //Interrupt-Flag zurücksetzen
  IEC0bits.T1IE = 1;    //Timer1 Interrupt einschalten
}

/**
 * Hauptfunktion
 */
int main()
{
  _initInternal();
  _initTimer();
  _initPins();
  
  while (1)
  { 
    _doMultiplexingLoop();
  }
  
  return 0;
}

/**
 * Interrupt-Routine für Timer1 (1Hz)
 */
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
  IFS0bits.T1IF = 0;
}