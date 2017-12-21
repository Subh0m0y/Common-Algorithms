#include <inttypes.h>
#include "gcd.h"

uint64_t gcd(uint64_t p, uint64_t q)
{
	if (p == 0) { return q; }
	if (q == 0) { return p; }
	uint64_t r = p % q;
	while (r != 0) {
		p = q;
		q = r;
		r = p % q;
	}
	return q;
}