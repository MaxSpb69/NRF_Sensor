/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1619
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "mcc_generated_files/pin_manager.h"
#include "spi_prog.h"
#include "NRF24.h"
/*
                         Main application
 */
#define IN_SENSOR

#define HTU21Address    0x40  
#define TRY_NUMBERS     3

#ifndef IN_SENSOR
    #define SensorID        0x00a0 // Идентификатор внешнего датчика
#else
    #define SensorID        0x00aa  // Идентификатор внутреннего датчика
#endif

uint32_t Stemp;
uint8_t RW_Data[3];
#ifndef IN_SENSOR
    const uint64_t pipe1 = 0xE8E8F0F0E2LL; // адрес  трубы (наружный датчик)
#else    
    const uint64_t pipe1 =   0xE8E8F0F0A2LL; // адрес трубы  (внутренний датчик)
#endif    
uint16_t counter = 0;
uint16_t buf_for_response[4] = {0, 0, 0, 0};

uint8_t nrf_data[4] = {0,}; // буфер для приема ответа/подтверждения
uint8_t pipe_num = 0;
uint8_t interval = 0x0b;
uint8_t try_counter;
bool send_ok_flag = false;



void Init_NRF(void)
{
    NRF_Init();
    enableAckPayload();
    openWritingPipe(pipe1);
    
}

void Start_conversion(void)
{

    RW_Data[0] = 0xf3;
    I2C_WriteNBytes(HTU21Address, RW_Data, 1); // Запуск измерения температуры в No Hold Mode
    __delay_ms(55);
    I2C_ReadNBytes(HTU21Address, RW_Data, 3);
    Stemp = ((RW_Data[0] * 256) + RW_Data[1]) & 0x0000fffc;
    Stemp = (17572 * Stemp) / 65536;
    buf_for_response[0] = Stemp - 4685;
    RW_Data[0] = 0xf5;
    I2C_WriteNBytes(HTU21Address, RW_Data, 1); // Запуск измерения влажности в No Hold Mode
    __delay_ms(55);
    I2C_ReadNBytes(HTU21Address, RW_Data, 3);
    Stemp = ((RW_Data[0] * 256) + RW_Data[1]) & 0x0000fff0;
    Stemp = (Stemp * 12500) / 65536;
    buf_for_response[1] = Stemp - 600;
//    FVRCON = 0x82;
//    buf_for_response[2] = ADC_GetConversion(channel_AN2);
//    FVRCON = 0x02;
    buf_for_response[3] = SensorID;

    
}

void GetBatteryVoltage(void)
{
   uint32_t volt;
   FVRCON = 0x82;
   volt = ADC_GetConversion(channel_AN2);
   __delay_ms(2);
    volt += ADC_GetConversion(channel_AN2);
   __delay_ms(2);
    volt += ADC_GetConversion(channel_AN2);
    buf_for_response[2]  = (uint16_t)(volt / 3);
//    buf_for_response[2]  = ADC_GetConversion(channel_AN2);
    FVRCON = 0x02;

}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    
    WDTCON0 = 0x19;
    __delay_ms(20);
    RW_Data[0] = 0xfe;
    I2C_WriteNBytes(HTU21Address, RW_Data, 1);         // Soft reset
    __delay_ms(20);
    I2C_Write1ByteRegister(HTU21Address, 0xe6, 0b00000010);    // User register setup
    LED_SetHigh();
    GetBatteryVoltage();
    
while (1)
{
    LED_SetLow();
    WDTCON0 = 0x15;
    Start_conversion(); 

    
    
    if(!send_ok_flag)     // Если за заданное число попыток так и не получили подтверждения приема и ответ
      Init_NRF();         // на всякий случай проинитим заново трансивер
    powerUp();
    send_ok_flag = false;
    for(try_counter = 0; try_counter < TRY_NUMBERS; try_counter++)
    {
        if(write(buf_for_response, 8)) // отправляем данные (8 байт)
        {
            if(isAckPayloadAvailable()) // проверяем пришло ли что-то вместе с ответом
            {
                read(nrf_data, 4); 
                flush_rx();
                if(nrf_data[0] == 0xd3) // Если это команда "Изменить интервал" (0xd3)
                {
                    interval = nrf_data[1] & 0x1f;  // Меняем интервал выхода в эфир
                    send_ok_flag = true;
                }
            }
       }
       
        if(send_ok_flag)
            break;
      // __delay_us(30000);
   }
    GetBatteryVoltage();
    powerDown();                    // Выключим трансивер
    WDTCON0 = (interval << 1) | 1;  // Установим WatchDog на интервал полученный в ответе, чтобы он разбудил процессор                 
    LED_SetHigh();  
    
    SLEEP();                        // СПАТЬ!!!!!
    //__delay_us(3000000);
    
  } // while(1)
}

/**
 End of File
*/