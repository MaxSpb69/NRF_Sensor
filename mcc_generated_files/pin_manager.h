/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1619
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_AN2 aliases
#define channel_AN2_TRIS                 TRISAbits.TRISA2
#define channel_AN2_LAT                  LATAbits.LATA2
#define channel_AN2_PORT                 PORTAbits.RA2
#define channel_AN2_WPU                  WPUAbits.WPUA2
#define channel_AN2_OD                   ODCONAbits.ODA2
#define channel_AN2_ANS                  ANSELAbits.ANSA2
#define channel_AN2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define channel_AN2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define channel_AN2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define channel_AN2_GetValue()           PORTAbits.RA2
#define channel_AN2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define channel_AN2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define channel_AN2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define channel_AN2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define channel_AN2_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define channel_AN2_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define channel_AN2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define channel_AN2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SPI_SCK aliases
#define SPI_SCK_TRIS                 TRISCbits.TRISC0
#define SPI_SCK_LAT                  LATCbits.LATC0
#define SPI_SCK_PORT                 PORTCbits.RC0
#define SPI_SCK_WPU                  WPUCbits.WPUC0
#define SPI_SCK_OD                   ODCONCbits.ODC0
#define SPI_SCK_ANS                  ANSELCbits.ANSC0
#define SPI_SCK_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SPI_SCK_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SPI_SCK_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SPI_SCK_GetValue()           PORTCbits.RC0
#define SPI_SCK_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SPI_SCK_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SPI_SCK_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SPI_SCK_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SPI_SCK_SetPushPull()        do { ODCONCbits.ODC0 = 0; } while(0)
#define SPI_SCK_SetOpenDrain()       do { ODCONCbits.ODC0 = 1; } while(0)
#define SPI_SCK_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SPI_SCK_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set SPI_MOSI aliases
#define SPI_MOSI_TRIS                 TRISCbits.TRISC1
#define SPI_MOSI_LAT                  LATCbits.LATC1
#define SPI_MOSI_PORT                 PORTCbits.RC1
#define SPI_MOSI_WPU                  WPUCbits.WPUC1
#define SPI_MOSI_OD                   ODCONCbits.ODC1
#define SPI_MOSI_ANS                  ANSELCbits.ANSC1
#define SPI_MOSI_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SPI_MOSI_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SPI_MOSI_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SPI_MOSI_GetValue()           PORTCbits.RC1
#define SPI_MOSI_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SPI_MOSI_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SPI_MOSI_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SPI_MOSI_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SPI_MOSI_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define SPI_MOSI_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define SPI_MOSI_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define SPI_MOSI_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SPI_MISO aliases
#define SPI_MISO_TRIS                 TRISCbits.TRISC2
#define SPI_MISO_LAT                  LATCbits.LATC2
#define SPI_MISO_PORT                 PORTCbits.RC2
#define SPI_MISO_WPU                  WPUCbits.WPUC2
#define SPI_MISO_OD                   ODCONCbits.ODC2
#define SPI_MISO_ANS                  ANSELCbits.ANSC2
#define SPI_MISO_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SPI_MISO_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SPI_MISO_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SPI_MISO_GetValue()           PORTCbits.RC2
#define SPI_MISO_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SPI_MISO_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SPI_MISO_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SPI_MISO_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SPI_MISO_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define SPI_MISO_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define SPI_MISO_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SPI_MISO_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set SPI_CS aliases
#define SPI_CS_TRIS                 TRISCbits.TRISC3
#define SPI_CS_LAT                  LATCbits.LATC3
#define SPI_CS_PORT                 PORTCbits.RC3
#define SPI_CS_WPU                  WPUCbits.WPUC3
#define SPI_CS_OD                   ODCONCbits.ODC3
#define SPI_CS_ANS                  ANSELCbits.ANSC3
#define SPI_CS_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SPI_CS_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SPI_CS_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SPI_CS_GetValue()           PORTCbits.RC3
#define SPI_CS_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SPI_CS_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SPI_CS_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SPI_CS_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SPI_CS_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define SPI_CS_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define SPI_CS_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SPI_CS_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set NRF_CE aliases
#define NRF_CE_TRIS                 TRISCbits.TRISC4
#define NRF_CE_LAT                  LATCbits.LATC4
#define NRF_CE_PORT                 PORTCbits.RC4
#define NRF_CE_WPU                  WPUCbits.WPUC4
#define NRF_CE_OD                   ODCONCbits.ODC4
#define NRF_CE_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define NRF_CE_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define NRF_CE_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define NRF_CE_GetValue()           PORTCbits.RC4
#define NRF_CE_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define NRF_CE_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define NRF_CE_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define NRF_CE_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define NRF_CE_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define NRF_CE_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)

// get/set NRF_IRQ aliases
#define NRF_IRQ_TRIS                 TRISCbits.TRISC5
#define NRF_IRQ_LAT                  LATCbits.LATC5
#define NRF_IRQ_PORT                 PORTCbits.RC5
#define NRF_IRQ_WPU                  WPUCbits.WPUC5
#define NRF_IRQ_OD                   ODCONCbits.ODC5
#define NRF_IRQ_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define NRF_IRQ_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define NRF_IRQ_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define NRF_IRQ_GetValue()           PORTCbits.RC5
#define NRF_IRQ_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define NRF_IRQ_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define NRF_IRQ_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define NRF_IRQ_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define NRF_IRQ_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define NRF_IRQ_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISCbits.TRISC6
#define LED_LAT                  LATCbits.LATC6
#define LED_PORT                 PORTCbits.RC6
#define LED_WPU                  WPUCbits.WPUC6
#define LED_OD                   ODCONCbits.ODC6
#define LED_ANS                  ANSELCbits.ANSC6
#define LED_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_GetValue()           PORTCbits.RC6
#define LED_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define LED_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONCbits.ODC6 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONCbits.ODC6 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/