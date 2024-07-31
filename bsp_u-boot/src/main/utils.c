
#include "utils.h"
#include "ADC.h"
#include "spi_drv.h"
 #include <string.h>
#include <command.h>
#include "extern_func.h"

#include "omap3-gptimer.h"
#include "omap3-system.h"

//#define DEBUG_CORRECTION // Per definire le stampe di debug

void xferData(UINT32 *data, UINT32 numWord, UINT32 numWordTot )
{
  UINT32 offset=0,remainder,totalWord;
  UINT8 status;
  result_spi_t res_spi;

  remainder = numWordTot % numWord;

  //set Total number of words
  if( remainder )
     totalWord = numWordTot + (numWord-remainder);
  else
     totalWord = numWordTot;
#ifdef DEBUGXFER
  printf("totalWord:%d\n" , totalWord);
#endif
  do{
    //waiting for  data ready go down
#ifdef ADC_BOARD
    while(gpio_get_value(PIN5))
    ;
#endif
#ifdef DEBUGXFER
    printf("data address:0x%08x\n",data);
#endif
    res_spi = spi_startXfer(MCSPI4, 0,data+offset ,numWord);

    if(res_spi != SPI_RES_OK)
      printf("Can't start transfer on MCSPI4 device ch 0, error:0x%08x\n",res_spi);
     do
     {
      res_spi =spi_dataRxPolling(MCSPI4,0/*channel*/ );
      if(res_spi != SPI_RES_OK)
        printf("Error SPI polling mode, err:0x%08x\n",res_spi);
      res_spi = spi_getStatusXfer(MCSPI4,0,&status);
     }
     while(status != SPI_STATUS_DONE);
#ifdef DEBUGXFER
     printf("Data receivced 0x%08x 0x%08x\n",*(data+offset),*(data+offset+1));
#endif
     if (status == SPI_STATUS_DONE)
        offset += numWord;

#ifdef DEBUGXFER
      printf("Received %d words,End loop\n",offset);
#endif
  }
  while(offset < totalWord);

}


void toVoltage(UINT32* fromADC,int length, float (*voltage)[2], float (*current)[2])
{
  int i,j;
  UINT32 ADCDincr = 0;
  UINT32 diff = 0;
#ifdef NO_DATAIN_CORRECTION
  j=0;

  for(i=0; i<2*length;i+=2)
  {
    voltage[j][0] = (float)(fromADC[i]&0x00FFFFFF)*LSBCH1;
    voltage[j][1]=0.0;
    current[j][0]=(float)(fromADC[i+1]&0x00FFFFFF)*LSBCH2;
    current[j][1]=0.0;
    j++;
  }
#else

  voltage[0][0] = (float)(fromADC[0]&0x00FFFFFF)*LSBCH1;
  voltage[0][1]=0.0;
  current[0][0]=(float)(fromADC[1]&0x00FFFFFF)*LSBCH2;
  current[0][1]=0.0;
  j=1;
  for(i=2; i<2*length;i+=2)
  {
    diff = (UINT32)(abs( (fromADC[i]&0x00FFFFFF)-(fromADC[i-2]&0x00FFFFFF)));
    if( diff < ((fromADC[i-2]&0x00FFFFFF)/THRESHOLDCH1))
    {
// acquisizione corretta
      voltage[j][0] = (float)(fromADC[i]&0x00FFFFFF)*LSBCH1;
#ifdef DEBUG_CORRECTION
      if(i<60)
	{
    	  printf (" voltage = %d [mV] ", FLOAT2INTx1000(voltage[j][0]));
          printf (" fromADC = %d [mV] ", (fromADC[i]&0x00FFFFFF));
          printf (" soglia = %d [mV] \n", ((fromADC[i]&0x00FFFFFF)/THRESHOLDCH1) );
        }
#endif
    }
    else
    {
// inseriamo la correzione
      
      ADCDincr = ( (fromADC[i-2]&0x00FFFFFF) + (fromADC[i+2]&0x00FFFFFF) )/2;
      fromADC[i] = ADCDincr;
 
      voltage[j][0] = (float)(fromADC[i]&0x00FFFFFF)*LSBCH1;
      //fromADC[i]=fromADC[i-2];
#ifdef DEBUG_CORRECTION
          printf (" YES_CORRECTION"); 
          printf (" soglia = %d [mV]", ((fromADC[i-2]&0x00FFFFFF)/THRESHOLDCH1) );
          printf (" diff = %d ", diff );
          printf (" voltage = %d [mV] ", FLOAT2INTx1000(voltage[j][0]));
          printf (" fromADC - 2 = %d [mV] \n", (fromADC[i-2]&0x00FFFFFF));
          printf (" fromADC  = %d [mV] \n", (fromADC[i]&0x00FFFFFF)); 
          printf (" fromADC + 2 = %d [mV] \n", (fromADC[i+2]&0x00FFFFFF));        
#endif
    }

    diff = (UINT32)(abs((fromADC[i+1]&0x00FFFFFF)-(fromADC[i-1]&0x00FFFFFF)));
    if( diff < ((fromADC[i+1]&0x00FFFFFF)/THRESHOLDCH2) )
    {  
      current[j][0]=(float)(fromADC[i+1]&0x00FFFFFF)*LSBCH2;
    }
    else
    { // applico la correzione
      ADCDincr = ( (fromADC[i-1]&0x00FFFFFF) + (fromADC[i+3]&0x00FFFFFF) )/2;
      fromADC[i+1] = ADCDincr; 
      current[j][0]=(float)(fromADC[i+1]&0x00FFFFFF)*LSBCH2;
      //fromADC[i+1]=fromADC[i-1];
    }
 
    voltage[j][1]=0.0;
    current[j][1]=0.0;
    j++;
  }
#endif



  #ifdef PRINTACQ
  for(i=0;i<length;i++)
  {
    printf (" VR = %d [mV] ", FLOAT2INTx1000(voltage[i][0]));
    printf (" IR = %d [mA] \n",FLOAT2INTx1000(current[i][0]));
  }
  #endif


}

int usbDeviceInit(char **argv,char *destStr,UINT32 size)
{
  int  i,usb_stor_curr_dev_local=-1,usb_ether_curr_dev_local=-1;

  if (argv==NULL)
  {
    printf("Argv argument error\n");
    return -1;
  } 

  if(destStr==NULL)
  {
    printf("Destination Address error\n");
    return -1;
  } 

  usb_stop();
  i = usb_init();
  if (i >= 0)
  {
   //  try to recognize storage devices immediately 
    usb_stor_curr_dev_local = usb_stor_scan(1);
  // try to recognize ethernet devices immediately 
    //usb_ether_curr_dev_local = usb_host_eth_scan(1);
  }
  else
  {
    printf("usb init failure\n");
    return  usb_stor_curr_dev_local;
  }

  if(usb_stor_curr_dev_local == 0)
  {
    if(usb_get_dev_index(0) != NULL )
      strcpy(argv[2],"0\0");
    else if(usb_get_dev_index(1) != NULL )
      strcpy(argv[2],"1\0");
    else if(usb_get_dev_index(2) != NULL )
      strcpy(argv[2],"2\0");
    else if(usb_get_dev_index(3) != NULL )
      strcpy(argv[2],"3\0");
    else
    {
      argv[2]=NULL;
      printf("No usb device found\n");
    }

    //set memory destination address to copy data from file 
    sprintf(argv[3],"%08x",destStr);
    //set data size
    #ifdef DEBUG
    printf("Set read size:%0x\n",size);
    #endif
    sprintf(argv[5],"0x%x",size);
  }
  else
  {
    printf("No usb device found\n");
    return -1;
  }
  #ifdef DEBUG
  if(argv[1]!=NULL)
    printf("Argv %s \n",argv[1]);
  if(argv[2]!=NULL)
    printf("Argv %s \n",argv[2]);
  if(argv[3]!=NULL)
    printf("Argv %s \n",argv[3]);
  if(argv[4]!=NULL)
    printf("Argv %s \n",argv[4]);
  if(argv[5]!=NULL)
    printf("Argv %s \n",argv[5]);
  if(argv[6]!=NULL)
    printf("Argv %s \n",argv[6]);
  #endif


  return  usb_stor_curr_dev_local;
}

/*************************************************************************/
/*				TIMER					*/
/*************************************************************************/
#define GET_BASEADDR_GPTIMER(id,base_addr) \
do { \
    switch (id)\
    {\
      case 1:\
        base_addr=GPTIMER1_BASE;\
      break;\
      case 2:\
        base_addr=GPTIMER2_BASE;\
      break;\
      case 3:\
        base_addr=GPTIMER3_BASE;\
      break;\
      case 4:\
        base_addr=GPTIMER4_BASE;\
      break;\
      case 5:\
        base_addr=GPTIMER5_BASE;\
      break;\
      case 6:\
        base_addr=GPTIMER6_BASE;\
      break;\
      case 7:\
        base_addr=GPTIMER7_BASE;\
      break;\
      case 8:\
        base_addr=GPTIMER8_BASE;\
      break;\
      case 9:\
        base_addr=GPTIMER9_BASE;\
      break;\
      case 10:\
        base_addr=GPTIMER10_BASE;\
      break;\
      case 11:\
        base_addr=GPTIMER11_BASE;\
      break;\
      case 13:\
        base_addr=GPTIMER13_BASE;\
      break;\
      default:\
        base_addr=0x00000000;\
	break;\
    }\
} while(0)

void configureTimer(UINT8 id,UINT32 tcrr)
{

   UINT32 base_addr=0x00000000;
   GET_BASEADDR_GPTIMER(id,base_addr);
#ifdef DEBUG1
   printf("Configure GPTIMER%d base address:0x%08x\n",id,base_addr);
#endif


    // timer off
    reg32s(base_addr, GPT_TCLR, 1, 0);
    // Sets true 1Khz rate w/ 32768Hz clock:  S 16.2.4.3 TRM D
    reg32w(base_addr, GPT_TPIR, 232000);
    reg32w(base_addr, GPT_TNIR, -768000);
    reg32w(base_addr, GPT_TLDR, tcrr);
    reg32w(base_addr, GPT_TCRR, tcrr);
    // clear int status bits
    reg32w(base_addr, GPT_TISR, ~0);
    // enable overflow int
    reg32w(base_addr, GPT_TIER, OVF_IT_FLAG);
    // dividisor = 100 -> 10Hz so it's visible
    reg32w(base_addr, GPT_TOCR, 0);
    reg32w(base_addr, GPT_TOWR, 100);
    // force 32K clock
    switch (id)
    {
      case 1:
        reg32s(0x48004c00, 0x40, 1, 0);
      break;
      case 2:
        reg32s(0x48004050, 0x40, 1, 0);
      break;
      case 3:
        reg32s(0x48004050, 0x40, 2, 0);
      break;
      case 4:
        reg32s(0x48004050, 0x40, 4, 0);
      break;

      default:
      break;
    }


}

void stopTimer(UINT8 id)
{
   UINT32 base_addr=0x00000000;
   GET_BASEADDR_GPTIMER(id,base_addr);
 
#ifdef DEBUG1
   printf("Stop GPTIMER%d base address:0x%08x\n",id,base_addr);
#endif
   // timer off
   reg32s(base_addr, GPT_TCLR, 1, 0);
   //reg32w(base_addr, GPT_TCLR, 0x0);

}


void startTimer(UINT8 id)
{
   UINT32 base_addr=0x00000000;
   GET_BASEADDR_GPTIMER(id,base_addr);
 
   // timer on
   reg32s(base_addr, GPT_TCLR, 3, 0x01);
   //reg32w(base_addr, GPT_TCLR,  0x1);
#ifdef DEBUG1
   printf("Start GPTIMER%d base address:0x%08x tclr reg:0x%08x \n",id,base_addr,reg32r(base_addr,GPT_TCLR));
#endif

}

UINT32 getTCRR(UINT8 id)
{
   UINT32 base_addr=0x00000000,reg;
 
   GET_BASEADDR_GPTIMER(id,base_addr);
   reg= reg32r(base_addr, GPT_TCRR);
#ifdef DEBUG1
   printf("getTCRR GPTIMER%d base address:0x%08x value:0x%08x\n",id,base_addr,reg);
#endif
   return reg;
}

void setTCRR(UINT8 id, UINT32 tcrr)
{
   UINT32 base_addr=0x00000000;
   GET_BASEADDR_GPTIMER(id,base_addr);
#ifdef DEBUG1
   printf("setTCRR GPTIMER%d base address:0x%08x\n",id,base_addr);
#endif
   reg32w(base_addr, GPT_TCRR, tcrr);
}
/*************************************************************************/
