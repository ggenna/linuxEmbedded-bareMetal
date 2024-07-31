#ifndef _UTILS_H_
#define _UTILS_H_

#include "user_type.h"
#define FLOAT2INTx1000(floatnum) (int) (floatnum*1000)

#define PIN5	138
#define THRESHOLDCH1 3
#define THRESHOLDCH2 12

void xferData(UINT32 *data, UINT32 numWord, UINT32 numWordTot );

void toVoltage(UINT32* fromADC,int length, float (*voltage)[2], float (*current)[2]);

int usbDeviceInit(char **argv,char *destStr,UINT32 size);

void configureTimer(UINT8 id,UINT32 tcrr);
void stopTimer(UINT8 id);
void startTimer(UINT8 id);
UINT32 getTCRR(UINT8 id);
void setTCRR(UINT8 id, UINT32 tcrr);

#endif //end _UTILS_H_




