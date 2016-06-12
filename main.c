#include "main.h"
#include "system_config.h"
#include "binary_display.h"
#include "numeric_display.h"
#include <libpic30.h>

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
 * Hauptfunktion
 */
int main()
{
  _initInternal();
  _initPins();
  
  while (1)
  { 
    _doMultiplexingLoop();
  }
  
  return 0;
}
