// rule110.c

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
#include <unistd.h>

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

#define MAX_BUFFER_SIZE 32

static int buffer[MAX_BUFFER_SIZE] = {0};

static bool check_last_three_bits(unsigned int n) {
    unsigned int mask = (1 << 3) - 1;
    unsigned int last_3_bits = n & mask;
    bool result = true;
    switch (last_3_bits) {
    case 0:
        result = ZERO;
        break;
    case 1:
        result = ONE;
        break;
    case 2:
        result = TWO;
        break;
    case 3:
        result = THREE;
        break;
    case 4:
        result = FOUR;
        break;
    case 5:
        result = FIVE;
        break;
    case 6:
        result = SIX;
        break;
    case 7:
        result = SEVEN;
        break;
    default:
        break;
    }
    return result;
}

static unsigned int reverse_bits(unsigned int n) {
    unsigned int result = n;
    int size = sizeof(n) * CHAR_BIT - 1; // extra shift needed at the end
    for (n >>= 1; n; n >>= 1) {
        result <<= 1;
        result |= n & 1;
        size--;
    }
    result <<= size; // shift when n's highest bits are zero
    return result;
}

static unsigned int get_next(unsigned int n) {
    unsigned int result = 0;
    while (n) {
        if (check_last_three_bits(n)) {
            result <<= 1;
            result |= 1;
        } else {
            result <<= 1;
            result |= 0;
        }
        n >>= 1;
    }
    result = reverse_bits(result);

    return result;
}

static void set_buffer(unsigned int n) {
    memset(buffer, 0, MAX_BUFFER_SIZE);
    size_t i;
    i = MAX_BUFFER_SIZE - 1;
    while (n) {
        buffer[i--] = n & 1;
        n >>= 1;
    }
}

static void display_buffer(void) {
    size_t i;
    for (i = 0; i < MAX_BUFFER_SIZE; i++) {
        if (buffer[i]) {
            // printf('X');
            // printf("#");
            printf("██");
        } else {
            // printf(' ');
            // printf(".");
            printf("░░");
        }
    }
    putchar('\n');
}

static const unsigned int PATTERNS[10] = {
    0x1C000000, 0xAA000000, 0x36000000, 0x7E000000, 0x1FF00000,
    0x80000000, 0x3FF00000, 0x1F700000, 0x5A5A0000, 0x81800000};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    unsigned int repeat;
    unsigned int n;
    repeat = 32;
    n = PATTERNS[7];
    set_buffer(n);
    while (repeat--) {
        display_buffer();
        usleep(100 * 1000);
        n = get_next(n);
        set_buffer(n);
    }
    return 0;
}
