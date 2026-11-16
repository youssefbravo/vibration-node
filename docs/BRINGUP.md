# Board bring-up checklist

Do these in order. Do not start a step until the one above it works.
Tick them off and commit after each one.

## Before anything is plugged in
- [ ] Solder pin headers onto the LIS3DH and INA260 boards (uni lab)
- [ ] Borrow a multimeter
- [ ] Rules: power OFF before rewiring · all grounds connected · sensors on **3.3 V** · never 5 V into a pin unless the datasheet says it is 5 V tolerant · the motor never draws power from the Nucleo pins

## Nucleo-F446RE (both boards, one at a time)
- [ ] 1. Plug in via USB. A drive `NODE_F446RE` and a COM port appear (Device Manager → Ports)
- [ ] 2. STM32CubeProgrammer → update the ST-Link firmware
- [ ] 3. CubeIDE: new project for NUCLEO-F446RE, blink **LD2 (PA5)** with HAL
- [ ] 4. **Blink again with registers only** (no HAL): enable GPIOA clock in `RCC->AHB1ENR`, set PA5 to output in `GPIOA->MODER` (bits 11:10 = 01), toggle `GPIOA->ODR` bit 5. Use your `bitops.h` macros
- [ ] 5. Step through step 4 in the debugger, watching the GPIOA registers change in the SFR view
- [ ] 6. **UART printf**: USART2 (PA2 TX / PA3 RX), 115200 8N1, prints "hello" in a serial terminal
- [ ] 7. **Logic analyzer**: clip CH0 to PA2 and GND to GND, PulseView sample rate ≥ 1 MHz, add the UART decoder → you see "hello"
- [ ] 8. **Button B1 (PC13) as EXTI interrupt** toggles the LED (no polling in `main`)
- [ ] 9. **Timer PWM** on a pin (e.g. TIM2 CH1 on PA0): 1 kHz, 25 % duty, confirmed in PulseView
- [ ] 10. **UART receive into your ring buffer** from the RX interrupt; main loop echoes characters back

## First sensor: LIS3DH accelerometer (I2C)
Wiring: VIN → 3V3, GND → GND, SCL → D15 (PB8), SDA → D14 (PB9). Adafruit board has its own pull-ups. Default address 0x18.
- [ ] 11. Read WHO_AM_I (reg 0x0F) → expect **0x33**. If not: check the I2C waveform in PulseView (I2C decoder) before changing code
- [ ] 12. Configure 100 Hz, ±2 g; stream X/Y/Z over UART; values change when you tilt the board
- [ ] 13. Raise output data rate (e.g. 1.344 kHz) for vibration later — note what breaks

## Parked until later steps (keep in the box)
- INA260 current sensor, DS18B20 temperature, DFR0411 motor + 5 V supply → **Step 4** (mid-Feb)
- MCP2562 CAN transceivers + 120 Ω resistors → **Step 6** (May). Note: CAN1 on PB8/PB9 clashes with I2C1 there — use PA11/PA12 (Morpho header) for CAN.
