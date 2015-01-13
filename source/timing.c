#include "timing.h"

/*
* GetSystemTick function by xerpi
*/
u64 getSystemTick() {
	register unsigned long lo64 asm ("r0");
	register unsigned long hi64 asm ("r1");
	asm volatile ( "SVC 0x28" : "=r"(lo64), "=r"(hi64) );
	return ((uint64_t)hi64<<32) | (uint64_t)lo64;
}