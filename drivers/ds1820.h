/* *****************************************************************************
 * File:        ds1820.h
 * Project:     --
 * Author:      Nicolas Meyert�ns
 * Version:     1.4
 * Web:         www.PIC-Projekte.de
 * ****************************************************************************/

#ifndef DS1820_DRIVER
#define	DS1820_DRIVER

#include <stdint.h>

/*Makros*/
#define LAT_DQ          LATBbits.LATB6
#define DQ              PORTBbits.RB6
#define TRIS_DQ         TRISBbits.TRISB6

/*Bekannmachen globaler Variablen*/
extern uint8_t DS18S20 [9];

/*Prototypen*/
uint8_t OW_MRI (void);
void OW_W_Bit (uint8_t bitvalue);
void OW_W_Byte (uint8_t bytevalue);
uint8_t OW_R_Bit (void);
uint8_t OW_R_Byte (void);
void OW_S_Rom(void);

#endif	/* DS1820_DRIVER.H */