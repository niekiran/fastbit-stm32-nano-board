<!--
DRAFT — content only, not laid out in the branded template used by
fastbit_stm32_nano_UM_v2_0.pdf / fastbit_stm32_nano_UM_v3_0.pdf.

This mirrors those two manuals' exact section structure, updated against
the actual v2.1 schematic (Documents/Schematics/fastbit_stm32_nano_sch_v2_1(SPI_LCD).pdf).
See the "Open items" section at the bottom for what's still needed before
this can be turned into a matching PDF.
-->

# User manual — Nano Board with STM32F303CCT6 MCU (v2.1)

## Introduction

The Nano board allows users to easily develop applications with the STM32F303CCT6
microcontroller with the Arm Cortex-M4 32-bit core.

Based on STM32F303CCT6, it includes one BMI270 (a 3-axis gyroscope and a 3-axis
accelerometer sensor), LEDs, push-buttons, and a USB Type-C port.

**Figure 1: Nano** — *[NEEDED: photo of the physical v2.1 board, top view — see "Open items"]*

## Contents
1. Features
2. List of tables
3. List of figures
4. Hardware and layout
5. Programming Nano Board

## List of tables
- Table 1. Boot modes
- Table 2. HSE pins
- Table 3. UART1 pins

## List of figures
- Figure 1. Nano
- Figure 2. Nano top layout
- Figure 3. Nano bottom layout
- Figure 4. ST-Link V2 to Nano board connection

## List of Block-diagram
- Block 1: UART-USB bridge

## List of abbreviation
| Abbreviation | Meaning |
|---|---|
| SWD | Serial Wire Debug |
| LQFP | Low Profile Quad Flat Package |
| HSE | High Speed External |

(No LSE entry — see note under "OSC Clock" below: v2.1 does not carry the 32.768 kHz
crystal that v2.0 has.)

## Feature

The Nano offers the following features:
- The STM32F303CCT6 microcontroller features a 32-bit Arm Cortex-M4 with FPU core
  (72 MHz max), 256-Kbyte Flash memory, and 48-Kbyte SRAM in a LQFP48 package.
- Three push buttons:
  - SW1 (reset), SW2 (user button), SW3 (boot0).
- Four LEDs:
  - D1 (red) for 3.3 V power on/off.
  - Three user LEDs, D2 (blue), D3 (green), D4 (red).
- Board connectors:
  - J1 SWD.
  - J2 USB Type-C.
  - 2.54 mm pitch extension header for 30 pins of LQFP48 I/Os for quick connection to
    prototyping board and easy probing.
- Power-supply options: ST-LINK or USB VBUS.

## Hardware and layout

The Nano is designed around the STM32F303CCT6 microcontroller in a 48-pin LQFP package.

Figure 2 and Figure 3 help users locate the STM32F303CCT6 and its peripherals (BMI270,
push buttons, LEDs).

**Figure 2: Nano top layout** — *[NEEDED: annotated top-side board photo — see "Open items"]*

**Figure 3: Nano bottom layout** — *[NEEDED: annotated bottom-side board photo — see "Open items"]*

### Power supply and power selection
- The power supply is provided either by the host PC through the USB Type-C cable, or
  via the SWD port using an ST-Link connection.
  - The onboard regulator regulates the 5 V input from USB to provide a steady 3.3 V output.

**Note: Don't connect an external power supply to the header sockets.**

### LEDs
- D1 PWR: red LED indicates that the board is powered.
- User D2: blue LED, connected to I/O PA1 of the STM32F303CCT6.
- User D3: green LED, connected to I/O PA2 of the STM32F303CCT6.
- User D4: red LED, connected to I/O PA3 of the STM32F303CCT6.

### Push buttons
- SW1 RESET: push button connected to NRST, used to reset the STM32F303CCT6.
- SW2 USER: user button, connected to I/O PA0 of the STM32F303CCT6.
- SW3 BOOT0: push button connected to BOOT0, used to toggle the boot mode of the
  STM32F303CCT6.

| BOOT0 | Boot Mode |
|---|---|
| 0 | Main flash memory |
| 1 | System memory |

**Table 1: Boot modes**

Note: By default, the microcontroller runs the application code from the main flash
memory. To change this behavior, use the BOOT0 button.
1. Press and hold the BOOT0 button, then press the reset button.
2. This makes the microcontroller run the built-in bootloader from system memory
   (i.e., the microcontroller enters bootloader mode).

### 6-Axis (Gyro + Accelerometer) MEMS Motion Tracking

- BMI270 is an ultra-low-power, high-performance 6-axis IMU (Gyro + Accelerometer),
  combining a 3-axis gyroscope and a 3-axis accelerometer on a single die.
- The STM32F303CCT6 microcontroller controls this sensor through the I2C interface.
- BMI270 replaces the MPU6050 used on Nano board v2.0; it sits at the same I2C address
  and uses the same board pins, so no wiring change is required relative to v2.0.

### OSC Clock

- HSE: OSC 8 MHz clock supply

  Refers to an external oscillator running at 8 MHz. It provides a higher-frequency
  clock source suitable for driving the core processing unit or other high-speed
  peripherals.

  | Pin Name | Pin Function |
  |---|---|
  | PF0 | OSC_IN |
  | PF1 | OSC_OUT |

  **Table 2: HSE pins**

**Note:** unlike Nano board v2.0, v2.1 does not carry the 32.768 kHz (LSE) crystal
used for RTC/timing-sensitive functions — confirmed against the v2.1 schematic's
Oscillators block, which shows only the 8 MHz HSE crystal. (This matches v3.0, whose
manual also omits an LSE pin table.) If your application needs a precise low-speed
clock for the RTC, it will need to run from an internal/software-calibrated source
instead of an external 32.768 kHz crystal on this board revision.

### USB to UART bridge

- The USB to UART bridge facilitates communication between a computer and the
  STM32F303CCT6, with UART1 Tx and UART1 Rx serving as the transmit and receive pins,
  connected to pins PA9 and PA10 on the microcontroller.

  | Pin Name | Pin Function |
  |---|---|
  | PA9 | UART1_Tx |
  | PA10 | UART1_Rx |

  **Table 3: UART1 pins**

**Block 1: UART-USB Bridge** — *identical topology to the v2.0 manual's Block 1*
  (STM32F303CCT6 USART1_TX/PA9 and USART1_RX/PA10 → CH340N RX/TX → USB to PC).
  See "Open items" below re: reusing that diagram.

## Programming Nano Board

1. **Using bootloader (ST-Link not required):**
   - Power the board via USB.
   - Press and hold the BOOT0 button, then press the reset button.
   - Open STM32CubeProgrammer and connect to the board by selecting UART/USB.
   - Open a `.elf` file and download the program to the board.
   - Reset the board to run the code.

   Note: You cannot debug the code using this method.

2. **Using ST-Link:**
   - Connect the ST-Link to the board via the SWD interface.

     **Figure 4: ST-link V2 to Nano board connection** — *identical wiring to the v2.0
     manual's Figure 4 (SWDCLK/SWDIO/RESET/SWO/GND/3V3 on the same 6-pin header).
     See "Open items" below re: reusing that diagram.*

   - Power the board via USB or ST-Link, depending on the setup.
   - Open STM32CubeIDE or any other compatible IDE.
   - Configure the IDE to use ST-Link as the debugging interface.
   - Build your project or open a `.elf` file.
   - Use the IDE to download the program to the board.
   - Use the IDE's "Debug" option to debug the program, or "Run" to execute it without
     debugging.

---

## Open items before this becomes a published PDF

1. **Board photos (Figures 1–3)** — I have no way to photograph the physical v2.1
   board. Please supply: a clean top-view product photo (Figure 1), and the same
   annotated top/bottom layout photos used in the v2.0/v3.0 manuals but for the v2.1
   board (Figures 2–3, ideally labeling J1 SWD, J2 USB-C, D1–D4 LEDs, SW1–SW3 buttons,
   U7 BMI270, Y1 8 MHz crystal, and the CH340N USB-UART converter). I drew the pin/label
   facts above directly from the v2.1 schematic, but the photos themselves need to come
   from you.
2. **Figures 4 and Block 1** — these are simple schematic-style box diagrams (not
   photos), and the underlying hardware (SWD pinout, CH340N UART bridge) is identical
   between v2.0 and v2.1. Two options: reuse the exact same diagram images from the
   v2.0 manual as-is (if you have the source graphics), or I can redraw both as
   plain diagrams from the pin facts above — let me know which you'd prefer.
3. **Template/branding** — the v2.0 and v3.0 manuals are laid out in a branded
   template (fastbitembedded.com header, logo, page footer) that I don't have the
   source file for. This draft has the full accurate content and structure to drop
   into that template; I can't produce a matching PDF without either the template
   source or you converting this content over.
