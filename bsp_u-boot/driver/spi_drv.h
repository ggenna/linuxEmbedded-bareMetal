/************************************************************************/
/*									*/
/*				spi_drv.h				*/
/*									*/
/************************************************************************/	


#ifndef _SPI_H_
#define _SPI_H_

#include "user_type.h"
#include "pbits.h"


typedef UINT8 result_spi_t;
#define SPI_RES_OK				0
#define SPI_ERR_RESET_MCSPI_FAILURE		1
#define SPI_ERR_ENABLE_IRQ_FAILURE		2
#define SPI_ERR_RESET_IRQSTATUS_FAILURE		3
#define SPI_ERR_CH_CONFIG_FAILURE		4
#define SPI_ERR_SET_MASTERSLAVE_FAILURE		5
#define SPI_ERR_CH_UNCONFIGURED			6
#define SPI_ERR_WORD_LENGTH_WRONG		7
#define SPI_ERR_GET_WL				8
#define SPI_ERR_XFERLEVEL_FAILURE		9
#define SPI_ERR_XFERSIZE_FAILURE		9
#define SPI_ERR_XFERSTART_FAILURE		10
#define SPI_ERR_DISABLE_IDLE_MODE		11
#define SPI_ERR_TX_XFER_SIZE_NOT_SUPPORTED      12
#define SPI_ERR_TX_XFER                         13
#define SPI_ERR_RX_XFER                         14


#define MCSPI1 1
#define MCSPI2 2
#define MCSPI3 3
#define MCSPI4 4

#define XFER_TRANSMIT_RECEIVE			0x0
#define XFER_RECEIVE_ONLY			0x1
#define XFER_TRANSMIT_ONLY			0x2

#define SPI_FREQ_48MHZ				 1 
#define SPI_FREQ_24MHZ				 2 
#define SPI_FREQ_12MHZ				 4 
#define SPI_FREQ_6MHZ				 8
#define SPI_FREQ_3MHZ				16 
#define SPI_FREQ_1_5MHZ				32  
#define SPI_FREQ_750KHZ				64 
#define SPI_FREQ_375KHZ			       128 
#define SPI_FREQ_187KHZ			       256 
#define SPI_FREQ_93_7KHZ		       512  
#define SPI_FREQ_46_8KHZ		      1024   
#define SPI_FREQ_23_4KHZ		      2048   
#define SPI_FREQ_11_7KHZ		      4096   
#define SPI_FREQ_5_8KHZ		      	      8192   
#define SPI_FREQ_2_9KHZ		      	     16384   
#define SPI_FREQ_1_5KHZ		      	     32768   









#define SPI_STATUS_INIT		0x0
#define SPI_STATUS_STARTED	0x1
#define SPI_STATUS_DONE		0x2

#define SPI_MASTER_MODE		0
#define SPI_SLAVE_MODE		1


#define WORD_LENGTH	0x17  /*<! Define the word lenght in bits for the incoming data 24 bit*/
#define FIFO_CAPACITY   64    /*<! MCSPI FIFO size in bytes */	
//#define FIFO_CAPACITY   4    /*<! MCSPI FIFO size in bytes */	
#define FIFO_LEVEL_RX      0.01
#define FIFO_LEVEL_TX      0.01
/* ***************************************************/
/**
  \fn result_spi_t spi_init(UINT8 id, UINT8 chennel) 
  Initialize spi device
  \param UINT8 id select the MCSPIx device
  \param UINT8 channel select the channel inside the SPI device
  \param UINT8 mode select MASTER or SLAVE 
*/
/* ***************************************************/
result_spi_t spiInit(UINT8 id, UINT8 chennel, UINT8 mode, UINT8 xferMode, UINT8 spi_clk);




/* ***************************************************/
/**
 \fn result_spi_t spi_configXfer(UINT8 id, UINT8 channel)
  Setup the data transfer by SPI device
  \param UINT8 id select the MCSPIx device
  \param UINT8 channel select the channel inside the SPI device
*/
/* ***************************************************/
result_spi_t spi_configXfer(UINT8 id, UINT8 channel);


/* ***************************************************/
/**
  \fn  result_spi_t spi_startXfer(UINT8 id, UINT8 channel,UINT32 dstAdrr, UINT16 size)
  Start SPI transfer
  \param UINT8 id select the MCSPIx device
  \param UINT8 channel select the channel in MCSPIx device
  \param UINT16 size Data size to transfer in number of word
*/
/* ***************************************************/
result_spi_t spi_startXfer(UINT8 id, UINT8 channel,UINT32 *dstAdrr,UINT16 size);


/* ***************************************************/
/**
  \fn result_spi_t spi_stopXfer(UINT8 id, UINT8 channel);
  \param UINT8 id select the MCSPIx device
  \param UINT8 channel select the channel in MCSPIx device
*/
/* ***************************************************/
result_spi_t spi_stopXfer(UINT8 id, UINT8 channel);


/* ***************************************************/
/**
  \fn result_spi_t spi_getStatusXfer(UINT8 id, UINT8 channel, UINT8 *status)
  Get transfer status. status value will be DONE = 1 when the transfer will be completed.
  \param UINT8 id select the MCSPIx device
  \param UINT8 channel select the channel in MCSPIx device
  \param UINT8* status return transfer status
*/
/* ***************************************************/
result_spi_t spi_getStatusXfer(UINT8 id, UINT8 channel, UINT8 *status);

/* ***************************************************/
/*
  \fn result_spi_t spi_irq_handler(int id); 
*/
/* ***************************************************/
void spi_irq_handler(int id); 


/* ***************************************************/
/*
  result_spi_t spi_dataRxPolling(UINT8 id, UINT8 channel);
*/
/* ***************************************************/
result_spi_t spi_dataRxPolling(UINT8 id, UINT8 channel);



/* ***************************************************/
/*
  result_spi_t spi_dataTx(UINT8 id, UINT8 channel,UINT32 srcAddr,UINT16 size)
*/
/* ***************************************************/
result_spi_t spi_dataTx(UINT8 id, UINT8 channel,UINT32 srcAddr,UINT16 size);

/* ***************************************************/
/*
  \fn void spi_dump_reg(UINT8 id, UINT8  channel);
  Dump spi register 
*/
/* ***************************************************/
void spi_dump_reg(UINT8 id, UINT8  channel);
#endif


