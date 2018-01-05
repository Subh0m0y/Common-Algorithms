// Original and permanent link: http://xoroshiro.di.unimi.it/xoroshiro128plus.c
/*  Written in 2016 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>
#include <sys/time.h>

/* This is the successor to xorshift128+. It is the fastest full-period
   generator passing BigCrush without systematic failures, but due to the
   relatively short period it is acceptable only for applications with a
   mild amount of parallelism; otherwise, use a xorshift1024* generator.

   Beside passing BigCrush, this generator passes the PractRand test suite
   up to (and included) 16TB, with the exception of binary rank tests, as
   the lowest bit of this generator is an LFSR of degree 128. The next bit
   can be described by an LFSR of degree 8256, but in the long run it will
   fail linearity tests, too. The other bits needs a much higher degree to
   be represented as LFSRs.

   We suggest to use a sign test to extract a random Boolean value, and
   right shifts to extract subsets of bits.

   Note that the generator uses a simulated rotate operation, which most C
   compilers will turn into a single instruction. In Java, you can use
   Long.rotateLeft(). In languages that do not make low-level rotation
   instructions accessible xorshift128+ could be faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

uint64_t s[2];

////////////////////////////////////////////////////////////////////////
/* Modifications by Subhomoy Haldar (github.com/Subh0m0y) start here. */

// As per the recommendation by the original authors - David Blackman and
// Sebastiano Vigna, we shall use two iterations of a seeded splitmix64
// generator (written by Sebastiano Vigna) and use its output to seed this
// program's seed vector.

// Original and permanent link: http://xoroshiro.di.unimi.it/splitmix64.c

static uint64_t splitmix64next(const uint64_t x) {
    uint64_t z = (x + 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

const uint64_t SEED_SCRAMBLER = 0x37bc7dd1f3339a5fULL;

static uint64_t time_based_x(void) {
    // Obtain the (relative, partial) time information
    // in microseconds
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    uint64_t value = currentTime.tv_usec;
    // Combine and generate the seed.
    uint64_t x = (value << 32) | value;
    x ^= SEED_SCRAMBLER;
    return x;
}

void _seed_with(const uint64_t x) {
    s[0] = splitmix64next(x);
    s[1] = splitmix64next(s[0]);
}

void _seed_auto(void) {
    _seed_with(time_based_x());
}

/* Modifications by Subhomoy Haldar end here. */
////////////////////////////////////////////////

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

uint64_t next(void) {
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    const uint64_t result = s0 + s1;

    s1 ^= s0;
    s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
    s[1] = rotl(s1, 36); // c

    return result;
}


/* This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */

void jump(void) {
    static const uint64_t JUMP[] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
        for(int b = 0; b < 64; b++) {
            if (JUMP[i] & UINT64_C(1) << b) {
                s0 ^= s[0];
                s1 ^= s[1];
            }
            next();
        }

    s[0] = s0;
    s[1] = s1;
}
