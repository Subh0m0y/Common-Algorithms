#ifndef TEST_H
#define TEST_H
#include <stdbool.h>

/*
 * Method to compare the equality of two integer expressions.
 * test : The name/description of the test being performed.
 * exp 	: The expected value.
 * act	: The actual value.	
 */
bool check_uint64s_equal(const char * test, const uint64_t exp, const uint64_t act);

#endif