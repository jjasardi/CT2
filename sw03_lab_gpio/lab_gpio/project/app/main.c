/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 Lab GPIO
 * -- Description : Configure and use GPIO port B as output and 
 * --               GPIO port A is input.
 * --               Lab version without additional hardware 
 * --               except for three wires.
 * --
 * -- $Id: main.c ostt $
 * ------------------------------------------------------------------------- */

#include <stdint.h>
#include <reg_stm32f4xx.h>

#include "reg_ctboard.h"

/* user macros */

#define MASK_3_BITS  0x0007

/* ----------------------------------------------------------------------------
 * Main
 * ------------------------------------------------------------------------- */


int main(void)
{
    uint16_t data_gpio_in;              // use to read input values from gpio
    uint8_t data_dip_switch;            // use to read values from dip switches

    GPIOA_ENABLE();                     // peripheral clk enable
    GPIOB_ENABLE();                     // peripheral clk enable

    /* Reset GPIOA specific values */
    GPIOA->MODER = 0xa8000000;           // mode register
    GPIOA->OSPEEDR = 0x00000000;         // output speed register
    GPIOA->PUPDR = 0x64000000;           // pull resistor register
    GPIOA->OTYPER = 0x00000000;          // type register (pp / f. gate)
    GPIOA->AFRL = 0x00000000;
    GPIOA->AFRH = 0x00000000;
    GPIOA->ODR = 0x00000000;             // output data register
    
    /* Reset GPIOB specific values */
    GPIOB->MODER = 0x00000280;           // mode register
    GPIOB->OSPEEDR = 0x000000c0;         // output speed register
    GPIOB->PUPDR = 0x00000100;           // pull resistor register
    GPIOB->OTYPER = 0x00000000;          // type register (pp / f. gate)
    GPIOB->AFRL = 0x00000000;
    GPIOB->AFRH = 0x00000000;
    GPIOB->ODR = 0x00000000;             // output data register
    

    /* configure GPIO pins
     * clear register bits: GPIOx->xxxx &= ~(clear_mask << bit_pos);
     * set register bits:   GPIOx->xxxx |=  (set_value << bit_pos);
     * On GPIOA and GPIOB only pins 11 down to 0 are available to the user. 
     * Pins 15 down to 12 are used for system functions of the discovery board, 
     * e.g. connection of the debugger.
     * These pins must not be reconfigured. 
     * OTHERWISE THE DEBUGGER CANNOT BE USED ANY MORE!!!
     */
    /// STUDENTS: To be programmed
		GPIOA->MODER &= ~(0x03 << 0);  // clear PA0 direction mode
		GPIOA->MODER |= 0x00 << 0;     //  set PA0 direction mode
			
		GPIOA->MODER &= ~(0x03 << 2);  // clear PA1 direction mode
		GPIOA->MODER |= 0x00 << 2;     //  set PA1 direction mode
			
		GPIOA->MODER &= ~(0x03 << 4);  // clear PA2 direction mode
		GPIOA->MODER |= 0x00 << 4;     //  set PA2 direction mode
		
		GPIOA->PUPDR &= ~(0x03 << 0);  // clear PA0 pull-up/pull-down
		GPIOA->PUPDR |= 0x02 << 0;     //  set PA0 pull-up/pull-down
			
		GPIOA->PUPDR &= ~(0x03 << 2);  // clear PA1 pull-up/pull-down
		GPIOA->PUPDR |= 0x01 << 2;     //  set PA1 pull-up/pull-down
			
		GPIOA->PUPDR &= ~(0x03 << 4);  // clear PA2 pull-up/pull-down
		GPIOA->PUPDR |= 0x00 << 4;     //  set PA2 pull-up/pull-down
		
		//---------
		GPIOB->MODER &= ~(0x03 << 0);  // clear PB0 direction mode
		GPIOB->MODER |= 0x01 << 0;     //  set PB0 direction mode
			
		GPIOB->MODER &= ~(0x03 << 2);  // clear PB1 direction mode
		GPIOB->MODER |= 0x01 << 2;     //  set PB1 direction mode
			
		GPIOB->MODER &= ~(0x03 << 4);  // clear PB2 direction mode
		GPIOB->MODER |= 0x01 << 4;     //  set PB2 direction mode
		
		GPIOB->OTYPER &= ~(0x01 << 0);  // clear PB0 type
		GPIOB->OTYPER |= 0x0 << 0;     //  set PB0 type
			
		GPIOB->OTYPER &= ~(0x01 << 1);  // clear PB1 type
		GPIOB->OTYPER |= 0x1 << 1;     //  set PB1 type
			
		GPIOB->OTYPER &= ~(0x01 << 2);  // clear PB2 type
		GPIOB->OTYPER |= 0x1 << 2;     //  set PB2 type
		
		GPIOB->PUPDR &= ~(0x03 << 0);  // clear PB0 pull-up/pull-down
		GPIOB->PUPDR |= 0x00 << 0;     //  set PB0 pull-up/pull-down
			
		GPIOB->PUPDR &= ~(0x03 << 2);  // clear PB1 pull-up/pull-down
		GPIOB->PUPDR |= 0x00 << 2;     //  set PB1 pull-up/pull-down
			
		GPIOB->PUPDR &= ~(0x03 << 4);  // clear PB2 pull-up/pull-down
		GPIOB->PUPDR |= 0x01 << 4;     //  set PB2 pull-up/pull-down
		
		GPIOB->OSPEEDR &= ~(0x03 << 0);  // clear PB0 speed
		GPIOB->OSPEEDR |= 0x00 << 0;     //  set PB0 speed
			
		GPIOB->OSPEEDR &= ~(0x03 << 2);  // clear PB1 speed
		GPIOB->OSPEEDR |= 0x01 << 2;     //  set PB1 speed
			
		GPIOB->OSPEEDR &= ~(0x03 << 4);  // clear PB2 speed
		GPIOB->OSPEEDR |= 0x03 << 4;     //  set PB2 speed
		
		



    /// END: To be programmed

    while (1) {
        /* implement tasks 6.1 to 6.2 below */
        /// STUDENTS: To be programmed
			
			uint8_t valueA = (GPIOA->IDR & MASK_3_BITS); //read bits PA2..PA0
			CT_LED->BYTE.LED23_16 = valueA;
			
			//-------
			
			uint8_t valueB = (CT_DIPSW->BYTE.S15_8 & MASK_3_BITS); //read bits PB2..PB0
			CT_LED->BYTE.LED15_8 = valueB;
			
			GPIOB->ODR = valueB;
			uint8_t valueODR = (GPIOB->ODR & 0x07);
			CT_LED->BYTE.LED7_0 = valueODR;
			



        /// END: To be programmed

    }
}
