#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

static void Hw_init(void);
static void Printf_test(void);

void nacho(void)
{
	Hw_init();

	putstr("Hello World!\n");

	Printf_test();

	uint32_t* i = 100;
	while(i--)
	{
		uint8_t ch = Hal_uart_get_char();
		Hal_uart_put_char(ch);
	}

}

static void Hw_init(void)
{
	Hal_uart_init();
}

static void Printf_test(void)
{
	debug_printf("%s\n", "Hello printf");
	debug_printf("%u\n", 777);
	debug_printf("%x\n", 777);
}

