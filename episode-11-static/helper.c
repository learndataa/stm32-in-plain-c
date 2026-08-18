// Episode 11 EXERCISE FILE -- not built by default.
//
// This is the "another file" referred to in the README's try-it-yourself
// step 2. It attempts to call double_it() -- the static function defined
// in main.c -- from outside its own file.
//
// To try this yourself: temporarily add this file to your build (see
// README), then build. You should get a LINKER error, not a compiler
// error -- the code compiles fine, it just fails to link, because
// double_it() has internal linkage and simply doesn't exist as far as
// this file (or the linker) is concerned.

#include <stdint.h>

uint8_t double_it(uint8_t x); // declaring it doesn't make it visible --
                               // "static" in main.c means it was never
                               // given external linkage to declare in the
                               // first place.

uint8_t try_calling_the_static_one(uint8_t x) {
    return double_it(x);
}
