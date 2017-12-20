#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"

int main(int argc, char const *argv[])
{
	if (argc < 3) {
		printf("USAGE: gcd <int1> <int1> [<int3> ... <intn>]\n"
				"NOTE: Only positive integers are allowed.");
	}
	int index = 1;
	uint64_t divisor = 0;
	while (index < argc) {
		char const * arg = argv[index];
		long long value = strtoll(arg, NULL, 0);
		if (value < 0) {
			printf("Only positive integers please!\n");
			exit(EXIT_FAILURE);
		}
		divisor = gcd((uint64_t) value, divisor);
		index++;
	}
	printf("%"PRIu64"\n", divisor);
	return EXIT_SUCCESS;
}