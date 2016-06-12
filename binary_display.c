#include "binary_display.h"
#include <libpic30.h>

float __bin_displaynumber;

/**
 * Spielt die Boot-Animation auf diesem Display ab
 */
void bdisplay_boot_anim()
{
  _bdisplay_reset();
  GND_BIN = 1;
  
  unsigned int i;
  for(i = 0; i < 6; i++)
  {
    BINLED_DOT = i % 2;
    __delay_ms(30);
    BINLED1 = i % 2;
    __delay_ms(30);
    BINLED2 = i % 2;
    __delay_ms(30);
    BINLED3 = i % 2;
    __delay_ms(30);
    BINLED4 = i % 2;
    __delay_ms(30);
    BINLED5 = i % 2;
    __delay_ms(30);
    BINLED6 = i % 2;
  }
}

/**
 * Setzt die Zahl, die angezeigt werden soll.
 * Kommastellenbehandlung:
 * Erste Kommastelle >= 5 -> LED an
 * Erste Kommastelle < 5  -> LED aus
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void bdisplay_set(float pNumber)
{
  __bin_displaynumber = pNumber;
}

/**
 * Setzt die OUTPUT-Pins auf den nötigen Zustand,
 * damit die mit bidsplay_set gesetzte Zahl angezeigt wird
 */
void bdisplay_loop()
{
  _bdisplay_reset();
  unsigned int tmp_number = (int) __bin_displaynumber;
  BINLED1 = (tmp_number >> 0) & 1;
  BINLED2 = (tmp_number >> 1) & 1;
  BINLED3 = (tmp_number >> 2) & 1;
  BINLED4 = (tmp_number >> 3) & 1;
  BINLED5 = (tmp_number >> 4) & 1;
  BINLED6 = (tmp_number >> 5) & 1;
  BINLED_DOT = (((int) (__bin_displaynumber * 10.0F)) % 10) >= 5;
}

/**
 * Resettet alle nötigen Ausgänge.
 * Andere Output-Pins, die nicht benötigt werden,
 * werden nicht zurückgesetzt!
 */
void _bdisplay_reset()
{
  BINLED_DOT = 0;
  BINLED1 = 0;
  BINLED2 = 0;
  BINLED3 = 0;
  BINLED4 = 0;
  BINLED5 = 0;
  BINLED6 = 0;
}