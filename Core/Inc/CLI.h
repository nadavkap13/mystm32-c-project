#ifndef INC_CLI_H_
#define INC_CLI_H_

typedef void (*HandlerFunc)(void*,char*);

void initCLI();
void cmdLed(void*obj,char*params);
void cmdLedoff(void* obj,char* params);
void cmdLedBlink(void* obj,char* params);
void cmdLedBright(void* obj,char* params);
void cmdClockTick(void* obj,char* params);
void cmdClockTime(void* obj,char* params);
void cmdBuzzerStartPlay(void* obj,char* params);
void cmdBuzzerStopPlay(void* obj,char* params);
void cmdGetTempAndHumidity(void* obj,char* params);
#endif /* INC_CLI_H_ */
