# vibration-node

STM32 motor-monitoring node: reads vibration, current and temperature, computes
features (RMS, FFT), flags faults, and later reports over CAN to a HiL test rig.

Hardware: 2× NUCLEO-F446RE · LIS3DH accelerometer · INA260 current sensor ·
DS18B20 temperature sensor · DFR0411 DC motor · MCP2562 CAN transceivers ·
24 MHz 8-channel logic analyzer.

## Roadmap

| Step | When | Goal | Done when |
|---|---|---|---|
| 1 C foundations | now → mid-Jan | pointers, memory, structs, bits, `volatile`, Makefiles | `make test` passes with your own ring buffer + bit macros |
| 2 MCU basics | mid-Dec → mid-Feb | GPIO, timers, IRQs, UART, I2C/SPI, debugger, logic analyzer | `docs/BRINGUP.md` fully ticked |
| 3 Testing | Feb | Unity/Ceedling, mocks, HAL so logic runs on the PC | sensor driver tested on PC with a mocked I2C |
| 4 Node v1 | mid-Feb → Mar | vibration + current + temperature, RMS/FFT, fault flag | catches a weight taped to the motor |
| 5 FreeRTOS | Apr | tasks, queues, ISR → task handoff | node runs as tasks |
| 6 CAN | May → Jun | frames, bit timing, DBC, python-can | node data decoded on the PC |
| 7 Mini HiL | Jun → Aug | board A fakes faults, board B under test, Pi runs pytest | automated pass/fail report |

## Layout

```
lib/        portable C modules (no hardware) - unit-tested on the PC
  ringbuf/  byte FIFO           <- Step 1 exercise
  bitops/   register bit macros <- Step 1 exercise
test/       Unity tests for lib/
vendor/     third-party code (Unity v2.6.0, MIT)
firmware/   STM32CubeIDE projects (created when the boards arrive)
docs/       datasheets, manuals, bring-up checklist
```

## Build and test on your PC

Needs GCC + make (installed: WinLibs GCC 16, `mingw32-make`).

```
mingw32-make test          # build + run all unit tests
mingw32-make test-ringbuf  # one suite
mingw32-make -k test       # run every suite even if one fails
mingw32-make clean
```

Right now every test **fails on purpose**: `lib/ringbuf/ringbuf.c` and
`lib/bitops/bitops.h` are stubs. Implementing them is the Step 1 exercise.
The tests define what "correct" means — read them first.
