// rule110.h

#ifndef __RULE110_H__
#define __RULE110_H__

// https://en.wikipedia.org/wiki/Rule_110
//
// Rules:
// Current pattern:             | 111 | 110 | 101 | 100 | 011 | 010 | 001 | 000
// New state for center cell:   |  0  |  1  |  1  |  0  |  1  |  1  |  1  |  0
// 7 -> 0
// 6 -> 1
// 5 -> 1
// 4 -> 0
// 3 -> 1
// 2 -> 1
// 1 -> 1
// 0 -> 0

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum Rule {
    ZERO = false,
    ONE = true,
    TWO = true,
    THREE = true,
    FOUR = false,
    FIVE = true,
    SIX = true,
    SEVEN = false
};

bool check_last_three_bits(unsigned int n);

unsigned int reverse_bits(unsigned int n);

unsigned int get_next(unsigned int n);

void set_buffer(unsigned int n);

void display_buffer(void);

int main(int argc, char **argv);

#endif // __RULE110_H__
