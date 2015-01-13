#include "minlib.h"

void swap(s16 *n1, s16 *n2) {
	*n1 ^= *n2;
	*n2 ^= *n1;
	*n1 ^= *n2;
}

s16 absVal(s16 n) {
	if (n < 0) return -n;
	return n;
}