# vibration-node

STM32 motor-monitoring node: reads vibration, current and temperature, computes
features (RMS, FFT), flags faults, and reports over CAN to a hardware-in-the-loop
(HiL) test rig.

Hardware: 2× NUCLEO-F446RE · LIS3DH accelerometer · INA260 current sensor ·
DS18B20 temperature sensor · DFR0411 DC motor · MCP2562 CAN transceivers ·
24 MHz 8-channel logic analyzer.

## Status

- [x] Register bit and bit-field macros (`lib/bitops`), 10/10 tests passing
- [x] Ring buffer (`lib/ringbuf`), in progress
- [ ] Board bring-up (`docs/BRINGUP.md`)

## Roadmap

| Step | When | Goal | Done when |
|---|---|---|---|
| 1 C foundations | Nov → mid-Jan | pointers, memory, structs, bits, `volatile`, Makefiles | `make test` passes with the ring buffer and bit macros |
| 2 MCU basics | mid-Dec → mid-Feb | GPIO, timers, IRQs, UART, I2C/SPI, debugger, logic analyzer | `docs/BRINGUP.md` fully ticked |
| 3 Testing | Feb | Unity, mocks, a HAL so driver logic runs on the PC | sensor driver tested on the PC against a mocked I2C bus |
| 4 Node v1 | mid-Feb → Mar | vibration + current + temperature, RMS/FFT, fault flag | detects a weight taped to the fan |
| 5 FreeRTOS | Apr | tasks, queues, ISR → task handoff | node runs as tasks with no missed samples |
| 6 CAN | May → Jun | frames, bit timing, DBC, python-can | node data decoded live on the PC |
| 7 Mini HiL | Jun → Aug | second board injects faults, Raspberry Pi runs pytest | automated pass/fail report |
| 8 Secure update (stretch) | Aug → Sep | signed firmware images over CAN, rollback | unsigned image is rejected |

## Layout

```
lib/        portable C modules (no hardware), unit-tested on the PC
  bitops/   register bit and field macros
  ringbuf/  byte FIFO
test/       Unity tests for lib/
vendor/     third-party code (Unity v2.6.0, MIT)
firmware/   STM32CubeIDE projects
docs/       bring-up checklist; datasheets are listed in docs/README.md
```

## Build and test

Needs GCC and make. On Windows (WinLibs) use `mingw32-make`, elsewhere `make`.

```
mingw32-make test          # build and run all unit tests
mingw32-make test-bitops   # one suite
mingw32-make -k test       # run every suite even if one fails
mingw32-make clean
```

Compiled with `-std=c11 -Wall -Wextra -Werror -pedantic`.
