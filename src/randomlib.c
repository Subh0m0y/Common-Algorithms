#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "xoroshiro128plus.h"

#define UINT32_MASK 0xFFFFFFFFULL


// The seeding functions.

/*
 * Initializes the PRNG. Uses the current time to seed
 * it. It's expected resolution is in microseconds.
 */
void init_rand(void)
{
    _seed_auto();
}

/*
 * Initializes the PRNG with a given seed.
 */
void seed(uint64_t x)
{
    _seed_with(x);
}

/*
 * Returns a random integer in the range 0 (inclusive)
 * and limit (exclusive). The integers generated are uniformly
 * distributed.
 */
uint64_t next_uint64(const uint64_t limit)
{
    return next() % limit;
}

/*
 * Returns a 32-bit unsigned integer.
 */
uint32_t next_uint32()
{
    // Generate 2 ints at a time out of one call to next()
    // This makes use of both halves of the 64 bits generated
    static uint32_t next_uint32_temp;
    static bool has_next_uint32 = false;

    uint32_t val;
    if (has_next_uint32) {
        val = next_uint32_temp;
    } else {
        uint64_t full = next();
        val = full >> 32;                                   // The upper half
        next_uint32_temp = (uint32_t) (full & UINT32_MASK); // The lower half
    }
    // quick flip
    has_next_uint32 ^= true;
    return val;
}

/*
 * Returns a boolean value. The expected probability of
 * both values is 50%.
 */
bool next_bool()
{
    // Sign test as per the recommendation
    // We check if the highest bit is on
    return (next() >> 63) & 1;
}

/*
 * Returns a uniformly distributed double between 0
 * (inclusive) and 1 (exclusive).
 */
double next_double()
{
    return ((double) next()) / ((double) UINT64_MAX);
}

/*
 * Returns a normally distributed double between -1.0
 * and +1.0
 */
double next_gaussian()
{
    static double next_gaussian;
    static bool has_next_gaussian = false;

    double val;
    if (has_next_gaussian) {
        val = next_gaussian;
    } else {
        double u, v, s;
        do {
            // Limit u and v to the range [-1, 1]
            u = next_double() * 2 - 1;
            v = next_double() * 2 - 1;
            s = u * u + v * v;
        } while(s > 1);
        double scale = sqrt(-2.0 * log(s) / s);
        next_gaussian = v * scale;
        val = u * scale;
    }
    // Quick flip
    has_next_gaussian ^= true;
    return val;
}
