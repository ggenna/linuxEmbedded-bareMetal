
#include "pbits.h"
#include "omap3-system.h"
#include "omap3-intc.h"
#include "omap3-gptimer.h"

#include "var.h"
#include "pwm_drv.h"
#include "spi_drv.h"
#include "ADC.h"
#include "FFT.h"
#include <string.h>
#include <command.h>
#include "extern_func.h"
#include "math.h"
#include "utils.h"

/* macros */
#define TWO_PI (6.2831853071795864769252867665590057683943L)
#define PWMFREQ 200000
#define FREQ_GPT 32768
//#define DEBUG_MAIN // per abilitare le stampe di debug

/* Create output table*/
#define D_OUTFILE
typedef struct{
	int freq;
	float mz;
	float fz;

} table;



#ifdef USBTEST 
static int usb_stor_curr_dev = -1; /* current device */
static int usb_ether_curr_dev = -1; /* current ethernet device */
#endif //USBTEST
//extern UINT32 incomingDataMCSPI4[MAX_DATA_BYTE];
//extern UINT32 incomingDataMCSPI3[MAX_DATA_BYTE];


void gptimer1_handler(int id) {

	static int blink = 0;

	if (blink & (1<<2)){
		LEDS_OFF(LED0);
		LEDS_ON(LED1);
	} 
	else{
		LEDS_ON(LED0);
		LEDS_OFF(LED1);
	}
	blink++;
	// clear ints
	reg32w(GPTIMER1_BASE, GPT_TISR, ~0);
}

int main(int argc, char **argv) {

  UINT8 res,status;
  UINT32 local[200],i,j,frequency,tcrr,tcrr_i;
  int y,s,fid,Ns,N_int_max,N_int,Nduty_step,Ns_step,iNs;
  result_spi_t res_spi;
  char *argvLocal[7]={"0","usb","005","8030d180","fileUsbI1234567890.txt","000010"}, *outputstring;

  float Ts,duty,IfftI,IfftR,modulusV,modulusI,modulusz,phaseV,phaseI,phasez,sen0,idduty,VfftR,VfftI;
  float (*v)[2];           /* pointer to time-domain samples */
  float (*vfft)[2];        /* pointer to frequency-domain samples */
  float (*in)[2];          /* pointer to time-domain samples */
  float (*infft)[2];       /* pointer to frequency-domain samples */


  //neon_init();
  app_startup(argv); 
     


// INIT PWM devices  
#ifdef PWMTEST
  frequency = PWMFREQ;	
  res=pwmInit(GPT11);
  if(res != PWM_RES_OK)
    printf("Can't initialize PWM device, error:0x%08x\n",res);
  res=pwmInit(GPT10);
  if(res != PWM_RES_OK)
    printf("Can't initialize PWM device, error:0x%08x\n",res);
#endif  //end PWMTEST    

//INIT MCSPI devices
#ifdef MCSPITEST
  res_spi = spiInit(MCSPI4,0,SPI_MASTER_MODE,XFER_RECEIVE_ONLY,SPI_FREQ_24MHZ);
  if(res_spi != SPI_RES_OK)      
    printf("Can't configure MCSPI4 device, error:0x%08x\n",res_spi);
  res_spi = spi_configXfer(MCSPI4, 0);
  if(res_spi != SPI_RES_OK)      
    printf("Can't configure transfer on MCSPI4 device ch 0, error:0x%08x\n",res_spi);
#endif //end MCSPITEST

#ifdef USBTEST 
  char * inputstring,*righe;
  int stringSize=5000,righeSize=60;
  inputstring = (char *) malloc(sizeof(char)*stringSize);
  if(inputstring==NULL)
    printf("ERROR: MEMALLOC failed\n");
  righe = (char *) malloc(sizeof(char)*righeSize);
  if(inputstring==NULL)
    printf("ERROR: MEMALLOC failed\n");
#ifdef DEBUG
  printf("(Re)start USB...\n");
#endif   
  //Set file name
  strcpy(argvLocal[4],"fileUsbI.txt");
  //Init usb device
  do
  {
    usb_stor_curr_dev =  usbDeviceInit(argvLocal,inputstring,stringSize-1);  
    if(usb_stor_curr_dev!=0)
      printf("!!!!!!!!!!!!!!!!\nNo USB device found\n!!!!!!!!!!!!!!!!\n");
  }while(usb_stor_curr_dev!=0);
 
   if(usb_stor_curr_dev==0)
   {  
     //read file
     do_fat_fsload(NULL, 0,8, argvLocal);
     #ifdef DEBUG1
     printf("\ndata read from file,string addr:0x%08x\n", inputstring);
     //printf("string_input:\n%s\n",inputstring);
     #endif
   }
   
  int z=0,c=0;
  
  memset(righe,'0',righeSize);        
  while (inputstring[z]!='\n')
  {
   righe[c] =inputstring[z];
   c++;
   z++;
  }
  //if(c<stringSize)
  if(c<righeSize)
  {
    righe[c]='\n';
    sscanf (righe,"%d ",&y);
  }
  else
    y=0;
  #ifdef DEBUG
  printf("number of rows:%d\n", y);
  #endif
  printf("free inputstring\n");
  //if(inputstring!=NULL) 
  //  free(inputstring);
  //y= number of rows; 30 = number of characters for each row
  stringSize = y*30;
  //inputstring = (char *) malloc(sizeof(char)*stringSize);
  if(inputstring==NULL)
    printf("ERROR: MEMALLOC failed\n");
  //Init usb device
  printf("reading file...\n");
  usb_stor_curr_dev =  usbDeviceInit(argvLocal,inputstring,stringSize-1);  
  if(usb_stor_curr_dev==0)
  {  
    //read file
    do_fat_fsload(NULL, 0,8, argvLocal);
    #ifdef DEBUG
    printf("\ndata read from file,string addr:0x%08x\n", inputstring);
    //printf("string_input:\n%s\n",inputstring);
    #endif
  }

  int freq[y],time,samples[y],pwmUpdate[y];
  table tableimp[y];
  float Tp[y];
  UINT16 updateDuty; 


/*READ CONFIGURATION DATA */
  z++;
  for(i=0; i<y; i++)
  {
    c=0;
    while (inputstring[z]!='\n')
    {
      righe[c] =inputstring[z];
      c++;
      z++;
    }
		
    if(c<righeSize)
    {
      righe[c]='\n';
    }
    sscanf (righe," %d  %d  %d %d",&freq[i],&samples[i],&time,&pwmUpdate[i]);
    Tp[i] = (float) time*1.0;
#ifdef DEBUG
    printf ("righe:%s\n",righe);
    printf ("frequency[%d] = %d; ",i, freq[i]);
    printf ("samples[%d] = %d; ",i, samples[i]);
    printf ("Time[%d] = %d; ",i, (int)Tp[i]);
    printf ("pwm update[%d] = %d\n; ",i, pwmUpdate[i]);
#endif
    z++;
  }

   // free memory
  if(inputstring!=NULL)
    free(inputstring);
  if(righe!=NULL)
    free(righe);
#endif //USBTEST


  for (s=0;s<y; s++)
  {
    #ifdef DEBUG
    printf("Start loop, index:%d\n",s);
    #endif 
    idduty=0;
    //Ns =  samples[s];
    N_int_max = (int) Tp[s]/T_DATAREADY;

    if( N_int_max < samples[s] )
      Ns = N_int_max;
    else
      Ns = samples[s];

    //Calculate number of change for PWM duty cycle
    if( pwmUpdate[s] >  N_int_max  )
      updateDuty = N_int_max;
    else
      updateDuty = pwmUpdate[s];
  
    if(Ns>updateDuty)
      N_int = Ns;
    else
      N_int = updateDuty;
   
     Ns_step = N_int/Ns;
     Nduty_step = N_int/updateDuty;     

    /* calculate sampling time*/
    //N_period=1.0/Freq[s];
    Ts = Tp[s]/((float)updateDuty)*freq[s];
    //Calculate GPT timer period    
    tcrr_i = ((UINT32) (Tp[s] * FREQ_GPT / N_int)) ;
    tcrr = 0xffffffff - ((UINT32) (Tp[s] * FREQ_GPT )) ;


#ifdef DEBUG
    printf (" Ts = %d [x1000] \n", FLOAT2INTx1000(Ts));
    printf (" Ns = %d \n", Ns);
    printf ("timer period:%u [x1000], tcrr reg:0x%08x,N_int:%d,Ns_step:%d,Nduty_step:%d \n",tcrr/FREQ_GPT,tcrr,N_int,Ns_step,Nduty_step);
#endif
   
    //allocate memory
    UINT32 *incomingDataMCSPI4=(UINT32*) malloc(sizeof(UINT32)*2*Ns); 
    if(incomingDataMCSPI4 == NULL)
      printf("ERROR: MEMALLOC failed\n");		


    configureTimer(1/*GP1TIMER*/,tcrr);


  
//Acquisition cycle
#ifdef PWMTEST
    idduty=0;
    iNs=0;
    int cnt=0;
    int indexDuty=0;
    //start timer
    UINT8 dutyVec[updateDuty];
    for(i=0;i<updateDuty;i++)    
    {
      sen0 =   sin( TWO_PI * Ts * (float)i );
      dutyVec[i]  = (UINT8)(100.0 * ((1.0+ sen0)/2.0));
      #ifdef DEBUG1
        printf("index:%d sen0:%d [x1000],sin arg:%d [x1000], duty:%d [x1000], Ts [x1000]:%d\n",i,FLOAT2INTx1000(sen0),FLOAT2INTx1000( TWO_PI * Ts * (float)i),FLOAT2INTx1000(dutyVec[i]),FLOAT2INTx1000(Ts));
      #endif
    }

    for(i=0;i<N_int;i++)
    {
      //start timer
      startTimer(1/*GPTIMER1*/);


      if ( i == idduty)
      {
        if (freq[s] < 5)
        {
           frequency = PWMFREQ;
	   res = pwm_configure(GPT11,frequency,dutyVec[indexDuty++],LOW2HIGH_POLARITY); 
	   if(res != PWM_RES_OK)
	     printf("Can't configure PWM device, error:0x%08x.Duty:%d,Freq:%d\n",res,FLOAT2INTx1000(duty),frequency);
	   res = pwm_start(GPT11);
	   if(res != PWM_RES_OK)
	     printf("Can't start PWM device, error:0x%08x\n",res);
	   else
           {
             #ifdef DEBUG1
	     printf("PWM GPT11 device started\n");
             #endif
           }
	}
	else
        {
           frequency = PWMFREQ;
	   res = pwm_configure(GPT10,frequency,dutyVec[indexDuty++],LOW2HIGH_POLARITY); 
	   if(res != PWM_RES_OK)
	     printf("Can't configure PWM device, error:0x%08x.Duty:%d,Freq:%d\n",res,duty,frequency);
	   res = pwm_start(GPT10);
	   if(res != PWM_RES_OK)
	     printf("Can't start PWM device, error:0x%08x\n",res);
	   else
           {
             #ifdef DEBUG1
	     printf("PWM GPT10 device started\n");
             #endif
           }
	 }
	 idduty+=Nduty_step;
      }//end idduty
#endif
#if MCSPITEST
    
    if(i==iNs)
    {
      //spi xfer
      //param1:  incoming data address
      //param2:  number of word to transfer for each data ready cycle
      //param3:  total of number of words 
      xferData(&incomingDataMCSPI4[cnt],2,2);
      cnt +=2;
      iNs+=Ns_step;
    } //end iNs
    //wait
    //while( getTCRR(1/*GPTIMER1*/) != 0xFFFFFFFF)
    while( getTCRR(1/*GPTIMER1*/) < (tcrr+(i+1)*tcrr_i)  )
    {
      if(  getTCRR(1/*GPTIMER1*/) == 0 )
      {
        printf("Error: timeout loop\n");
        break;
      } 
    }
    //update GPT timer
    //setTCRR(1/*GPTIMER1*/, tcrr);
#endif  //END MCSPITEST
    }//end Acquisition cycle


    stopTimer(1/*GPTIMER1*/);

    #ifdef DEBUG1				
    printf("...transfer complete\n");
    printf("incomingDataMCSPI4:0x%08x\n", incomingDataMCSPI4);
    dump(incomingDataMCSPI4,2*Ns);
    #endif

    res = pwm_configure(GPT11,frequency,50,LOW2HIGH_POLARITY);  
    if(res != PWM_RES_OK)
      printf("Can't configure PWM device, error:0x%08x.Duty:%d,Freq:%d\n",res,50,frequency);
    res = pwm_configure(GPT10,frequency,50,LOW2HIGH_POLARITY); 
    if(res != PWM_RES_OK)
      printf("Can't configure PWM device, error:0x%08x.Duty:%d,Freq:%d\n",res,50,frequency);
    
    #ifdef DEBUG
    printf("Start FFT\n");
    #endif
    /* Allocate voltage and current arrays memory. */
    //v = malloc( Ns * sizeof(float));
    //in = malloc( Ns * sizeof(float));
    v = malloc(2 * Ns * sizeof(float));
    in = malloc(2 * Ns * sizeof(float));
    /* Allocate FFT results arrays memory. */
    vfft = malloc(8 * samples[s] * sizeof(float));
    infft = malloc(8 * samples[s] * sizeof(float));
   //float vfft[4*Ns][4*Ns];    
   //float infft[4*Ns][4*Ns];

    toVoltage(incomingDataMCSPI4,Ns,v,in);

#ifdef DEBUG_MAIN
  int index;
  for(index=0;index<10;index++)
  {
    printf (" VR = %d [mV] ", FLOAT2INTx1000(v[index][0]));
    printf (" VI = %d [mV] \n", FLOAT2INTx1000(v[index][1]));
    //printf (" IR = %d [mA] \n",FLOAT2INTx1000(in[index][0]));
    //printf (" II = %d [mA] \n",FLOAT2INTx1000(in[index][1]));
  }
#endif
    //free memory
    free(incomingDataMCSPI4);

    /*Calculate FFT of voltage signal*/
    fft(Ns,  v, vfft);
    /*Calculate FFT of current signal*/
    fft(Ns,  in, infft);

     /* Calculate index of nominal frequency */
     //fid = ( (samples[s])/Ns);
     fid = round(Tp[s] * freq[s]);
#ifdef DEBUG_MAIN		     
     for(index=95;index<105;index++) 
     {
       printf (" vfftR = %d ", FLOAT2INTx1000(vfft[index][0]));
       printf (" vfftI = %d \n", FLOAT2INTx1000(vfft[index][1]));

     }
     printf ( " fid = %d \n", fid);
#endif

      /* Real and Imaginary part of  FFT of voltage signal at position fid of vfft array. */
     //VfftR = vfft[fid][0];
     //VfftI = vfft[fid][1];
     VfftR = vfft[fid][0]/ Ns ;
     VfftI = vfft[fid][1]/ Ns ;

     /* Real and Imaginary part of  FFT of current signal at position fid of infft array. */
     IfftR = infft[fid][0]/Ns;
     IfftI = infft[fid][1]/Ns;
#ifdef DEBUG
     printf( " Vfft R = %d [mV] \n",FLOAT2INTx1000(VfftR));
     printf( " Vfft I = %d [mV] \n", FLOAT2INTx1000(VfftI));
     printf( " Ifft R = %d [mA] \n",FLOAT2INTx1000(IfftR));
     printf( " Ifft I = %d [mA]\n",FLOAT2INTx1000(IfftI));
#endif

     /* Calculate modulus  and phase of signals */
     modulusV = 2 * sqrt( (VfftR * VfftR) + (VfftI *VfftI));
     modulusI = 2 * sqrt( (IfftR * IfftR) + (IfftI *IfftI));


     phaseV = atan2(VfftI,VfftR);
     phaseI = atan2(IfftI,IfftR);

#ifdef DEBUG
     printf( " modulusV = %d\t modulusI = %d \n", FLOAT2INTx1000(modulusV),FLOAT2INTx1000(modulusI));
     printf( " phaseV = %d\tphaseI = %d\n ", FLOAT2INTx1000(phaseV),FLOAT2INTx1000(phaseI));
#endif


     /* Calculate modulus and phase of equivalent impedance*/
     modulusz = (modulusV/ modulusI);
     phasez = phaseV - phaseI;
     /* Store all results into an array */
     tableimp[s].freq = freq[s];
     tableimp[s].mz   = modulusz;
     tableimp[s].fz   = phasez;
#ifdef DEBUG  
     printf( " freq = %d ", freq[s]);
     printf( " modulusz = %d [x1000] ", FLOAT2INTx1000(modulusz));
     printf( " phasez = %d [x1000] \n", FLOAT2INTx1000(phasez));
#endif

#ifdef STOREDATAIN
  int len=100;
  char riga[len];
  //free(outputstring);
  outputstring = (char *) malloc(sizeof(char)*Ns*len);
#if 1
  strcpy(outputstring,"VR [mV]; IR [mV];\n");
  for( i = 0 ; i < Ns ; i++ ) 
  {
    memset(riga,"0",len);
    sprintf (riga, "%d;%d;\n", FLOAT2INTx1000(v[i][0]),FLOAT2INTx1000(in[i][0]));
    strcat (outputstring,riga);
  }
#endif	
#ifdef USBTEST 
  //set data size
  stringSize=strlen(outputstring);
  //Set file name
  strcpy(argvLocal[4],"DataIn_");
  sprintf(riga,"%d",s);
  strcat(argvLocal[4],riga);
  strcat(argvLocal[4],".csv");
  //set memory source address to copy in file 
  usb_stor_curr_dev =  usbDeviceInit(argvLocal,outputstring,stringSize);  
  //write file in usb device 
  if(usb_stor_curr_dev==0)
    do_fat_fswrite(NULL, 0,8, argvLocal);
#endif //end USBTEST
   if(outputstring!=NULL) 
     free(outputstring);

#endif //end STOREDATAIN


    /* Free Memory*/
    if(v!=NULL)
      free(v);
    if(in!=NULL)
      free(in);

    if(vfft!=NULL)
      free(vfft);
    if(infft!=NULL)
      free(infft);

#ifdef DEBUG
    printf( "End loop \n");
#endif
}

#ifdef USBTEST 
#ifdef DEBUG
  printf( "Writring result... \n");
#endif
  //Set file name
  strcpy(argvLocal[4],"fileUsbO.txt");

  printf("y:%d\n",y);
  int n,len=50;
  char riga[len];
  //char * outputstring =(char*) malloc(sizeof(char)*len);
  n=y*len+1;
  outputstring = (char *) malloc(sizeof(char)*y*len);
  n=0;

  strcpy(outputstring,"freq; moduloz [x1000];fasez [x1000];\n");
  for( i = 0 ; i < y ; i++ ) 
  {
    memset(riga,"0",len);
    n=sprintf (riga, "%d;%d;%d;\n", tableimp[i].freq, FLOAT2INTx1000(tableimp[i].mz), FLOAT2INTx1000(tableimp[i].fz));
    strcat (outputstring,riga);
  }	

  //set data size
  stringSize=strlen(outputstring);
  //set memory source address to copy in file 
  usb_stor_curr_dev =  usbDeviceInit(argvLocal,outputstring,stringSize);  
  //write file in usb device 
  if(usb_stor_curr_dev==0)
    do_fat_fswrite(NULL, 0,8, argvLocal);
#endif  //end USBTEST
   if(outputstring!=NULL)  
     free(outputstring);	
	
   printf("\n******************************************************\n");
   printf("end\n");         
   while(1);
   return 0;
}
