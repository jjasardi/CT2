/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Module      : SPI Library
 * -- Description :
 * --
 * -- $Id: hal_spi.c 4707 2019-02-26 09:32:59Z ruan $
 * ------------------------------------------------------------------
 */
#include <reg_stm32f4xx.h>
#include "hal_spi.h"

#define BIT_TXE  (uint32_t)0x00000002
#define BIT_RXNE (uint32_t)0x00000001
#define BIT_BSY  (uint32_t)0x00000080

static void set_ss_pin_low(void);
static void set_ss_pin_high(void);
static void wait_10_us(void);

/*
 * according to description in header file
 */
void hal_spi_init(void)
{
    RCC->APB2ENR |= 0x00001000;       // enable SPI clock
    RCC->AHB1ENR |= 0x00000001;       // start clock on GPIO A
    
    
    // configure GPIOs
    // P5.5 --> PA4 (NSS)       --> output
    // P5.6 --> PA5 (SCLK)      --> AF5 (see datasheet)
    // P5.7 --> PA6 (MISO)      --> AF5 (see datasheet)
    // P5.8 --> PA7 (MOSI)      --> AF5 (see datasheet)
    // P5.9 --> PA8 (NSBUF)     --> input
    
    GPIOA->OSPEEDR &= 0xFFFF00FF;   // clear PA4-PA7
    GPIOA->OSPEEDR |= 0x0000FF00;   // set PA4-PA7 to very high speed
    
    GPIOA->MODER &= 0xFFFC00FF;     // clear mode on PA4-PA8 --> PA8 = input
        
    GPIOA->MODER |= 0x0000A800;     // set alternate function on PA5-PA7
    GPIOA->MODER |= 0x00000100;     // set PA4 to output
    
    GPIOA->AFRL &= 0x000FFFFF;      // clear alternate function
    GPIOA->AFRL |= 0x55500000;      // Set SPI1 (AF5) alternate function PA5-PA7
    
    // configure SPI
    SPI1->CR2 = 0x0000;             // set spi to default state
    SPI1->CR1 = 0x0000;             // set spi to default state

    // add your SPI configs below (based on reference manual)
    
    /// STUDENTS: To be programmed
		
		SPI1->CR1 = 0x0300;       //set SSM and SSI to 1 and the other to 0 (0000 00011 0000 0000) Bit 8 and 9
		SPI1->CR1 |= 0x1 << 6;    //set SPE to 1 (Bit 6)
		SPI1->CR1 |= 0x1 << 2;    //set MSTR to 1 (Bit 2)
		SPI1->CR1 |= 0x111 << 3;  //set BR to 111 --> 42000kHz/200kHz = 210 (256 divider)


    /// END: To be programmed
    
    set_ss_pin_high();
}

/*
 * according to description in header file
 */
uint8_t hal_spi_read_write(uint8_t send_byte)
{
    /// STUDENTS: To be programmed
	
	//according to the flow chart "Handling Data transmission and reception"
	
	set_ss_pin_low();
	SPI1->DR = send_byte;									//DR = data register
	while (!(SPI1->SR & BIT_TXE)) {}			//SR = status register
	
	while (!(SPI1->SR & BIT_RXNE)) {}
	uint8_t valueFromRX = SPI1->DR;
	//while ((SPI1->SR & BIT_TXE) & (SPI1->SR & BIT_BSY)) {}
		
	wait_10_us();
	set_ss_pin_high();

	return valueFromRX;


    /// END: To be programmed
}

/**
 * \brief  Set Slave-Select Pin (P5.5 --> PA4) low
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_low(void)
{
    GPIOA->BSRR = 0x00100000;          // Set P5.5 --> PA4 low
}

/**
 * \brief  Set Slave-Select Pin (P5.5 --> PA4) high
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_high(void)
{
    GPIOA->BSRR = 0x00000010;          // Set P5.5 --> PA4 high
}

/**
 * \brief  Wait for approximately 10us
 *
 * No parameters
 *
 * No returns
 */
static void wait_10_us(void)
{
    uint8_t counter = 0;
    while (counter < 160) {
        counter++;
    }
}
