/*
 * File:   spi_prog.c
 * Author: maxsp
 *
 * Created on May 8, 2022, 4:38 PM
 */

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"

uint8_t SPI_byte_SendReceive(uint8_t send_byte)
{
    uint8_t mask = 0b10000000;
    uint8_t receive_byte = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        if(send_byte & mask)        // MOSI output setting
             SPI_MOSI_SetHigh();
        else
            SPI_MOSI_SetLow();
          SPI_SCK_SetHigh();          // SCK pulse send
         receive_byte <<= 1;
         receive_byte |= SPI_MISO_GetValue();
         __delay_us(50);
        SPI_SCK_SetLow();
        mask >>= 1;    
    }
    return receive_byte;
}

void SPI_byte_Send(uint8_t send_byte)
{
    uint8_t mask = 0b10000000;
    for(uint8_t i = 0; i < 8; i++)
    {
        if(send_byte & mask)        // MOSI output setting
            SPI_MOSI_SetHigh();
        else
            SPI_MOSI_SetLow(); 
        SPI_SCK_SetHigh();          // SCK pulse send
         __delay_us(60);
        SPI_SCK_SetLow();
        mask >>= 1;    
    }
}

uint8_t SPI_byte_Receive(void)
{
    uint8_t receive_byte = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        SPI_SCK_SetHigh();          // SCK pulse send
        receive_byte <<= 1;
        receive_byte |= SPI_MISO_GetValue();
         __delay_us(40);
        SPI_SCK_SetLow();
    }
    return receive_byte;
}


void SPI_SendReceive(uint8_t * send_buf, uint8_t * receive_buf, uint16_t len)
{

    for(uint8_t i = 0; i < len; i++)
        *(receive_buf + i) = SPI_byte_SendReceive(*(send_buf + i));

}

void SPI_Send(uint8_t * send_buf, uint16_t len)
{

    for(uint8_t i = 0; i < len; i++)
        SPI_byte_Send(*(send_buf + i));
    SPI_MOSI_SetHigh();

}

void SPI_Receive(uint8_t * receive_buf, uint16_t len)
{

    for(uint8_t i = 0; i < len; i++)
        *(receive_buf + i) = SPI_byte_Receive();


}