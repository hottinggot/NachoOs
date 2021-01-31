#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"
#include "stdlib.h"

static void Hw_init(void);
static void Printf_test(void);
static void Timer_test(void);

void nacho(void)
{
	Hw_init();

	putstr("Hello World!\n");

	Printf_test();
	Timer_test();

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
