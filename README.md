# Easy FreeRTOS install for RP2040 & RP2350

A quick & simple method that works for both RP2040 and RP2350 chips on RPi Pico-SDK, with automatic chip selection and proper SMP support.

This repo is just an example "Hello World" application, but the method works with any Pico-SDK project in less than a minute.

## Prerequisites

- Pico SDK installed at `~/.pico-sdk` (Mac/Linux)
- CMake and build tools

## How To

1. Clone the FreeRTOS kernel from Raspberry Pi's GitHub repo (not the one from FreeRTOS's, it lacks RP2350 port):
   ```bash
   cd ~/.pico-sdk/sdk/2.1.1/lib # <- SDK directory, version/lib folder
   git clone https://github.com/raspberrypi/FreeRTOS-Kernel.git
   ```

2. Copy the `freertos` folder of this repo to project directory

3. Edit the main project's CMakeLists.txt:
    ```cmake
    [...]

    # Initialise the Raspberry Pi Pico SDK
    pico_sdk_init()

    # Add FreeRTOS
    add_subdirectory(freertos) # <- add this

    [...]

    # Add the standard library to the build
    target_link_libraries(your-project
        pico_stdlib
        freertos) # <- add this

    [...]
    ```

4. In `main.c`/`main.cpp`:
   - Include FreeRTOS headers: `#include "FreeRTOS.h"`, `#include "task.h"`, ...
   - Create tasks after `stdio_init_all()`
   - Call `vTaskStartScheduler()` at the end of `main()` function
   - Add an infinite loop as safety guard (scheduler should never return)

5. Compile & flash the project, that's it

## `freertos` directory structure

```
freertos/
├── CMakeLists.txt      # Build configuration with automatic port selection
├── FreeRTOSConfig.h    # Unified sample config for RP2040/RP2350
├── hooks.c             # Error handlers and static memory allocation
└── cpp_mem.cpp         # C++ new/delete overrides for FreeRTOS heap
```

## Sample configuration

- SMP enabled (`configNUMBER_OF_CORES = 2`) for dual-core operation
- Chip-specific clocks: 133MHz for RP2040, 150MHz for RP2350  
- RP2350 features: FPU enabled, TrustZone disabled, MPU disabled
- Memory safety: Static allocation support, stack overflow checking (level 2), malloc failure hooks
- Debugging: Assert support and error handlers