/************************************************/
/*						*/
/*	pwm_hw.h	     			*/	
/*						*/
/************************************************/


#ifndef _PWM_HW_H_
#define _PWM_HW_H_

#include "user_type.h"

typedef UINT8 pwm_hw_result_t;
#define PWM_HW_RES_OK	0 /*!< Successful operation*/
#define PWM_HW_RES_ERR	1 /*!< command failure */
#define PWM_HW_ERR_GPT_PWM_UNKNOWN 2 /*!< unknown GPTimer id*/
#define  PWM_HW_ERR_PRESCALE_RATIO_NOT_SUPPORTED 3 /*<! PRESCALE RATIO NOT SUPPORTED*/
#define PWM_HW_ERR_POLARITY_WRONG 4 /*!< Set wrong polarity value */ 
#define PWM_HW_ERR_DUTYCYCLE_VALUE_OUTOFRANGE  5 /*!< Duty cycle value not supporteDuty cycle value not supportedd*/
#define PWM_HW_ERR_SET_FREQ	6

 
#define GPT8   8   /*<! GPT8 timer id*/
#define GPT9   9   /*<! GPT8 timer id*/
#define GPT10 10   /*<! GPT8 timer id*/
#define GPT11 11   /*<! GPT8 timer id*/

#define LOW2HIGH_POLARITY 0  /*<! Set the waveform polarity low to high*/
#define HIGH2LOW_POLARITY 1  /*<! Set the waveform polarity high to low*/

/* **********************************************************************/
/**
  \fn pwm_hw_result_t pwm_hw_init(void) 
  Initialize PWM device  
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_init(UINT8 id);

/* **********************************************************************/
/**
  \fn pwm_hw_result_t pwm_hw_setFreq(UINT8 id,UINT32 freq, UINT8 duty) 
  Set frequyency and duty cycle for the output PWM waveform 
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_setFreq(UINT8 id,UINT32 freq, UINT8 duty);

/* **********************************************************************/
/** 
 \fn  pwm_hw_result_t pwm_hw_set_polarity(UINT8 id,UINT8 polarity)
  Set polarity  for the output PWM waveform 
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_set_polarity(UINT8 id,UINT8 polarity);

/* **********************************************************************/
/** 
 \fn  pwm_hw_result_t pwm_hw_set_prescale(UINT8 id,UINT8 polarity)
  Set prescale to enable a second prescale ratio for the GPTimer clock in 
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_set_prescale(UINT8 id,UINT8 prescale);



/* **********************************************************************/
/** 
 \fn  pwm_hw_result_t pwm_hw_stop(UINT8 id)
  Stop PWM waveform generation
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_stop(UINT8 id);


/* **********************************************************************/
/** 
 \fn  pwm_hw_result_t pwm_hw_start(UINT8 id)
  Start PWM waveform generation
*/
/* **********************************************************************/
pwm_hw_result_t pwm_hw_start(UINT8 id);


#endif  /*end _PWM_HW_H_ */

