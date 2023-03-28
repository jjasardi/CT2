/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module lcd
 * --               Performs all the interactions with the lcd
 * --
 * -- $Id: lcd.c 5144 2020-09-01 06:17:21Z ruan $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdio.h>

/* user includes */
#include "lcd.h"
#include "reg_ctboard.h"

/* macros */
#define LCD_ADDR_LINE1      0u
#define LCD_ADDR_LINE2      20u

#define NR_OF_CHAR_PER_LINE 20u

#define LCD_CLEAR           "                    "

/// STUDENTS: To be programmed
void lcd_write_value(uint8_t slot_nr, uint8_t value) {
	//char lcdValue = snprintf(value)
	char buffer[3];
	snprintf(buffer, 3, "%02d", value);
	for(size_t i = 0; i < 3; i++) {

		CT_LCD->ASCII[(slot_nr - 1) * 3 + i] = buffer[i];
	}
}

void lcd_write_total(uint8_t total_value) {
	char buffer[16];
	snprintf(buffer, 16, "total throws %02d", total_value);
	for(size_t i = 0; i < 16; i++) {
		CT_LCD->ASCII[LCD_ADDR_LINE2 + i] = buffer[i];
	}
	//CT_LCD->ASCII[20] = total_value;
}

void hal_ct_lcd_clear(void) {
	CT_LCD->BG.GREEN = 65535;
	
	for(size_t i = 0; i < NR_OF_CHAR_PER_LINE; i++) {
		CT_LCD->ASCII[LCD_ADDR_LINE1 + i] = LCD_CLEAR[i];
		CT_LCD->ASCII[LCD_ADDR_LINE2 + i] = LCD_CLEAR[i];
	}
}



/// END: To be programmed
