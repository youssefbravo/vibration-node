# Reference documents

Keep every PDF you use in this folder. You will open the reference manual more
than any other file in this project.

| File | What it is | When you need it | Status |
|---|---|---|---|
| `RM0390_STM32F446_reference_manual.pdf` | **The** register-level manual (RCC, GPIO, TIM, USART, I2C, SPI, ADC, CAN...) | Every day from step 2 | ✅ |
| `STM32F446RE_datasheet.pdf` | Pinout, alternate functions table, electrical limits (which pins are 5 V tolerant) | Wiring anything | ✅ |
| `UM1724_Nucleo64_user_manual.pdf` | The Nucleo board: LED = PA5, button = PC13, ST-Link UART = USART2 PA2/PA3, solder bridges, Arduino/Morpho pin maps | Board day 1 | ✅ |
| `PM0214_CortexM4_programming_manual.pdf` | Cortex-M4 core: NVIC, SysTick, exceptions, instruction set | Interrupts (step 2) | ✅ |
| `LIS3DH_datasheet.pdf` | Accelerometer registers. WHO_AM_I = reg 0x0F → 0x33 | I2C bring-up | ✅ |
| `INA260_datasheet.pdf` | Current/voltage/power sensor. Manufacturer ID reg 0xFE → 0x5449 | Step 4 | ✅ |
| `DS18B20_datasheet.pdf` | 1-Wire temperature sensor timing | Step 4 | ✅ (SparkFun mirror of the Maxim datasheet; ADI's current copy is Rev 6 at the link below) |
| `MCP2562_datasheet.pdf` | CAN transceiver (VIO pin → connect to 3.3 V) | Step 6 | ✅ |

All 8 downloaded 16 Nov 2026 and checked to be complete PDFs.

## Source links (to re-download)

ST's and Analog Devices' servers block scripted downloads (curl/PowerShell),
so use a normal browser:

- RM0390: https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
- STM32F446RE datasheet: https://www.st.com/resource/en/datasheet/stm32f446re.pdf
- UM1724: https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf
- PM0214: https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf
- LIS3DH: https://www.st.com/resource/en/datasheet/lis3dh.pdf
- DS18B20: https://www.analog.com/media/en/technical-documentation/data-sheets/DS18B20.pdf

PDFs are git-ignored (they are large and not yours to redistribute); this list
is what lets you or anyone else re-download them.
