/* 
 * File:   binary_display.h
 * Author: Werner
 *
 * Dieses Display beschreibt die binäre Darstellung von 0-63.5.
 * Hierzu werden 6+1 LEDs benötigt
 * 
 * Created on 11. Juni 2016, 12:40
 */

#ifndef BINARY_DISPLAY_H
#define	BINARY_DISPLAY_H

#include "main.h"
#include <xc.h>

/*
 * Macros für Konfiguration 
 */
#define BINLED_DOT LATAbits.LATA1
#define BINLED1    LATBbits.LATB2
#define BINLED2    LATBbits.LATB1
#define BINLED3    LATBbits.LATB0
#define BINLED4    LATAbits.LATA4
#define BINLED5    LATBbits.LATB3
#define BINLED6    LATAbits.LATA2

/**
 * Spielt die Boot-Animation auf diesem Display ab
 */
void bdisplay_boot_anim();

/**
 * Setzt die Zahl, die angezeigt werden soll.
 * Kommastellenbehandlung:
 * Erste Kommastelle >= 5 -> LED an
 * Erste Kommastelle < 5  -> LED aus
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void bdisplay_set(float pNumber);

/**
 * Setzt die OUTPUT-Pins auf den nötigen Zustand,
 * damit die mit bdisplay_set gesetzte Zahl angezeigt wird
 */
void bdisplay_loop();

/**
 * Resettet alle nötigen Ausgänge.
 * Andere Output-Pins, die nicht benötigt werden,
 * werden nicht zurückgesetzt!
 */
void _bdisplay_reset();

#endif	/* BINARY_DISPLAY_H */

