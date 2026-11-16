# Handoff — everything set up so far (16 Nov 2026)

From here on you drive. This file is the full record of what was bought, what was
installed, what is in this repo, what is still open, and how to keep going
without an AI writing your code.

---

## 1. Hardware — ordered (total €110.38)

| Shop | Order # | Contents | Paid | Expected |
|---|---|---|---|---|
| Amazon.de | 028-7431964-7878730 | AZDelivery logic analyzer, 24 MHz, 8 ch | €13.99 | Tue 17 Nov |
| Conrad | 2020447831 | 2× STMicroelectronics NUCLEO-F446RE (genuine, sold by Conrad) | €44.93 | Thu 19 Nov |
| BerryBase | 1105554 | 15 lines, see below | €51.46 | 17–19 Nov (see open issue) |

**BerryBase contents:** Adafruit LIS3DH accelerometer · Adafruit INA260 current sensor ·
DS18B20 temperature sensor · DFRobot DFR0411 130 DC motor module · 5 V 2.4 A plug PSU
(5.5/2.1 mm) · DC barrel socket → screw terminal · jumper wire set (F-F / M-M / F-M) ·
2× breadboard 830 · 2× USB-A → Mini-B cable (0.3 m) · 10× 10 kΩ · 5× 4.7 kΩ · 4× 120 Ω ·
10× 100 nF · 2× 470 µF 25 V · 2× MCP2562 CAN transceiver.

**What each part is for**
| Part | Plan step | Role |
|---|---|---|
| Nucleo-F446RE ×2 | 2 → 7 | MCU + built-in ST-Link debugger; two because the CAN/HiL rig needs a pair |
| Logic analyzer | 2 → 7 | See UART / I2C / PWM / CAN signals in PulseView |
| LIS3DH | 2, 4 | Vibration sensor (I2C or SPI) — first sensor to bring up |
| INA260 | 4 | Motor current (I2C) |
| DS18B20 + 4.7 kΩ | 4 | Temperature (1-Wire, bit-banged timing) |
| DFR0411 motor + 5 V PSU + barrel socket + 470 µF | 4 | The "machine"; tape a weight on the propeller to create the fault |
| MCP2562 ×2 + 120 Ω | 6, 7 | CAN bus between the two boards (VIO pin → 3.3 V) |

**Decisions made along the way (and why)**
- reichelt cart (€91 incl. 12 V PC fan + ADXL345) was abandoned: no payment method that worked for you.
- BerryBase has no Nucleo and no 12 V PWM fan → motor changed to the 5 V DFR0411; ADXL345 (out of stock) → LIS3DH. Current + temperature sensors added because step 4 needs them.
- Nucleo on Amazon was €45+ each from Waveshare or no-name sellers → bought at Conrad for €19.99 instead.

**Not bought yet (buy when the step starts)**
- USB-CAN adapter with candleLight / gs_usb firmware (~€15–25) — step 6, May
- Raspberry Pi 4/5 + CAN interface — step 7, June
- Borrow: multimeter, soldering iron (LIS3DH and INA260 headers ship unsoldered)
- Blu-Tack / tape / zip ties for mounting the sensor and the imbalance weight

## 2. Open issue — BerryBase address ⚠️

The order was placed with **postcode 10577** and city **"mitte, building 20"**
(correct: 10557 Berlin). The order cannot be edited online.

- Support ticket **353309** sent 16 Nov asking them to correct it before shipping.
  Expected reply: ~17 Nov, by email.
- Your saved BerryBase account address is already corrected for future orders.
- If it ships unchanged: track it via the DHL email/app; street + number are
  correct, so it often still arrives. If it comes back, reply on ticket 353309.

## 3. Installed on this PC

| Tool | Version | Notes |
|---|---|---|
| WinLibs GCC + `mingw32-make` | GCC 16.2.0, Make 4.4.1 | via winget, on your user PATH (open a new terminal) |
| PulseView | 0.4.2 | logic analyzer software |
| Git | 2.55 | was already installed |

**Still to install yourself (needs a free myST login at st.com):**
STM32CubeIDE (editor/compiler/debugger + ST-Link drivers) and STM32CubeProgrammer.

## 4. This repo

```
README.md        roadmap (7 steps) + build commands
HANDOFF.md       this file
Makefile         host build of unit tests (Windows: mingw32-make)
lib/ringbuf/     exercise 1 — header/API done, ringbuf.c = stubs
lib/bitops/      exercise 2 — bitops.h = stubs
test/            20 Unity tests (10 ring buffer, 10 bit macros)
vendor/unity/    Unity v2.6.0 (MIT)
firmware/        empty — CubeIDE projects go here on board day
docs/BRINGUP.md  13-step board bring-up checklist
docs/README.md   datasheet list + download links
```

State: skeleton committed (c39f46e). All 20 tests build cleanly
(`-Wall -Wextra -Werror -pedantic`) and **fail on purpose**.

The tests were verified against a separate reference solution (kept outside
this repo) — all 20 passed. So when a test fails, the bug is in your code,
not in the test.

## 5. Your to-do list, in order

1. [x] First commit (c39f46e)
2. [ ] Install STM32CubeIDE + STM32CubeProgrammer (before Thursday) — needs you to accept ST's license and sign in to myST (or use the guest e-mail link)
3. [x] All 8 PDFs in `docs/` (16 Nov)
4. [ ] Watch for BerryBase's reply on ticket 353309
5. [ ] Exercise 2: make `mingw32-make test-bitops` pass (shorter, start here)
6. [ ] Exercise 1: make `mingw32-make test-ringbuf` pass
7. [ ] Tomorrow: plug in the logic analyzer, open PulseView, confirm it is detected (fx2lafw driver)
8. [ ] Thursday: boards arrive → `docs/BRINGUP.md` step 1 onward
9. [ ] Weekdays C (step 1), weekends board bring-up, full switch to step 2 mid-Dec

## 6. Working without AI — how to get unstuck

The order that works for embedded:
1. **Read the test / the requirement** — what exactly is expected?
2. **Read the manual section** — RM0390 for registers, the sensor datasheet for its registers. Search the PDF for the register name.
3. **Measure, don't guess** — on hardware, look at the pin with the logic analyzer *before* changing code. Most "code bugs" in bring-up are wiring, clock enable, or pin alternate-function mistakes.
4. **Debugger** — single-step, watch the peripheral registers (SFR view in CubeIDE).
5. **Shrink the problem** — smallest program that shows the bug.
6. Only then search: ST Community forum, the reference manual errata, Stack Overflow.

Habits from your plan worth keeping:
- Commit after every checklist step that works, with a message saying what works.
- Add ~30 % time buffer for hardware debugging. When behind, cut scope (fewer sensors), not steps.
- Book for step 3: James Grenning, *Test-Driven Development for Embedded C*.
- Simulink Onramp (free, MathWorks) in May.
