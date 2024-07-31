/********************************************************************************/
/*                                                                              */
/*                              omap3-gptimer.h                                 */
/*                                                                              */
/********************************************************************************/


#ifndef _OMAP3_TIMER_H
#define _OMAP3_TIMER_H

#include "user_type.h"

#define GPTIMER1_BASE 0x48318000
#define GPTIMER2_BASE 0x49032000
#define GPTIMER3_BASE 0x49034000
#define GPTIMER4_BASE 0x49036000
#define GPTIMER5_BASE 0x49038000
#define GPTIMER6_BASE 0x4903a000
#define GPTIMER7_BASE 0x4903c000
#define GPTIMER8_BASE 0x4903e000
#define GPTIMER9_BASE 0x49040000
#define GPTIMER10_BASE 0x48086000
#define GPTIMER11_BASE 0x48088000
#define GPTIMER13_BASE 0x48304000

#define GPT_TIOCP_CFG 0x010
#define GPT_TISTAT 0x014
#define GPT_TISR 0x018
#define GPT_TIER 0x01C
#define GPT_TWER 0x020
#define GPT_TCLR 0x024
#define GPT_TCRR 0x028
#define GPT_TLDR 0x02C
#define GPT_TTGR 0x030
#define GPT_TWPS 0x034
#define GPT_TMAR 0x038
#define GPT_TCAR1 0x03C
#define GPT_TSICR 0x040
#define GPT_TCAR2 0x044
#define GPT_TPIR 0x048
#define GPT_TNIR 0x04C
#define GPT_TCVR 0x050
#define GPT_TOCR 0x054
#define GPT_TOWR 0x058

// TISR/TIER flags
#define TCAR_IT_FLAG (1<<2)
#define OVF_IT_FLAG (1<<1)
#define MAT_IT_FLAG (1<<0)

#ifndef __ASSEMBLER__
struct omap3_gptimer {
	UINT32 pad0[4];
	volatile UINT32 TIOCP_CFG;
	volatile UINT32 TISTAT;
	volatile UINT32 TISR;
	volatile UINT32 TIER;
	volatile UINT32 TWER;
	volatile UINT32 TCLR;
	volatile UINT32 TCCR;
	volatile UINT32 TLDR;
	volatile UINT32 TTGR;
	volatile UINT32 TWPS;
	volatile UINT32 TMAR;
	volatile UINT32 TCAR1;
	volatile UINT32 TSICR;
	volatile UINT32 TCAR2;
	volatile UINT32 TPIR;
	volatile UINT32 TNIR;
	volatile UINT32 TCVR;
	volatile UINT32 TOCR;
	volatile UINT32 TOWR;
};
#endif

// TCLR Register
#define TCLR_GPO_CFG	14
#define TCLR_CAPT_MODE	13
#define TCLR_PT		12
#define TCLR_TRG	10
#define TCLR_TCM	 8
#define TCLR_SCPWM	 7
#define TCLR_CE		 6
//#define TCLR_PRE	 5
#define TCLR_PTV	 2
//#define TCLR_AR		 1
//#define TCLR_ST		 0



#endif


