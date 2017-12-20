#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"
#include "test.h"

/*
 * Unit Tests
 * ----------
 * 1. gcd(42, 56) = 14
 * 2. gcd(461952, 116298) = 18
 * 3. gcd(7966496, 314080416) = 32
 * 4. gcd(24826148, 45296490) = 526
 * 5. gcd(12, 0) = 12
 * 6. gcd(0, 0) = 0
 * 7. gcd(0, 9) = 9
 */

void test_gcd()
{
	int count = 0;
	int total = 0;
	++total;
	count += check_uint64s_equal("gcd(42, 56) = 14",
			14,	gcd(42, 56)) ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(461952, 116298) = 18",
			18, gcd(461952, 116298))  ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(7966496, 314080416) = 32",
			32, gcd(7966496, 314080416))  ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(24826148, 45296490) = 526",
			526, gcd(24826148, 45296490))  ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(12, 0) = 12",
			12, gcd(12, 0))  ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(0, 0) = 0",
			0, gcd(0, 0))  ? 1 : 0;
	++total;
	count += check_uint64s_equal("gcd(0, 9) = 9",
			9, gcd(0, 9))  ? 1 : 0;

	printf("%d out of %d tests passed.\n", count, total);

	if (count != total) { exit(EXIT_FAILURE); }
}

int main(int argc, char const *argv[])
{
	test_gcd();
	return 0;
}