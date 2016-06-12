#include "ds1820.h"
#include "drivers/ds1820.h"
#include "main.h"
#include <xc.h>

/**
 * Es wird eine Nachricht auf den Datenbus gesandt, dass nun
 * eine Nachricht gesendet wird.
 * Anschließend werden ALLE Sensoren auf diesem Bus angesprochen
 */
void temp_initCon()
{
  OW_MRI();
  OW_S_Rom();
}

/**
 * Weißt den DS18S20 an, eine Temperaturmessung durchzuführen und
 * auf seinen internen Speicher zu schreiben
 */
void temp_record()
{
  OW_W_Byte(0x44);
}

/**
 * Weißt den DS18S20 an, die vorher durchgeführte Temperaturmessung
 * auf den Bus zu senden
 */
void temp_sendData()
{
  OW_W_Byte(0xBE); // Befehl für Auslesen des Ergebnisses
}

/**
 * Interpretiert die vom DS18S20 gesandten Daten und gibt diese als
 * Float-Value zurück.
 * Achtung, es kann möglicherweise auch Datenmüll zurückommen
 * 
 * @return Temperatur
 */
float temp_interpret()
{
  unsigned int i;
  for (i = 0; i < 2; i++)
    DS18S20[i] = OW_R_Byte();
  
  float ftemp;
  if (DS18S20[1] == 0) // Positive Temp.-Werte
    ftemp = DS18S20[0] / 2.0F;
  else // Neg. Temp.-Werte
    ftemp = (((~DS18S20[0]) + 1) * (-1.0F)) / 2.0F;
  
  return ftemp;
}