#include "stdint.h"
#include "armcpu.h"
#include "task.h"
#include "switch.h"

extern KernelTcb_t* sCurrent_tcb;
extern KernelTcb_t* sNext_tcb;

__attribute__ ((naked)) void Kernel_task_context_switching(void)
{
	__asm__ ("B Save_context");
	__asm__ ("B Restore_context");
}

__attribute__ ((naked)) void Save_context(void)
{
	__asm__ ("PUSH {lr}");
	__asm__ ("PUSH {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}");
	__asm__ ("MRS r0, cpsr");
	__asm__ ("PUSH {r0}");

	__asm__ ("LDR r0, =sCurrent_tcb");
	__asm__ ("LDR r0, [r0]");
	__asm__ ("STMIA r0!, {sp}");
}

__attribute__ ((naked)) void Restore_context(void)
{
	__asm__ ("LDR r0, =sNext_tcb");
	__asm__ ("LDR r0, [r0]");
	__asm__ ("LDMIA r0!, {sp}");

	__asm__ ("POP {r0}");
	__asm__ ("MSR cpsr, r0");
	__asm__ ("POP {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}");
	__asm__ ("POP {pc}");
}
