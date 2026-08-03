# STM32 in Plain C — Episode 1: #include

Format: voiceover only, no face on camera. Screen recording (code editor
+ terminal) and TOP-DOWN board shots only. Read naturally, don't perform.

Target runtime: 60-90 seconds. This is a single-concept series — resist
the urge to over-explain. One idea, proven once, done.

---

## SCRIPT (read straight through as VO)

[Cold open, screen recording, LED already blinking in a small corner
picture-in-picture or cut to TOP-DOWN briefly]

"Every single file in this series starts with this line."

[Screen: highlight `#include "stm32f0xx_hal.h"`]

"Comment it out—"

[Screen: comment out the line, click BUILD only — no flashing, no
board interaction yet, this failure happens purely on the compile step]

"—and the whole thing falls apart before it even gets near the chip."

[Screen: build errors scroll, highlight one: "unknown type name
'GPIO_InitTypeDef'"]

"The compiler has no idea what a GPIO_InitTypeDef is. Or what
HAL_GPIO_WritePin means. Or GPIO_PIN_4. None of it."

[Screen: scroll through 2-3 more error lines quickly]

"Because none of those words are defined in this file. They're defined
somewhere else — inside stm32f0xx_hal.h."

[Screen: briefly open the actual HAL header file, scroll fast to show
it's just... more code, definitions, real content — not magic]

"#include doesn't do anything mysterious. It just copies everything
from that file into this one, before the compiler even starts. That's
it. That's the whole trick."

[Screen: uncomment the line back]

"Put it back—"

[Screen: build again, success this time, then flash to the board]

"—and suddenly the compiler knows every one of those words again."

[Cut to TOP-DOWN: LED blinking steadily]

"One line. It's not magic. It's just borrowing someone else's
vocabulary before you start talking."

[End card: "Next: why C makes you choose the SIZE of a number" +
subscribe]

---

## TITLE
**Why Every STM32 Program Starts With This One Line | STM32 in Plain C**

Alt: "The Line That Breaks Everything If You Remove It | C for STM32"

## DESCRIPTION

```
Episode 1 of STM32 in Plain C: a companion series to Hardware 
Conversations, breaking down the C syntax and HAL calls line by line — 
for anyone who's comfortable in Python but new to C and embedded work.

Today: #include. What it actually does, and what breaks when it's 
missing — proven live by deleting it and watching the build fail.

This series pairs with Hardware Conversations (the neural-network-on-
STM32 series) — if you've been following along there and glossing over 
the HAL_ calls, this is for you.

⏱️ TIMESTAMPS
0:00 The line every file starts with
0:10 Deleting it on purpose
0:25 Reading the error
0:45 What #include actually does
1:00 Putting it back

🔧 CODE USED
Full commented example in the video, also on GitHub:
https://github.com/learndataa/hardware-conversations

#include isn't magic - it's just copying another file's contents into 
yours before the compiler starts. One line, one idea, proven once.

#STM32 #C #EmbeddedSystems #LearnC #Microcontroller #Programming
```

## TAGS (fits 500-character limit)

```
STM32, C programming, embedded C, learn C, include statement, C for 
beginners, HAL library, microcontroller programming, embedded systems, 
C syntax explained, STM32 tutorial, bare metal programming, C compiler 
errors, header files, programming basics, learn embedded systems, 
STM32 in plain C
```
(≈290 characters — well under limit, room to expand if needed)

## EXTENDED KEYWORDS (pinned comment / community post)

```
what does include do in C, C header files explained, STM32 HAL tutorial, 
C programming for Python developers, embedded C basics, why use include 
in C, C compiler error explained, learn C from scratch, STM32F051 
tutorial, bare metal C programming, microcontroller programming basics, 
C for hardware, understanding HAL library, C syntax for beginners, 
embedded systems learning path
```
