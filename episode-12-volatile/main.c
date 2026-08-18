// Episode 12: volatile
// The compiler assumes a variable's value can't change unless it sees
// code that changes it. That assumption is usually right -- but it's
// exactly wrong for a variable an interrupt or piece of hardware can
// change behind the compiler's back. "volatile" turns the assumption off.
// This episode is BUILD-ONLY -- the proof is in the generated assembly,
// not on the LED.

#include <stdint.h>

// Try this WITHOUT volatile first (as written). Then add "volatile"
// (see README) and compare the disassembly -- that's the whole demo.
uint8_t flag = 0;

// A classic embedded pattern: "wait here until something else sets flag."
// In real firmware, "something else" would be an interrupt handler.
void wait_for_flag(void) {
    while (flag == 0) {
    }
}

int main(void) {
    wait_for_flag();

    while (1) {
        // Nothing runs here -- this episode is about compiling, not blinking.
    }
}
