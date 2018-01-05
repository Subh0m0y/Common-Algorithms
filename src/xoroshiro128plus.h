#ifndef XORO_SHIRO_128_PLUS
#define XORO_SHIRO_128_PLUS

#include <inttypes.h>

/* Only expose the method that is relevant */

/*
 * Automatically initializes the seed vector for the xoroshiro128+
 * PRNG, using a part of the current time (in microseconds) and
 * a seed scrambler.
 */
void _seed_auto(void);

/*
 * Initializes the seed vector with a starting value. This is useful
 * for debugging when reproducible scenarios are desirable.
 */
void _seed_with(const uint64_t x);

/*
 * Returns 64 randomly generated bits. 
 */
uint64_t next(void);

#endif