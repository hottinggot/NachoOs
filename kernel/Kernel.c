#include "stdint.h"
#include "Kernel.h"

void Kernel_start(void)
{
	Kernel_task_start();
}

void Kernel_yield(void)
{
	Kernel_task_scheduler();
}
