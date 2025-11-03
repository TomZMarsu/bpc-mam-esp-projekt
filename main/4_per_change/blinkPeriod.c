#include "blinkPeriod.h"

static SemaphoreHandle_t blinkPeriodMutex;
static int blinkPeriod;

void initBlinkPeriod(int initialPeriodInMS) {
    blinkPeriodMutex = xSemaphoreCreateMutex();
    setBlinkPeriod(initialPeriodInMS);
}
void setBlinkPeriod(int periodInMS) {
    xSemaphoreTake(blinkPeriodMutex, portMAX_DELAY);
    blinkPeriod = periodInMS;
    xSemaphoreGive(blinkPeriodMutex);
}
int getBlinkPeriod() {
    int period_to_return = 0;

    xSemaphoreTake(blinkPeriodMutex, portMAX_DELAY);
    period_to_return = blinkPeriod;
    xSemaphoreGive(blinkPeriodMutex);

    return period_to_return;
}