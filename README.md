# STM32 in Plain C

A companion series to [Hardware Conversations](https://github.com/learndataa/hardware-conversations) — one video, one concept, one tiny well-commented example.

If you've been following the Hardware Conversations series (building small neural networks in hardware on an STM32) and found yourself glossing over lines like `HAL_ADC_ConfigChannel(&hadc1, &sConfig)` or `GPIO_InitTypeDef GPIO_InitStruct = {0};` — this series is for that gap. It's aimed at people who are comfortable in a language like Python but new to C and embedded programming specifically.

Each episode isolates **exactly one C or HAL concept**, proves it with the smallest possible working example, and shows the result live on an LED. No episode assumes you've watched a previous one, but they build on each other in a sensible order.

---

## Who this is for

- You can read and write Python (or a similar high-level language) comfortably.
- C syntax — pointers, structs, fixed-width types, macros — looks unfamiliar or intimidating.
- You've seen STM32 HAL code (your own or someone else's) and found yourself skimming past the setup boilerplate without really understanding it.
- You don't need a full "learn C" course — you need the specific handful of ideas that HAL-based embedded code leans on repeatedly.

## Who this is *not* for

- If you already know C well, this will move too slowly — you're better served by the main [Hardware Conversations](https://github.com/learndataa/hardware-conversations) series directly.
- This is not a general-purpose C course. It only covers what's needed to comfortably read and write STM32 HAL code.

---

## Hardware used

Every example in this series targets the same board used throughout Hardware Conversations, so code is directly portable between the two series:

- **MCU**: STM32F051C8T6
- **Programmer/debugger**: ST-Link V2
- **Toolchain**: STM32 HAL library, hand-written `main.c` (no CubeMX-generated boilerplate — every line in every example is there for a reason, not auto-generated)

Most episodes only need the board itself and a single LED (the one already wired for earlier episodes works fine). A few later episodes may reuse the potentiometer setup from Hardware Conversations — noted per-episode where relevant.

## How to build and flash an example

1. Open the episode folder you want (see episode list below).
2. Copy `main.c` into your STM32 project, replacing the existing `main.c`.
3. Build with your usual toolchain (STM32CubeIDE, Makefile + arm-none-eabi-gcc, or your preferred setup).
4. Flash via ST-Link.
5. Each `main.c` is heavily commented — read the top comment block first, it explains what the example proves and (where relevant) what to break on purpose to see the concept in action.

No two examples require different wiring unless explicitly noted in that episode's folder.

---

## Episode list (Tier 1: Foundations)

Each folder contains that episode's `main.c` and a short `README.md` with the video link once published.

| # | Episode | Concept | Folder |
|---|---|---|---|
| 1 | Why Every STM32 Program Starts With This One Line | `#include` | [`episode-1-include/`](./episode-1-include) |
| 2 | Why C Makes You Choose the Size of a Number | Fixed-width types (`uint8_t`, `uint16_t`, `uint32_t`) | `episode-2-fixed-width-types/` |
| 3 | Every HAL Call Returns Something | Functions & return values | `episode-3-functions-return-values/` |
| 4 | The Loop That Never Ends (On Purpose) | `if/else`, `while(1)` | `episode-4-control-flow/` |
| 5 | One Box, Many Settings | Structs | `episode-5-structs/` |
| 6 | Why We Pass `&hadc1`, Not `hadc1` | Pointers and `&` | `episode-6-pointers/` |
| 7 | `GPIO_PIN_4` Isn't Magic | Enums / named constants | `episode-7-enums/` |
| 8 | Why `ADC_HandleTypeDef` Has Such a Long Name | Typedefs | `episode-8-typedefs/` |
| 9 | The Function That Isn't a Function | Macros / `#define` | `episode-9-macros/` |
| 10 | The Variable That Remembers | `static` | `episode-10-static/` |
| 11 | Why We Say `volatile` | `volatile` | `episode-11-volatile/` |
| 12 | Read Your Own main.c, Line by Line | Putting it all together | `episode-12-putting-it-together/` |

Folders for unreleased episodes will be added as each video goes live. This table is the roadmap — check back for links as episodes publish.

---

## Relationship to Hardware Conversations

This series and [Hardware Conversations](https://github.com/learndataa/hardware-conversations) share the same board, the same hand-written (no-CubeMX) style, and reference the same real lines of code — concepts here are anchored to actual lines used in that series, not abstract examples. Watch them in whichever order makes sense for you:

- Curious about the C first → start here, then move to Hardware Conversations once comfortable.
- Already watching Hardware Conversations and hitting unfamiliar syntax → jump to the specific episode here that covers it (see table above).

---

## Contributing / feedback

Found an error, have a suggestion for a future Tier 1 or Tier 2 topic, or want a specific line of HAL code explained? Open an issue — feedback shapes which concepts get covered next.

## License

MIT — use these examples freely in your own projects.
