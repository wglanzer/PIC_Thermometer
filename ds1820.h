/* 
 * File:   ds1820.h
 * Author: Werner
 *
 * Beschreibt die Schnittstelle vom Hauptprogramm
 * auf den DS18S20.
 * 
 * Aufrufreihenfolge MUSS eingehalten werden:
 * - temp_initCon();
 * - temp_record();
 * - __delay_ms(800);
 * - temp_initCon();
 * - temp_sendData();
 * - temp_interpret();
 * 
 * Created on 12. Juni 2016, 11:13
 */
#ifndef DS1820_H
#define	DS1820_H

/**
 * Es wird eine Nachricht auf den Datenbus gesandt, dass nun
 * eine Nachricht gesendet wird.
 * Anschließend werden ALLE Sensoren auf diesem Bus angesprochen
 */
void temp_initCon();

/**
 * Weißt den DS18S20 an, eine Temperaturmessung durchzuführen und
 * auf seinen internen Speicher zu schreiben
 */
void temp_record();

/**
 * Weißt den DS18S20 an, die vorher durchgeführte Temperaturmessung
 * auf den Bus zu senden
 */
void temp_sendData();

/**
 * Interpretiert die vom DS18S20 gesandten Daten und gibt diese als
 * Float-Value zurück
 * Achtung, es kann möglicherweise auch Datenmüll zurückommen
 * 
 * @return Temperatur
 */
float temp_interpret();

#endif	/* DS1820_H */

