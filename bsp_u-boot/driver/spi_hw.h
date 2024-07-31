/************************************************/
/*						*/
/*	spi_hw.h				*/	
/*						*/
/************************************************/


#ifndef _SPI_HW_H_
#define _SPI_HW_H_

#include "user_type.h"
#include "omap3-spi.h"

typedef UINT8 result_spi_hw_t;
#define SPI_HW_RES_OK				0
#define SPI_HW_ERR_MCSPI_UNKNOWN 		1
#define SPI_HW_ERR_RESET_FAILURE		2
#define SPI_HW_ERR_MCSPI_WRONG_CHANNEL  	3 
#define SPI_HW_ERR_ENABLE_IRQ_FAILURE		4
#define SPI_HW_ERR_TIMEOUT_WAITING_RXREG_READY	5
#define SPI_HW_ERR_WRONG_MODE			6

#define MCSPI1 1
#define MCSPI2 2
#define MCSPI3 3
#define MCSPI4 4

#define MCSPI_MASTER_MODE 0x0
#define MCSPI_SLAVE_MODE 0x1

#define MCSPI_NOIDLE_MODE 0x01

#define MCSPI_POL_PHA_MODE0	0x0	/*<! spim_clk Active High, sampling rising edge  POL=0x0 PHA=0x0 */
#define MCSPI_POL_PHA_MODE1	0x1	/*<! spim_clk Active High, sampling falling edge  POL=0x0 PHA=0x1 */
#define MCSPI_POL_PHA_MODE2	0x2	/*<! spim_clk Active Low,  sampling falling edge  POL=0x1 PHA=0x0 */
#define MCSPI_POL_PHA_MODE3	0x3	/*<! spim_clk Active Low,  sampling rising edge  POL=0x1 PHA=0x1 */

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_reset(UINT8 id) 
*/
/* ***************************************************/
result_spi_hw_t spi_hw_reset(UINT8 id); 


/* ***************************************************/
/**
   \fn result_spi_hw_t spi_hw_channelConfig(UINT8 id, UINT8 channel,UINT8 ffer,UINT8 ffew, UINT8 tcs, UINT8 sbpol, UINT8 sbe, UINT8 is,UINT8 dep0, UINT8 dep1, UINT8 trm, UINT8 wl,UINT8 clkd, UINT8 epol, UINT8 pol, UINT8 pha);
  Configure SPI channel.
*/
/* ***************************************************/
result_spi_hw_t spi_hw_channelConfig(UINT8 id, UINT8 channel,UINT8 ffer,UINT8 ffew, UINT8 tcs, UINT8 sbpol, UINT8 sbe, UINT8 is,UINT8 dep0, UINT8 dep1, UINT8 trm, UINT8 wl,UINT8 clkd, UINT8 epol, UINT8 pol, UINT8 pha);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_channelEnable(UINT8 id,UINT8 channel)
  Enable channel on MCSPIx device  
*/
/* ***************************************************/
result_spi_hw_t spi_hw_channelEnable(UINT8 id,UINT8 channel);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_channelDisable(UINT8 id,UINT8 channel)
  Disable channel on MCSPIx device  
*/
/* ***************************************************/
result_spi_hw_t spi_hw_channelDisable(UINT8 id,UINT8 channel);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_setDeviceMode(UINT8 id, UNT8 modea)
  Select Master o Slave mode
  \param UINT8 id
  \param mode  MCSPI_MASTER_MODE=0x0  MCSPI_SLAVE_MODE=0x1

*/
/* ***************************************************/
result_spi_hw_t spi_hw_setDeviceMode(UINT8 id, UINT8 mode);


/* ***************************************************/
/**
   \fn result_spi_hw_t spi_hw_resetIrqStatus(UINT8 id);
  Reset IRQ status bits 
*/
/* ***************************************************/
result_spi_hw_t spi_hw_resetIrqStatus(UINT8 id);

/* ***************************************************/
/**
 \fn result_spi_hw_t spi_hw_readIrqStatus(UINT8 id)
*/
/* ***************************************************/
result_spi_hw_t spi_hw_readIrqStatus(UINT8 id,UINT32 *irqStatusReg);



/* ***************************************************/
/**
  result_spi_hw_t spi_hw_readChStatus(UINT8 id,UINT8 channel,UINT32 *chStatusReg)
*/
/* ***************************************************/
result_spi_hw_t spi_hw_readChStatus(UINT8 id,UINT8 channel,UINT32 *chStatusReg);

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_waitRxRegReady(UINT8 id, UINT32 channel);
*/
/* ***************************************************/
result_spi_hw_t spi_hw_waitRxRegReady(UINT8 id, UINT32 channel);


/* ***************************************************/
/**
   \fn result_spi_hw_t spi_hw_clearStatus(UINT8 id,UINT8 irq)
 Clear the source of interrupt 
 \param UINT8 id select MCSPI device
 \param UINT8 irq select the interrupt source. Use irq position in IRQSTATUS register 
 
*/
/* ***************************************************/

result_spi_hw_t spi_hw_clearStatus(UINT8 id,UINT8 irq);

/* ***************************************************/
/**
   \fn result_spi_hw_t spi_hw_setXferLevel(UINT8 id,UINT8 ael, UINT8 afl, UINT16 wcnt);
*/
/* ***************************************************/
result_spi_hw_t spi_hw_setXferLevel(UINT8 id,UINT8 ael, UINT8 afl, UINT16 wcnt);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_getAFL(UINT8 id,UINT8 channel,UINT8 *afl)
  Get AFL value (Bufferl Full level) from CH CONFIG register
  \param UINT8 id  select MCSPI device
  \param UINT8 *afl retrive afl value from CHxCONF register  
*/
/* ***************************************************/
result_spi_hw_t spi_hw_getAFL(UINT8 id,INT8 *afl);

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_getAEL(UINT8 id,UINT8 channel,UINT8 *ael)
  Get AFL value (Bufferl Full level) from CH CONFIG register
  \param UINT8 id  select MCSPI device
  \param UINT8 *ael retrive ael value from CHxCONF register  
*/
/* ***************************************************/
result_spi_hw_t spi_hw_getAEL(UINT8 id,UINT8 *ael);

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_setXferSize(UINT8 id, UINT16 wcnt)
  Set transfer size in number of word.
  \param UINT8 id  select MCSPI device
  \param UINT16 wcnt set number of word to transfer   		
*/
/* ***************************************************/
result_spi_hw_t spi_hw_setXferSize(UINT8 id, UINT16 wcnt);

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_writeTxReg(UINT8 id, UINT8 channel, UINT32 value)
  Write data in MCSPI TXx register
*/
/* ***************************************************/
result_spi_hw_t spi_hw_writeTxReg(UINT8 id, UINT8 channel, UINT32 value);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_readRxReg(UINT8 id, UINT8 channel, UINT32 *value)
  Read data from RX Register in MCSPI device and channel x
  \param UINT8 id select MCSPI device
  \param UINT8 channel select channel 
  \param UINT32 *value contains data read from RX Register
*/
/* ***************************************************/
result_spi_hw_t spi_hw_readRxReg(UINT8 id, UINT8 channel, UINT32 *value);

/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_getWordLength(UINT8 id, UINT8 channel, UINT8 *wl);
*/
/* ***************************************************/
result_spi_hw_t spi_hw_getWordLength(UINT8 id, UINT8 channel, UINT8 *wl);

/* ***************************************************/
/**
 \fn result_spi_hw_t spi_hw_dump_reg(UINT8 id, UINT8  channel);
*/
/* ***************************************************/
result_spi_hw_t spi_hw_dump_reg(UINT8 id, UINT8  channel);
/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_irqEnable(UINT8 id)
*/
/* ***************************************************/
result_spi_hw_t spi_hw_irqEnable(UINT8 id);


/* ***************************************************/
/**
  \fn result_spi_hw_t spi_hw_setIdleMode(UINT8 id, UINT8 mode);
  Set idle mode.
*/
/* ***************************************************/
result_spi_hw_t spi_hw_setIdleMode(UINT8 id, UINT8 mode);

#endif  /*SPI_HW_H_ */

