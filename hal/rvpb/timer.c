#include "stdint.h"
#include "timer.h"
#include "HalTimer.h"
#include "HalInterrupt.h"

extern volatile Timer_t* Timer;

static void interrupt_handler(void);

static uint32_t internal_1ms_counter;

void Hal_timer_init(void)
{
	Timer->timerxcontrol.bits.TimerEn = 0;
	Timer->timerxcontrol.bits.TimerMode = 0;
	Timer->timerxcontrol.bits.OneShot = 0;
	Timer->timerxcontrol.bits.TimerSize = 0;
	Timer->timerxcontrol.bits.TimerPre = 0;
	Timer->timerxcontrol.bits.IntEnable = 1;
	Timer->timerxload = 0;
	Timer->tierxvalue = 0xFFFFFFFF;


