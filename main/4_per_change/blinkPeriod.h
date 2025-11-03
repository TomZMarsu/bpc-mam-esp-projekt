#ifndef _BLINK_PERIOD_H
#define _BLINK_PERIOD_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

void initBlinkPeriod(int initialPeriodInMS);
void setBlinkPeriod(int periodInMS);
int getBlinkPeriod();
#endif