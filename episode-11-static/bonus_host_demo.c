// Episode 11 BONUS -- local static variables
//
// This file is NOT part of the PlatformIO/STM32 build. It's plain C,
// meant to compile and run directly on YOUR COMPUTER with gcc -- because
// the concept it shows (a static local variable keeps its value between
// calls) needs to actually run and print something, and this project has
// no UART/hardware in this episode to print with.
//
// This is standard C language behavior, not STM32/HAL-specific, so it
// works identically here as it would on the target chip.
//
// Run it yourself:
//   gcc -o bonus_host_demo bonus_host_demo.c
//   ./bonus_host_demo

#include <stdio.h>

int next_id(void) {
    static int counter = 0; // initialized ONCE, ever -- keeps its value
                             // between calls, unlike a normal local variable
    counter++;
    return counter;
}

int main(void) {
    printf("%d\n", next_id()); // 1
    printf("%d\n", next_id()); // 2
    printf("%d\n", next_id()); // 3
    return 0;
}
