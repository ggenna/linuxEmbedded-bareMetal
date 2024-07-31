/************************************************/
/*						*/
/*	pwm_drv.h		     			*/	
/*						*/
/************************************************/


#ifndef _PWM__DRV_H_
#define _PWM_DRV_H_

#include "user_type.h"

/** \def PWM TYPE RESUL  */
typedef UINT8 pwm_result_t;
#define PWM_RES_OK		0 /*!< Successful operation*/
#define PWM_RES_ERR		1 /*!< command failure */
#define PWM_ERR_INIT_DEVICE 	2 /*!< init device failure */
#define PWM_ERR_SET_FREQ 	3 /*!< set frequency or duty cycle failure */
#define PWM_ERR_SET_POLARITY 	4 /*!< set polarity failure */
#define PWM_ERR_START	 	5 /*!< start PWM device failure */
#define PWM_ERR_STOP	 	6 /*!< stop PWM device failure */
#define PWM_ERR_DUTYCYCLE_VALUE_NOT_SUPPORTED 7 /*!< Duty cycle value out of range*/

#define GPT8   8   /*<! GPT8 timer id*/
#define GPT9   9   /*<! GPT8 timer id*/
#define GPT10 10   /*<! GPT8 timer id*/
#define GPT11 11   /*<! GPT8 timer id*/

#define LOW2HIGH_POLARITY 0  /*<! Set the waveform polarity low to high*/
#define HIGH2LOW_POLARITY 1  /*<! Set the waveform polarity high to low*/


/* **********************************************************************/
/**
  \fn pwm_result_t pwm_init(UINT8 id)
  initialize device, set the pin mux in order to enable PWM output pin and
  set clock in for GPTimer 10 and 11.
   \param UINT8 id   		select GPTimer
*/
/* **********************************************************************/
pwm_result_t pwmInit(UINT8 id);

 
/* **********************************************************************/
/**
   \fn pwm_result_t pwm_configure(UINT8 id,UINT32 freq, UINT8 duty, UINT8 polarity)
   Set Frequency, duty cycle and polarity in the selected GPTimer 
   \param UINT8 id   		select GPTimer
   \param UINT32 freq  		Frequency [Hz] for the output waveform
   \param UINT32 duty		duty cycle [%] for the outupt waveform
   \param UINT32 polarity	Polarity (low to high, high to low) for the output waveform				
*/
/* **********************************************************************/
pwm_result_t pwm_configure(UINT8 id,UINT32 freq, UINT8 duty, UINT8 polarity);

/* **********************************************************************/
/**
  \fn pwm_result_t pwm_start(UINT8 id)
  Start PWM device to generate wafeform
  \param UINT8 id   		select GPTimer
*/
/* **********************************************************************/
pwm_result_t pwm_start(UINT8 id);

/* **********************************************************************/
/**
  \fn pwm_result_t pwm_stop(UINT8 id)
  Stop PWM device to generate wafeform
  \param UINT8 id   		select GPTimer
*/
/* **********************************************************************/
pwm_result_t pwm_stop(UINT8 id);


#if 0
/* **********************************************************************/
/**
  \fn pwm_result_t pwm_result_t pwm_open(UINT8 deviceId) 
 Select PWM device 
*/
/* **********************************************************************/
pwm_result_t pwm_open(UINT8 deviceId);


/* **********************************************************************/
/**
  \fn pwm_result_t pwm_result_t pwm_close(UINT8 deviceId)
  Release PWM device
*/
/* **********************************************************************/
pwm_result_t pwm_close(UINT8 deviceId);
#endif


#endif  /* _PWM_H_ */

