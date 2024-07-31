/*************************************************************************/          	
/*									 */
/*			omap3-spi.h					 */
/*									 */
/*************************************************************************/          	


#ifndef _OMAP3_SPI_H_
#define _OMAP3_SPI_H_

#include "user_type.h"

#define SPI_HW_RESET_DONE 	1

#define OMAP3_MCSPI1_BASE	0x48098000
#define OMAP3_MCSPI2_BASE	0x4809A000
#define OMAP3_MCSPI3_BASE	0x480B8000
#define OMAP3_MCSPI4_BASE	0x480BA000

#define OMAP3_MCSPI_MAX_FREQ	48000000

/*MCSPI REG offset*/
#define MCSPI_REVISION		0x0
#define MCSPI_SYSCONFIG		0x10
#define MCSPI_SYSSTATUS		0x14
#define MCSPI_IRQSTATUS		0x18
#define MCSPI_IRQENABLE		0x1C
#define MCSPI_WAKEUPENABLE	0x20
#define MCSPI_SYST		0x24
#define MCSPI_MODULCTRL		0x28
#define MCSPI_CH0CONF		0x2C
#define MCSPI_CH1CONF		0x40
#define MCSPI_CH2CONF		0x54
#define MCSPI_CH3CONF		0x68
#define MCSPI_CHSTAT		0x30
#define MCSPI_CH0STAT		0x0
#define MCSPI_CH1STAT		0x14
#define MCSPI_CH2STAT		0x28
#define MCSPI_CH3STAT		0x3c
#define MCSPI_CH0CTRL		0x34
#define MCSPI_CH1CTRL		0x48
#define MCSPI_CH2CTRL		0x5C
#define MCSPI_CH3CTRL		0x70
#define MCSPI_TX0		0x38
#define MCSPI_TX1		0x4C
#define MCSPI_TX2		0x60
#define MCSPI_TX3		0x74
#define MCSPI_RX0		0x3C
#define MCSPI_RX1		0x50
#define MCSPI_RX2		0x64
#define MCSPI_RX3		0x78
#define MCSPI_XFERLEVEL		0x7C



#if 0
/* OMAP3 McSPI registers */
struct mcspi_channel {
	unsigned int chconf;		/* 0x2C, 0x40, 0x54, 0x68 */
	unsigned int chstat;		/* 0x30, 0x44, 0x58, 0x6C */
	unsigned int chctrl;		/* 0x34, 0x48, 0x5C, 0x70 */
	unsigned int tx;		/* 0x38, 0x4C, 0x60, 0x74 */
	unsigned int rx;		/* 0x3C, 0x50, 0x64, 0x78 */
};

struct mcspi {
	unsigned char res1[0x10];
	unsigned int sysconfig;		/* 0x10 */
	unsigned int sysstatus;		/* 0x14 */
	unsigned int irqstatus;		/* 0x18 */
	unsigned int irqenable;		/* 0x1C */
	unsigned int wakeupenable;	/* 0x20 */
	unsigned int syst;		/* 0x24 */
	unsigned int modulctrl;		/* 0x28 */
	struct mcspi_channel channel[4]; /* channel0: 0x2C - 0x3C, bus 0 & 1 & 2 & 3 */
					/* channel1: 0x40 - 0x50, bus 0 & 1 */
					/* channel2: 0x54 - 0x64, bus 0 & 1 */
					/* channel3: 0x68 - 0x78, bus 0 */
};
#endif


/* per-register bitmasks */
//SYSCONFIG REG
#define OMAP3_MCSPI_SYSCONFIG_SIDLEMODE_POS		3
#define OMAP3_MCSPI_SYSCONFIG_SMARTIDLE 		(2 << 3)
#define OMAP3_MCSPI_SYSCONFIG_NOIDLEMODE		(1<<3)
#define OMAP3_MCSPI_SYSCONFIG_ENAWAKEUP 		(1 << 2)
#define OMAP3_MCSPI_SYSCONFIG_AUTOIDLE			(1 << 0)
#define OMAP3_MCSPI_SYSCONFIG_SOFTRESET 		(1 << 1)

#define OMAP3_MCSPI_SYSSTATUS_RESETDONE (1 << 0)

#define OMAP3_MCSPI_MODULCTRL_SINGLE	(1 << 0)
#define OMAP3_MCSPI_MODULCTRL_MS	(1 << 2)
#define OMAP3_MCSPI_MODULCTRL_STEST	(1 << 3)

#define OMAP3_MCSPI_CHCONF_PHA		(1 << 0)
#define OMAP3_MCSPI_CHCONF_PHA_POS	0
#define OMAP3_MCSPI_CHCONF_POL		(1 << 1)
#define OMAP3_MCSPI_CHCONF_POL_POS	1
#define OMAP3_MCSPI_CHCONF_CLKD_MASK	(0x0f << 2)
#define OMAP3_MCSPI_CHCONF_CLKD_POS	2
#define OMAP3_MCSPI_CHCONF_EPOL		(1 << 6)
#define OMAP3_MCSPI_CHCONF_EPOL_POS	6
#define OMAP3_MCSPI_CHCONF_WL_MASK	(0x1f << 7)
#define OMAP3_MCSPI_CHCONF_WL_POS	7
#define OMAP3_MCSPI_CHCONF_TRM_RX_ONLY	(0x01 << 12)
#define OMAP3_MCSPI_CHCONF_TRM_TX_ONLY	(0x02 << 12)
#define OMAP3_MCSPI_CHCONF_TRM_MASK	(0x03 << 12)
#define OMAP3_MCSPI_CHCONF_TRM_POS	12
#define OMAP3_MCSPI_CHCONF_DMAW		(1 << 14)
#define OMAP3_MCSPI_CHCONF_DMAW_POS	14
#define OMAP3_MCSPI_CHCONF_DMAR		(1 << 15)
#define OMAP3_MCSPI_CHCONF_DMAR_POS     15
#define OMAP3_MCSPI_CHCONF_DPE0		(1 << 16)
#define OMAP3_MCSPI_CHCONF_DPE0_POS	16
#define OMAP3_MCSPI_CHCONF_DPE1		(1 << 17)
#define OMAP3_MCSPI_CHCONF_DPE1_POS	17
#define OMAP3_MCSPI_CHCONF_IS		(1 << 18)
#define OMAP3_MCSPI_CHCONF_IS_POS	18
#define OMAP3_MCSPI_CHCONF_TURBO	(1 << 19)
#define OMAP3_MCSPI_CHCONF_TURBO_POS	19
#define OMAP3_MCSPI_CHCONF_FORCE	(1 << 20)
#define OMAP3_MCSPI_CHCONF_FORCE_POS	20
#define OMAP3_MCSPI_CHCONF_SBE 		(1 << 23)
#define OMAP3_MCSPI_CHCONF_SBE_POS 	23
#define OMAP3_MCSPI_CHCONF_SBPOL	(1 << 24)
#define OMAP3_MCSPI_CHCONF_SBPOL_POS	24
#define OMAP3_MCSPI_CHCONF_TCS_MASK	(3 << 25)
#define OMAP3_MCSPI_CHCONF_TCS_POS	 25
#define OMAP3_MCSPI_CHCONF_FFEW		(1 << 27)
#define OMAP3_MCSPI_CHCONF_FFEW_POS	27
#define OMAP3_MCSPI_CHCONF_FFER		(1 << 28)
#define OMAP3_MCSPI_CHCONF_FFER_POS	28



#define OMAP3_MCSPI_CHSTAT_RXS		(1 << 0)
#define OMAP3_MCSPI_CHSTAT_RXS_POS	0
#define OMAP3_MCSPI_CHSTAT_TXS		(1 << 1)
#define OMAP3_MCSPI_CHSTAT_TXS_POS	1
#define OMAP3_MCSPI_CHSTAT_EOT		(1 << 2)
#define OMAP3_MCSPI_CHSTAT_EOT_POS	2
#define OMAP3_MCSPI_CHSTAT_TXFFE	(1 << 3)
#define OMAP3_MCSPI_CHSTAT_TXFFE_POS	3
#define OMAP3_MCSPI_CHSTAT_TXFFF	(1 << 4)
#define OMAP3_MCSPI_CHSTAT_TXFFF_POS	4
#define OMAP3_MCSPI_CHSTAT_RXFFE	(1 << 5)
#define OMAP3_MCSPI_CHSTAT_RXFFE_POS	5
#define OMAP3_MCSPI_CHSTAT_RXFFF	(1 << 6)
#define OMAP3_MCSPI_CHSTAT_RXFFF_POS	6

#define OMAP3_MCSPI_CHCTRL_EN		(1 << 0)

#define OMAP3_MCSPI_WAKEUPENABLE_WKEN	(1 << 0)

/*XFERLEVEL REG*/
#define OMAP3_MCSPI_XFERLEVEL_AEL	(0X3F << 0)
#define OMAP3_MCSPI_XFERLEVEL_AFL	(0X3F << 8)
#define OMAP3_MCSPI_XFERLEVEL_AFL_POS	8
#define OMAP3_MCSPI_XFERLEVEL_WCNT	(0XFFFF << 16)

/*IRQ ENABLE REG*/
#define OMAP3_MCSPI_IRQENABLE_RX0_FULL_ENABLE_POS	2
#define OMAP3_MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_POS	3
#define OMAP3_MCSPI_IRQENABLE_RX0__ENABLE_EOWK_POS	17


#define OMAP3_MCSPI_IRQSTATUS_TX0_EMPTY_POS		0	
#define OMAP3_MCSPI_IRQSTATUS_TX0_UNDERFLOW_POS		1	
#define OMAP3_MCSPI_IRQSTATUS_RX0_FULL_POS		2	
#define OMAP3_MCSPI_IRQSTATUS_RX0_OVERFLOW_POS		3	
#define OMAP3_MCSPI_IRQSTATUS_TX1_EMPTY_POS		4	
#define OMAP3_MCSPI_IRQSTATUS_TX1_UNDERFLOW_POS		5	
#define OMAP3_MCSPI_IRQSTATUS_RX1_FULL_POS		6	
#define OMAP3_MCSPI_IRQSTATUS_TX2_EMPTY_POS		8	
#define OMAP3_MCSPI_IRQSTATUS_TX2_UNDERFLOW_POS		9	
#define OMAP3_MCSPI_IRQSTATUS_RX2_FULL_POS		10	
#define OMAP3_MCSPI_IRQSTATUS_TX3_EMPTY_POS		12
#define OMAP3_MCSPI_IRQSTATUS_TX3_UNDERFLOW_POS		13	
#define OMAP3_MCSPI_IRQSTATUS_RX3_FULL_POS		14	
#define OMAP3_MCSPI_IRQSTATUS_WKS_POS    		16	
#define OMAP3_MCSPI_IRQSTATUS_EOW_POS	        	17	


#if 0
struct omap3_spi_slave {
	struct spi_slave slave;
	struct mcspi *regs;
	unsigned int freq;
	unsigned int mode;
};

static inline struct omap3_spi_slave *to_omap3_spi(struct spi_slave *slave)
{
	return container_of(slave, struct omap3_spi_slave, slave);
}

int omap3_spi_txrx(struct spi_slave *slave, unsigned int len, const UINT8 *txp,
			UINT8 *rxp, unsigned long flags);
int omap3_spi_write(struct spi_slave *slave, unsigned int len, const UINT8 *txp,
		    unsigned long flags);
int omap3_spi_read(struct spi_slave *slave, unsigned int len, UINT8 *rxp,
		   unsigned long flags);
#endif

#endif /* _OMAP3_SPI_H_ */

