
/*
 * File:   NRF24.c
 * Author: maxsp
 *
 * Created on May 8, 2022, 4:38 PM
 */
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "spi_prog.h"
#include "NRF24.h"


bool p_variant; /** False for RF24L01 and true for RF24L01P */
uint8_t payload_size = 0; /**< Fixed size of payloads */
bool dynamic_payloads_enabled; /**< Whether dynamic payloads are enabled. */
uint8_t pipe0_reading_address[5] = {0,}; /**< Last address set on pipe 0 for reading. */
uint8_t addr_width = 0; /**< The address width to use - 3,4 or 5 bytes. */
uint8_t txDelay = 0;
uint32_t volt;


static const uint8_t child_pipe_enable[] = {ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5};
static const uint8_t child_pipe[] = {RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5};
static const uint8_t child_payload_size[] = {RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5};

void SETCS_LOW(void)
{
    SPI_CS_SetLow(); 
   //__delay_us(2);
   
}    




uint8_t write_register(uint8_t reg, uint8_t value)
{
	uint8_t status = 0;
	uint8_t addr = W_REGISTER | (REGISTER_MASK & reg);
    
	SETCS_LOW();                                            // CS signal activate
    SPI_SendReceive(&addr, &status, 1);
    SPI_Send(&value, 1);
	SPI_CS_SetHigh();                                           // CS signal deactivate
	return status;
}


uint8_t write_registerMy(uint8_t reg, const uint8_t* buf, uint8_t len)
{
	uint8_t status = 0;
	uint8_t addr = W_REGISTER | (REGISTER_MASK & reg);

	SETCS_LOW();                                            // CS signal activate
	SPI_SendReceive(&addr, &status, 1);
	SPI_Send((uint8_t*)buf, len);
	SPI_CS_SetHigh();                                           // CS signal deactivate
	return status;
}

uint8_t read_register(uint8_t reg)
{
	uint8_t addr = R_REGISTER | (REGISTER_MASK & reg);
	uint8_t dt = 0, dumb = 0xff;

	SETCS_LOW();                                            // CS signal activate
	SPI_SendReceive(&addr, &dt, 1);
	SPI_SendReceive(&dumb, &dt, 1);
	SPI_CS_SetHigh();                                           // CS signal deactivate
	return dt;
}

void maskIRQ(bool tx, bool fail, bool rx)
{
	uint8_t config = read_register(NRF_CONFIG);
	config &= ~(1 << MASK_MAX_RT | 1 << MASK_TX_DS | 1 << MASK_RX_DR); //clear the interrupt flags
	config |= fail << MASK_MAX_RT | tx << MASK_TX_DS | rx << MASK_RX_DR; // set the specified interrupt flags
	write_register(NRF_CONFIG, config);
}

void setRetries(uint8_t delay, uint8_t count)
{
	write_register(SETUP_RETR, (delay&0xf)<<ARD | (count&0xf)<<ARC);
}

void setPALevel(uint8_t level)
{
  uint8_t setup = read_register(RF_SETUP) & 0xF8;

  if(level > 3) // If invalid level, go to max PA
  {
	  level = (RF24_PA_MAX << 1) + 1;		// +1 to support the SI24R1 chip extra bit
  }
  else
  {
	  level = (level << 1) + 1;	 		// Else set level as requested
  }

  write_register(RF_SETUP, setup |= level);	// Write it to the chip
}

bool setDataRate(rf24_datarate_e speed)
{
	bool result = false;
	uint8_t setup = read_register(RF_SETUP);
	setup &= ~((1 << RF_DR_LOW) | (1 << RF_DR_HIGH));
	txDelay = 85;

	if(speed == RF24_250KBPS)
	{
		setup |= (1 << RF_DR_LOW);
		txDelay = 155;
	}
	else
	{
		if(speed == RF24_2MBPS)
		{
			setup |= (1 << RF_DR_HIGH);
			txDelay = 65;
		}
	}

	write_register(RF_SETUP, setup);
	uint8_t ggg = read_register(RF_SETUP);

	if(ggg == setup)
	{
		result = true;
	}

	return result;
}

void toggle_features(void)
{
	uint8_t addr = ACTIVATE, dumb = 0x73;
	SETCS_LOW();                                             // CS signal activate
	SPI_Send(&addr, 1);
	SPI_Send(&dumb, 1);
	SPI_CS_SetHigh();                                           // CS signal deactivate
}

uint8_t spiTrans(uint8_t cmd)
{
	uint8_t status = 0;
	SETCS_LOW();                                            // CS signal activate
	SPI_SendReceive(&cmd, &status, 1);
	SPI_CS_SetHigh();                                           // CS signal deactivate
	return status;
}

uint8_t get_status(void)
{
	return spiTrans(NRF_NOP);
}


void setChannel(uint8_t channel)
{
	write_register(RF_CH, channel);
}

uint8_t flush_rx(void)
{
	return spiTrans(FLUSH_RX);
}

uint8_t flush_tx(void)
{
	return spiTrans(FLUSH_TX);
}

//Power up now. Radio will not power down unless instructed by MCU for config changes etc.
void powerUp(void)
{
	uint8_t cfg = read_register(NRF_CONFIG);
	// if not powered up then power up and wait for the radio to initialize
	if(!(cfg & (1 << PWR_UP)))
	{
		write_register(NRF_CONFIG, cfg | (1 << PWR_UP));
		__delay_us(5000);
	}
}

void powerDown(void)
{
	NRF_CE_SetLow(); // Guarantee CE is low on powerDown
	write_register(NRF_CONFIG, read_register(NRF_CONFIG) & ~(1 << PWR_UP));
}


uint8_t write_payload(const void* buf, uint8_t data_len, const uint8_t writeType)
{
	uint8_t status = 0;
	const uint8_t* current = (const uint8_t*)buf;
	uint8_t addr = writeType;

	data_len = rf24_min(data_len, payload_size);
	uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;

	SETCS_LOW(); 
	SPI_SendReceive(&addr, &status, 1);
	SPI_Send((uint8_t*)current, data_len);

	while(blank_len--)
	{
		uint8_t empt = 0;
		SPI_Send(&empt, 1);
	}

	SPI_CS_SetHigh();
	return status;
}



void startFastWrite(const void* buf, uint8_t len, const bool multicast, bool startTx)
{
	write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);

	if(startTx)
	{
		NRF_CE_SetHigh();
	}
}


bool write(const void* buf, uint8_t len)
{
    
	startFastWrite(buf, len, 1, 1);

    FVRCON = 0x81;  
    volt = ADC_GetConversion(channel_AN2);
    FVRCON = 0x01;
 	while(!(get_status() & ((1 << TX_DS) | (1 << MAX_RT))))
        continue;



	NRF_CE_SetLow();
	uint8_t status = write_register(NRF_STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));

	if(status & (1 << MAX_RT))
	{
		flush_tx(); //Only going to be 1 packet int the FIFO at a time using this method, so just flush
		return 0;
	}

	//TX OK 1 or 0
	return 1;
}


void openWritingPipe(uint64_t value)
{
	write_registerMy(RX_ADDR_P0, (uint8_t*)&value, addr_width);
	write_registerMy(TX_ADDR, (uint8_t*)&value, addr_width);
	write_register(RX_PW_P0, payload_size);
}

bool isAckPayloadAvailable(void)
{
	return !(read_register(FIFO_STATUS) & (1 << RX_EMPTY));
}

void enableAckPayload(void)
{
	write_register(FEATURE, read_register(FEATURE) | (1 << EN_ACK_PAY) | (1 << EN_DPL));
	write_register(DYNPD, read_register(DYNPD) | (1 << DPL_P1) | (1 << DPL_P0));
	dynamic_payloads_enabled = true;
}

void openReadingPipe(uint8_t child, uint64_t address)
{
	if(child == 0)
	{
		memcpy(pipe0_reading_address, &address, addr_width);
	}

	if(child <= 6)
	{
		// For pipes 2-5, only write the LSB
		if(child < 2)
		  write_registerMy(child_pipe[child], (const uint8_t*)&address, addr_width);
		else
		  write_registerMy(child_pipe[child], (const uint8_t*)&address, 1);

		write_register(child_payload_size[child], payload_size);
		write_register(EN_RXADDR, read_register(EN_RXADDR) | (1 << child_pipe_enable[child]));
	}
}


void closeReadingPipe(uint8_t pipe)
{
	write_register(EN_RXADDR, read_register(EN_RXADDR) & ~(1 << child_pipe_enable[pipe]));
}


void startListening(void)
{
	powerUp();

	write_register(NRF_CONFIG, read_register(NRF_CONFIG) | (1 << PRIM_RX));
	write_register(NRF_STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));
	NRF_CE_SetHigh();
	// Restore the pipe0 adddress, if exists
	if(pipe0_reading_address[0] > 0)
	{
		write_registerMy(RX_ADDR_P0, pipe0_reading_address, addr_width);
	}
	else
	{
		closeReadingPipe(0);
	}

	if(read_register(FEATURE) & (1 << EN_ACK_PAY))
	{
		flush_tx();
	}
}




uint8_t NRF_Init(void)
{
	uint8_t setup = 0;
	p_variant = false;
	payload_size = 32;
	dynamic_payloads_enabled = false;
	addr_width = 5;
	pipe0_reading_address[0] = 0;

	NRF_CE_SetLow();
	SPI_CS_SetHigh();
	__delay_us(5000);

	write_register(NRF_CONFIG, 0x0C); // Reset NRF_CONFIG and enable 16-bit CRC.
	setRetries(5, 15);
	setPALevel(RF24_PA_LOW); // Reset value is MAX

	if(setDataRate(RF24_250KBPS)) // check for connected module and if this is a p nRF24l01 variant
	{
		p_variant = true;
	}

	setup = read_register(RF_SETUP);
	setDataRate(RF24_250KBPS); // Then set the data rate to the slowest (and most reliable) speed supported by all hardware.

	// Disable dynamic payloads, to match dynamic_payloads_enabled setting - Reset value is 0
	toggle_features();
	write_register(FEATURE, 0);
	write_register(DYNPD, 0);
	dynamic_payloads_enabled = false;

	// Reset current status. Notice reset and flush is the last thing we do
	write_register(NRF_STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));
	setChannel(124);
	flush_rx();
	flush_tx();
	powerUp(); //Power up by default when begin() is called
	write_register(NRF_CONFIG, (read_register(NRF_CONFIG)) & ~(1 << PRIM_RX));
	return (setup != 0 && setup != 0xff);
}

bool available(uint8_t* pipe_num)
{
	if(!(read_register(FIFO_STATUS) & (1 << RX_EMPTY)))
	{
		if(pipe_num) // If the caller wants the pipe number, include that
		{
			uint8_t status = get_status();
			*pipe_num = (status >> RX_P_NO) & 0x07;
		}

		return true;
	}

	return 0;
}

void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
	const uint8_t* current = (const uint8_t*)buf;
	uint8_t data_len = rf24_min(len, 32);
	uint8_t addr = W_ACK_PAYLOAD | (pipe & 0x07);
	SETCS_LOW(); 
	SPI_Send(&addr, 1);
	SPI_Send((uint8_t*)current, data_len);
	SPI_CS_SetHigh();
}

uint8_t read_payload(void* buf, uint8_t data_len)
{
	uint8_t status = 0;
	uint8_t* current = (uint8_t*)buf;

	if(data_len > payload_size)
	{
		data_len = payload_size;
	}

	uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;

	uint8_t addr = R_RX_PAYLOAD;
	SETCS_LOW(); 
	SPI_Send(&addr, 1);
	SPI_Receive((uint8_t*)current, data_len);

	while(blank_len--)
	{
		uint8_t empt = 0;
		SPI_Receive(&empt, 1);
	}

	SPI_CS_SetHigh();
	return status;
}


void read(void* buf, uint8_t len)
{
	read_payload(buf, len);
	write_register(NRF_STATUS, (1 << RX_DR) | (1 << MAX_RT) | (1 << TX_DS));
}

uint8_t getDynamicPayloadSize(void)
{
	uint8_t result = 0, addr, dumb = 0xff;
	SETCS_LOW(); 
	addr = R_RX_PL_WID;
	SPI_SendReceive(&addr, &result, 1);
	SPI_SendReceive(&dumb, &result, 1);
	SPI_CS_SetHigh();

	if(result > 32)
	{
		flush_rx();
		__delay_us(2000);
		return 0;
	}

	return result;
}