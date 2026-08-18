// Episode 10: Macros / #define
// A macro isn't a function. Before your code even compiles, the
// preprocessor swaps the macro name for its literal text -- word
// for word. This episode is BUILD-ONLY: the proof is entirely at
// compile time.

#include <stdint.h>

// Looks like it squares a number. It doesn't -- not always.
// The preprocessor does a literal, unparenthesized text swap:
//   UNSAFE_SQUARE(2+3)  becomes  2+3*2+3   ==  11, not 25
#define UNSAFE_SQUARE(x) x*x

// Wrapping the argument (and the whole expression) in parentheses
// forces the swap to happen safely:
//   SAFE_SQUARE(2+3)  becomes  ((2+3)*(2+3))  ==  25
#define SAFE_SQUARE(x) ((x)*(x))

int main(void) {
    int unsafe_result = UNSAFE_SQUARE(2 + 3);
    int safe_result   = SAFE_SQUARE(2 + 3);

    // Compile-time proof -- both values are known before the program
    // ever runs, so the compiler checks them for us.
    _Static_assert(UNSAFE_SQUARE(2 + 3) == 11,
                   "unsafe macro expands to 2+3*2+3, not 25");
    _Static_assert(SAFE_SQUARE(2 + 3) == 25,
                   "safe macro correctly parenthesizes its argument");

    (void)unsafe_result;
    (void)safe_result;

    while (1) {
        // Nothing runs here -- this episode is about compiling, not blinking.
    }
}
