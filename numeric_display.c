#include "numeric_display.h"

float __num_displaynumber = -1;

/**
 * Ab dieser Grenze ist der gesetzte Float-Wert
 * nicht mehr gültig und es werden 888 angezeigt
 */
const float NUM_INVALID = -1000.0F;

/**
 * Setzt die Zahl, die angezeigt werden soll.
 * Es werden 1 Kommastelle und 2 Vorkommastellen angezeigt
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void ndisplay_set(float pNumber)
{
  __num_displaynumber = pNumber;
}

/**
 * Setzt die OUTPUT-Pins auf den nötigen Zustand,
 * damit die mit ndisplay_set gesetzte Zahl angezeigt wird
 */
void ndisplay_loop(unsigned int pSegment)
{
  _ndisplay_reset();
  if(__num_displaynumber <= NUM_INVALID)
  {
    NUMLEDA = 1;
    NUMLEDB = 1;
    NUMLEDC = 1;
    NUMLEDD = 1;
    NUMLEDE = 1;
    NUMLEDF = 1;
    NUMLEDG = 1;
    return;
  }
  
  switch(pSegment)
  {
    case 0:
      // Hier zeigen wir ein °-Symbol an
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDF = 1;
      NUMLEDG = 1; 
      break;
      
    case 1:
      _ndisplay_show_number(((unsigned int) (__num_displaynumber * 10.0F)) % 10);
      break;
      
    case 2:
      _ndisplay_show_number(((unsigned int) __num_displaynumber) % 10);
      break;
      
    case 3:
      _ndisplay_show_number(((unsigned int) (__num_displaynumber / 10.0F)) % 10);
      break;
  }
}

/**
 * Setzt das Display ungültig
 */
void ndisplay_boot_anim()
{
  ndisplay_set(NUM_INVALID);
}

/**
 * Resettet alle nötigen Ausgänge.
 * Andere Output-Pins, die nicht benötigt werden,
 * werden nicht zurückgesetzt!
 */
void _ndisplay_reset()
{
  NUMLEDA = 0;
  NUMLEDB = 0;
  NUMLEDC = 0;
  NUMLEDD = 0;
  NUMLEDE = 0;
  NUMLEDF = 0;
  NUMLEDG = 0;
}

/**
 * Setzt OUTPUT-Pins so, dass eine bestimmte Zahl angezeigt wird
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void _ndisplay_show_number(unsigned int pNumber)
{
  switch(pNumber)
  {
    case 0:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDE = 1;
      NUMLEDF = 1;
      break;
      
    case 1:
      NUMLEDB = 1;
      NUMLEDC = 1;
      break;
      
    case 2:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDD = 1;
      NUMLEDE = 1;
      NUMLEDG = 1;
      break;
      
    case 3:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDG = 1;
      break;
      
    case 4:
      NUMLEDB = 1;
      NUMLEDC = 1;
      NUMLEDF = 1;
      NUMLEDG = 1;
      break;
      
    case 5:
      NUMLEDA = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDF = 1;
      NUMLEDG = 1;
      break;
      
    case 6:
      NUMLEDA = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDE = 1;
      NUMLEDF = 1;
      NUMLEDG = 1;
      break;
      
    case 7:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDC = 1;
      break;
      
    case 8:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDE = 1;
      NUMLEDF = 1;
      NUMLEDG = 1;
      break;
      
    case 9:
      NUMLEDA = 1;
      NUMLEDB = 1;
      NUMLEDC = 1;
      NUMLEDD = 1;
      NUMLEDF = 1;
      NUMLEDG = 1;
      break;
  }
}