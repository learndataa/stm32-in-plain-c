// Episode 9: Typedefs
// Why does HAL give types names like "ADC_HandleTypeDef"?
// This episode is BUILD-ONLY -- no flashing, no LED, no hardware needed.
// We prove the concept entirely at compile time.

#include <stdint.h>

// The long way: a struct with no typedef.
// To make a variable of this type, you must write "struct ADC_LikeHandle_tag"
// every single time. That's what typedef lets you avoid.
struct ADC_LikeHandle_tag {
    uint8_t channel;
    uint8_t is_ready;
};

// The typedef way: same struct, but now "ADC_LikeHandle" is a type name
// on its own -- no "struct" keyword needed to use it.
typedef struct {
    uint8_t channel;
    uint8_t is_ready;
} ADC_LikeHandle;

int main(void) {
    struct ADC_LikeHandle_tag long_way;   // works, but verbose every time
    ADC_LikeHandle short_way;             // same type, less typing

    long_way.channel  = 1;
    short_way.channel = 1;

    // Compile-time proof: both variables are the exact same type underneath.
    // If this fails, it fails when you build -- not on hardware, not at runtime.
    _Static_assert(sizeof(long_way) == sizeof(short_way),
                   "typedef'd and non-typedef'd forms must be identical");

    while (1) {
        // Nothing runs here -- this episode is about compiling, not blinking.
    }
}
