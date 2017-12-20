#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "test.h"

bool check_uint64s_equal(const char * test, const uint64_t exp, const uint64_t act)
{
	if (exp == act) {
		printf("PASSED: %s\n", test);
		return true;
	} else {
		printf("FAILED: %s\nExpected:\t%"PRIu64"\nActual:\t\t%"PRIu64"\n", test, exp, act);
		return false;
	}
}