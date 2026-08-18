// Episode 11: static
// "static" means two different things depending on where you use it.
// This file demonstrates static's FILE-SCOPE meaning: hiding a function
// so it can only be called from within this file.
// This episode is BUILD-ONLY -- no LED, no hardware.

#include <stdint.h>

// "static" here means "internal linkage" -- this function is invisible
// outside this file. No other .c file in the project can call it,
// even if they try to declare it themselves. The linker will refuse.
static uint8_t double_it(uint8_t x) {
    return x * 2;
}

// This function is NOT static, so other files in the project could
// call it -- and it's allowed to call our private static helper,
// because we're still inside the same file.
uint8_t quadruple_it(uint8_t x) {
    return double_it(double_it(x));
}

int main(void) {
    uint8_t result = quadruple_it(3); // 3 -> double_it -> 6 -> double_it -> 12
    (void)result;

    // This file alone builds cleanly -- proof that double_it() works fine
    // when called from within its own file. The README walks through the
    // real proof of "static = invisible outside this file": adding a
    // second .c file that tries to call double_it() directly, and
    // watching the linker refuse.

    while (1) {
        // Nothing runs here -- this episode is about compiling, not blinking.
    }
}
