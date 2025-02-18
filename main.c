/*
 * File:   main.c
 * Author: ryan
 *
 * Created on July 23, 2022, 8:34 PM
 */

#include "../PIC16F18877/in_progress/SSD1306_drivers.h"
#include "../PIC16F18877/libs/eeprom.h"
#include "../PIC16F18877/libs/i2c_drivers.h"
#include <pic16f18877.h>
#include <stdbool.h>

// CONFIG1
#pragma config FEXTOSC =                                                       \
    OFF // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC =                                                        \
    HFINT1 // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF // Clock Out Enable bit->CLKOUT function is
                              // disabled; i/o or oscillator function on OSC2
#pragma config CSWEN =                                                         \
    ON // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN =                                                         \
    ON // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE =                                                         \
    ON // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF   // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = ON    // Brown-out reset enable bits->Brown-out Reset
                             // Enabled, SBOREN bit is ignored
#pragma config BORV =                                                          \
    LO // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set
       // to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF // Zero-cross detect disable->Zero-cross detect circuit
                         // is disabled at POR.
#pragma config PPS1WAY =                                                       \
    ON // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared
       // and set only once in software
#pragma config STVREN = ON // Stack Overflow/Underflow Reset Enable bit->Stack
                           // Overflow or Underflow will cause a reset
#pragma config DEBUG = OFF // Background Debugger->Background Debugger disabled

// CONFIG3
#pragma config WDTCPS = WDTCPS_31 // WDT Period Select bits->Divider ratio
                                  // 1:65536; software control of WDTPS
#pragma config WDTE = OFF // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS =                                                        \
    WDTCWS_7 // WDT Window Select bits->window always open (100%); software
             // control; keyed access not required
#pragma config WDTCCS = SC // WDT input clock selector->Software Control

// CONFIG4
#pragma config WRT =                                                           \
    OFF // UserNVM self-write protection bits->Write protection off
#pragma config SCANE =                                                         \
    available // Scanner Enable bit->Scanner module is available for use
#pragma config LVP = ON // Low Voltage Programming Enable bit->Low Voltage
                        // programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF // UserNVM Program memory code protection bit->Program
                        // Memory code protection disabled
#pragma config CPD =                                                           \
    OFF // DataNVM code protection bit->Data EEPROM code protection disabled

#define _XTAL_FREQ 16000000

int main(void) {

  char phrase[] = {
      'r', ' ', 'Y', ' ', 'A', ' ', 'n', ' ', '&', ' ', 'K', ' ', 'a', ' ', 'L',
  };
  // NOSC HFINTOSC; NDIV 1;
  OSCCON1 = 0x60;
  // CSWHOLD may proceed; SOSCPWR Low power;
  OSCCON3 = 0x00;
  // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN
  // disabled; HFOEN disabled;
  OSCEN = 0x00;
  // HFFRQ 16_MHz;
  OSCFRQ = 0x05;
  // HFTUN 0;
  OSCTUNE = 0x00;

  I2C_Init();
  // SSD1306_Command(DISPLAYOFF);
  SSD1306_Init();
  // init_test();
  // GotoXY(1,50);
  // I2C_Stop();
  // Draw_pixel();
  // I2C_Stop();
  // SSD1306_Command(DISPLAYALLON_RESUME);
  while (1) {
    horizontal_fill_screen(0x55);
    __delay_ms(1000);
    horizontal_fill_screen(0x00);
    Horz_Goto_XY(0x34, 0x79, 0x00, 0x01);
    SSD1306_Data();

    for (int i = 0; i < 11; i++)
      put_char(&phrase[i]);

    __delay_ms(2000);
    horizontal_fill_screen(0x55);

    __delay_ms(1000);
    horizontal_fill_screen(0x00);

    Horz_Goto_XY(0x01, 0x46, 0x02, 0x03);
    SSD1306_Data();

    for (int i = 0; i < 11; i++)
      put_char(&phrase[i]);

    __delay_ms(2000);
    horizontal_fill_screen(0x00);
    Horz_Goto_XY(0x50, 0x7D, 0x01, 0x02);
    SSD1306_Data();

    for (int i = 0; i < 11; i++)
      put_char(&phrase[i]);

    __delay_ms(2000);
    horizontal_fill_screen(0x05);
    __delay_ms(1000);
    horizontal_fill_screen(0x00);
    Horz_Goto_XY(0x2D, 0x5A, 0x03, 0x03);
    SSD1306_Data();

    for (int i = 0; i < 11; i++)
      put_char(&phrase[i]);

    __delay_ms(2000);
    horizontal_fill_screen(0x55);
  }
  return 0;
}
