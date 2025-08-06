/*
 * RTC.c
 *
 *  Created on: Jul 29, 2025
 *      Author: SIGMA
 */

#include<avr/io.h>
#include"../MCAL/TWI.h"
#include"../common/std_types.h"



#define RTC_ADDRESS 0xD0
/*
 * RTC STORE VALUES IN BCD SO WE NEED TO CONVERT THE BCD VALUE TO DEC VALUE TO DIPLAY IT ON LCD
 */
static uint8 BCD_to_DEC(uint8 val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}
// THIS FUNCTION WILL BE USED IF WE WANT TO SET DATE AND TIME ON THE RTC AS IT ONLY UNDERSTAND BCD
static uint8 DEC_to_BCD(uint8 val) {
    return ((val / 10) << 4) | (val % 10);
}
// RTC_INIT TO INIT. ADDRESS BAUD RATE AND ENABLE TWEN
void RTC_init(void) {
    TWI_ConfigType config = {TWI_BAUD_100KHZ, 0x01}; // Dummy address
    TWI_init(&config);
}

void RTC_setTime(uint8 h, uint8 m, uint8 s) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);       // Write mode
    TWI_writeByte(0x00);              // Seconds register
    TWI_writeByte(DEC_to_BCD(s));
    TWI_writeByte(DEC_to_BCD(m));
    TWI_writeByte(DEC_to_BCD(h));
    TWI_stop();
}

void RTC_setDate(uint8 d, uint8 m, uint8 y) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x04); // Date register
    TWI_writeByte(DEC_to_BCD(d));
    TWI_writeByte(DEC_to_BCD(m));
    TWI_writeByte(DEC_to_BCD(y));
    TWI_stop();
}

uint8 RTC_getSecond(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x00); // Seconds register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}

uint8 RTC_getMinute(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x01); // Minutes register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}

uint8 RTC_getHour(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x02); // Hours register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}

uint8 RTC_getDay(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x04); // Date register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}

uint8 RTC_getMonth(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x05); // Month register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}

uint8 RTC_getYear(void) {
    TWI_start();
    TWI_writeByte(RTC_ADDRESS);
    TWI_writeByte(0x06); // Year register
    TWI_start();
    TWI_writeByte(RTC_ADDRESS | 1);
    uint8 val = TWI_readByteWithNACK();
    TWI_stop();
    return BCD_to_DEC(val);
}
