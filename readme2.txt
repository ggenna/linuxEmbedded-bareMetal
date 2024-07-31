Nel file: fileUsbI.txt
sono necessari 4 parametri

freq num_samples duration[sec] num_pwm_update 

Ecco alcune variabili per la compilazione condizionale:

ADC_BOARD:  abilita l'attesa del segnale DataReady durante l'acquisizione.

PRINTACQ: ablita la stampa a video dei dati acquisiti dall ADC.

STOREDATAIN: abilita la scrittura su file dei dati acquisiti dal dispositivo ADC. I dati sono salvati in file di nome DataInxxx.txt in formato csv
