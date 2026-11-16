# firmware/

STM32CubeIDE projects live here. Create the first one on board day:

1. STM32CubeIDE → File → New → STM32 Project → Board Selector → **NUCLEO-F446RE**
2. Project name `blink`, location: this folder (untick "Use default location")
3. Follow `../docs/BRINGUP.md` from step 3

To reuse the tested modules, add `../lib/ringbuf` and `../lib/bitops` to the
project's include paths and source folders instead of copying the files.
