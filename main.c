#include "main.h"
#include "system_config.h"
#include "binary_display.h"
#include "numeric_display.h"
#include <libpic30.h>
#include "ds1820.h"

/**
 * Diese Variable stellt einen ReadCounter für den DS18S20 dar.
 * 0      = Startwert
 * BEGIN  = DS18S20 wird aufgefordert, die Temperatur zu "lesen"
 * READ   = DS18S20 wird aufgefordert, die Temperatur dem Controller zu senden
 */
unsigned int tempReadCounter = 0;
const unsigned int BEGIN = 2000;
const unsigned int READ = 2250;
float currentTempToShow = 0;

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
 * alle nötigen Anzeigen durchgeht und diese "aktualisiert".
 * Ebenso wird hier der Temperatursensor in einem mit BEGIN und READ festgelegten
 * Intervall abgefragt. Es wird ein "Flackern" der Anzeige so gut es geht vermieden,
 * indem die Anweisungen aufgesplittet wurden
 */
void _doLoop()
{    
  /** 
   * BINÄRE ANZEIGE
   */
  bdisplay_loop();
  GND_BIN = 1;
  if (tempReadCounter == BEGIN || tempReadCounter >= READ)
    temp_initCon();
  else
    __delay_us(FREQ_SLEEP);
  GND_BIN = 0;
  
  /**
   * LED-SEGMENT 1
   */
  ndisplay_loop(0);
  GND_NUM1 = 1;
  if (tempReadCounter == BEGIN)
  {
    temp_record();
    ndisplay_set_loading(1);
  }
  else if (tempReadCounter >= READ)
    temp_sendData();
  else
    __delay_us(FREQ_SLEEP);
  GND_NUM1 = 0;
  
  /**
   * LED-SEGMENT 2
   */
  ndisplay_loop(1);
  GND_NUM2 = 1;
  if(tempReadCounter >= READ)
  {
    float temp = temp_interpret();
    if(temp > -50) //<50 Datenmüll, WTF?? Wird sich schon nicht geändert haben...
    {
      ndisplay_set(temp);
      bdisplay_set(temp);
    }
    tempReadCounter = 0;
    ndisplay_set_loading(0);
  }
  else
    __delay_us(FREQ_SLEEP);
  GND_NUM2 = 0;
  
  /**
   * LED-SEGMENT 3
   */
  ndisplay_loop(2);
  GND_NUM3 = 1;
  __delay_us(FREQ_SLEEP);
  GND_NUM3 = 0;

  /**
   * LED-SEGMENT 4
   */
  ndisplay_loop(3);
  GND_NUM4 = 1;
  if (tempReadCounter == READ)
  {
    if(currentTempToShow > -50) //<50 Datenmüll, WTF?? Wird sich schon nicht geändert haben...
    {
      ndisplay_set(currentTempToShow);
      bdisplay_set(currentTempToShow);
    }
  }
  else
    __delay_us(FREQ_SLEEP);
  GND_NUM4 = 0;
  
  tempReadCounter++;
}

/**
 * Hauptfunktion
 */
int main()
{
  _initInternal();
  _initPins();

  // "Booten"
  ndisplay_boot_anim();
  bdisplay_boot_anim();
  
  // Wir wollen am Anfang auch schon eine Anzeige haben
  tempReadCounter = BEGIN - 5;
  
  while (1)
    _doLoop();
  
  return 0;
}
