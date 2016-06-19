/* 
 * File:   numeric_display.h
 * Author: Werner
 *
 * Dieses Display beschreibt die dezimale Darstellung von 0-99.9
 * 
 * Created on 11. Juni 2016, 12:39
 */

#ifndef NUMERIC_DISPLAY_H
#define	NUMERIC_DISPLAY_H

#include "main.h"
#include <xc.h>

/*
 * Macros für Konfiguration 
 */
#define NUMLEDA    LATBbits.LATB5
#define NUMLEDB    LATBbits.LATB3
#define NUMLEDC    LATBbits.LATB0
#define NUMLEDD    LATBbits.LATB1
#define NUMLEDE    LATAbits.LATA2
#define NUMLEDF    LATAbits.LATA4
#define NUMLEDG    LATBbits.LATB2
#define NUMLED_DOT LATAbits.LATA1

/**
 * Spielt die Boot-Animation auf diesem Display ab
 */
void ndisplay_boot_anim();

/**
 * Setzt die Zahl, die angezeigt werden soll.
 * Es werden 1 Kommastelle und 2 Vorkommastellen angezeigt
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void ndisplay_set(float pNumber);

/**
 * Setzt, dass gerade etwas geladen wird
 * 
 * @param pIsLoading 1="Lädt gerade", 0="Laden fertig"
 */
void ndisplay_set_loading(unsigned int pIsLoading);

/**
 * Setzt die OUTPUT-Pins auf den nötigen Zustand,
 * damit die mit ndisplay_set gesetzte Zahl angezeigt wird
 */
void ndisplay_loop(unsigned int pSegment);

/**
 * Resettet alle nötigen Ausgänge.
 * Andere Output-Pins, die nicht benötigt werden,
 * werden nicht zurückgesetzt!
 */
void _ndisplay_reset();

/**
 * Setzt OUTPUT-Pins so, dass eine bestimmte Zahl angezeigt wird
 * 
 * @param pNumber Zahl, die angezeigt werden soll
 */
void _ndisplay_show_number(unsigned int pNumber);

#endif	/* NUMERIC_DISPLAY_H */

