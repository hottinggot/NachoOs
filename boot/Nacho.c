#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"
#include "stdlib.h"
#include "task.h"
#include "Kernel.h"
#include "event.h"

static void Hw_init(void);
static void Printf_test(void);
static void Timer_test(void);
static void Kernel_init(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

void nacho(void)
{
	Hw_init();

	putstr("Hello World!\n");

	Printf_test();
	//Timer_test();
	//
	
	Kernel_init();

	uint32_t* i = 100;
	while(i--)
	{
		uint8_t ch = Hal_uart_get_char();
		Hal_uart_put_char(ch);
	}

	while(1);

}

static void Hw_init(void)
{
	Hal_interrupt_init();
	Hal_timer_init();
	Hal_uart_init();
}

static void Printf_test(void)
{
	uint32_t *sysctrl0 = (uint32_t*)0x10001000;
	debug_printf("%s\n", "Hello printf");
	debug_printf("%u\n", 777);
	debug_printf("%x\n", 777);
	debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}

static void Timer_test(void)
{
	while(1)
	{
		debug_printf("current count: %u\n", Hal_timer_get_1ms_counter());
		delay(1000);
	}
}

static void Kernel_init(void)
{
	uint32_t taskId;

	Kernel_task_init();
	Kernel_event_flag_init();

	taskId = Kernel_task_create(User_task0);
	if(taskId == NOT_ENOUGH_TASK_NUM) {
		putstr("Task0 creation fail\n");
	}
/*
	taskId = Kernel_task_create(User_task1);
	if(taskId == NOT_ENOUGH_TASK_NUM) {
                putstr("Task1 creation fail\n");
        }

	taskId = Kernel_task_create(User_task2);
	if(taskId == NOT_ENOUGH_TASK_NUM) {
                putstr("Task2 creation fail\n");
        }
*/	

	Kernel_start();
}

void User_task0(void)
{
	uint32_t local = 0;
	
	debug_printf("User Task #0\n");

	while(1) {
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_UartIn);
		switch(handle_event) 
		{
			case KernelEventFlag_UartIn :
				debug_printf("\nEvent Handled\n");
				break;
		}
		Kernel_yield();

	}
}

/*
void User_task1(void)
{
	debug_printf("User Task #1\n");
	while(1) {
		debug_printf("User Task #1\n");
		Kernel_yield();
	}
}

void User_task2(void)
{
	debug_printf("User Task #2\n");
	while(1){
		debug_printf("User Task #2\n");
		Kernel_yield();
	}
}
*/
