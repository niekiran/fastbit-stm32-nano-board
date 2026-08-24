# fastbit-stm32-nano-board

Resources, example projects, and firmware for the **Fastbit STM32 Nano board** — an STM32F303CC-based dev board with an onboard IMU, a round 1.28" TFT LCD with capacitive touch, and USB.

Product link: https://fastbitembedded.com/collections/vendors?q=FastBit%20Embedded
Free video course: [Embedded Systems Bootcamp: Learn by Building Projects](https://courses.fastbitembedded.com/courses/mastering-embedded-systems-build-real-world-projects)

![image](https://github.com/niekiran/fastbit-stm32-nano-board/assets/29812736/72330185-fb94-474b-ba38-152436d2fbe6)
![image](https://github.com/niekiran/fastbit-stm32-nano-board/assets/29812736/c93a1f82-d91c-478b-8120-2281ac1b9dcd)

## Supported boards

- **[Fastbit STM32 Nano board v2.0](https://fastbitembedded.com/products/fastbit-stm32-nano-with-1-28-tft-lcd-display?_pos=3&_sid=9a704cd97&_ss=r)**
- **Fastbit STM32 Nano board v2.1** (product link coming soon)
- **[Fastbit STM32 Nano board v3.0](https://fastbitembedded.com/products/fastbit-stm32-nano-v3-with-1-28-tft-lcd-display-module?_pos=12&_sid=d19e43b3d&_ss=r)**

### Base board variants

All three share the same STM32F303CCT6 MCU and the same LED/button pinout (PA1/PA2/PA3 LEDs, PA0 user button). They differ in IMU, USB, and debug probe:

| Revision | IMU | USB | Debug probe |
|---|---|---|---|
| **v2.0** | MPU6050 | Micro-USB + onboard CH340N USB-UART bridge | External ST-Link via SWD header |
| **v2.1** | BMI270 | USB-C + onboard CH340N USB-UART bridge | External ST-Link via SWD header |
| **v3.0** | MPU6050 | Micro-USB | **Onboard ST-Link/V3** (STLINK-V3MODS) — no external probe needed |

**Important: the IMU does not simply track the newest revision.** v2.1 introduced the BMI270, but **v3.0 reverts to the MPU6050** — its headline feature is an onboard ST-Link/V3 debugger, not a new sensor. Check which IMU chip is actually populated on your board (`MPU6050` vs `BMI270` silkscreen) rather than assuming from the revision number.

Examples that use the IMU select the driver at compile time via a macro in `Core/Inc/main.h`:
```c
#define NANO_BOARD_V2_1   /* BMI270 -- v2.1 boards only */
/* #define NANO_BOARD_V2_0 */   /* MPU6050 -- v2.0 AND v3.0 boards */
```
Define exactly one to match your board's actual IMU (not its revision number) — `NANO_BOARD_V2_0` covers both v2.0 and v3.0 hardware, since both carry the MPU6050. (The macro name reflects the sensor generation the driver targets, not a 1:1 mapping to every board revision; if v3.0's onboard ST-Link ever needs its own compile-time distinction — e.g. probe-specific tooling — a separate `NANO_BOARD_V3_0` macro could be added later, but no such firmware difference exists today.)

### LCD shield variants

Two shield options — same 1.28" round GC9A01A LCD panel, same CST816S capacitive touch controller and µ-SD card slot, different wiring to the MCU:

| Shield | LCD interface | GPIO pins used | Example |
|---|---|---|---|
| **Fastbit 1.28" TFT LCD (SPI) with CTP and µ-SD card slot** | `LCD_MOSI`/`LCD_MISO`/`LCD_SCL`/`LCD_CSX`/`LCD_DCX`/`LCD_RST`/`LCD_TE` | Handful of pins, frees up the rest of the port | `010_Flappy_Bird_SPI` |
| **Fastbit 1.28" TFT LCD (8-bit Parallel) with CTP and µ-SD card slot** | Full 8-bit data bus `LCD_DB0`-`LCD_DB7` + `LCD_WRX`/`LCD_RDX`/`LCD_DCX`/`LCD_CSX`/`LCD_RST`/`LCD_TE` | Consumes most of a GPIO port for the data bus, in exchange for faster transfers | `016_Flappy_Bird_8bit_Parallel` |

**Base board and LCD shield are orthogonal** — in principle any base board revision can be fitted with either shield. v2.0, v2.1, and v3.0 have all been paired with the SPI shield; the 8-bit parallel shield has been paired with a v2.0-generation base board (MPU6050, Micro-USB, external ST-Link — matching `016_Flappy_Bird_8bit_Parallel`'s use of the MPU6050 driver). An 8-bit-parallel pairing with v2.1 or v3.0 isn't confirmed — check your actual board before assuming one exists.

## Examples

All example projects live under [`Examples/`](Examples/), each a standalone STM32CubeIDE project with its own `.ioc`/`.project` and its own `README.md` with full build/run details. IMU-based examples marked ✅ below build for either board revision (v2.0/MPU6050 or v2.1/BMI270); the rest don't touch the IMU.

| # | Project | What it does | IMU |
|---|---------|---------------|:---:|
| 001 | [LED_Toggle](Examples/001_LED_Toggle) | Toggle onboard LEDs — basic GPIO output template |  |
| 002 | [UserButton_LED](Examples/002_UserButton_LED) | User button (polled) controls an LED |  |
| 003 | [UserButton_IT](Examples/003_UserButton_IT) | User button (interrupt-driven) controls an LED |  |
| 004 | [UART_Transmit_Receive](Examples/004_UART_Transmit_Receive) | Menu-driven UART TX/RX demo |  |
| 005 | [UART_LED_Control_IT](Examples/005_UART_LED_Control_IT) | Control LEDs over UART, interrupt-driven RX |  |
| 007 | [Tilt_LED_Controller](Examples/007_Tilt_LED_Controller) | Tilt the board to light different LEDs based on roll/pitch; roll/pitch also printed over a real UART console | ✅ |
| 008 | [SPI_Loopback](Examples/008_SPI_Loopback) | SPI loopback self-test |  |
| 009 | [PWM_LED](Examples/009_PWM_LED) | PWM-based LED brightness control |  |
| 010 | [Flappy_Bird_SPI](Examples/010_Flappy_Bird_SPI) | Flappy Bird on the round TFT LCD (SPI), tilt-controlled | ✅ |
| 011 | [USB_VCOM_Transmit](Examples/011_USB_VCOM_Transmit) | Streams RTC time over a USB CDC virtual COM port |  |
| 012 | [USB_HID_Mouse](Examples/012_USB_HID_Mouse) | Onboard gyro drives a USB HID mouse pointer, with Kalman smoothing, startup + drift-tracking bias calibration, deadzone, and a pointer-acceleration curve | ✅ |
| 013 | [MPU6050_3D_Model](Examples/013_MPU6050_3D_Model) | Streams IMU orientation over UART to a Processing sketch for 3D visualization |  |
| 015 | [Nano_LCD_TP](Examples/015_Nano_LCD_TP) | GC9A01A round LCD + CST816S capacitive touch panel bring-up |  |
| 016 | [Flappy_Bird_8bit_Parallel](Examples/016_Flappy_Bird_8bit_Parallel) | Flappy Bird on the round TFT LCD (8-bit parallel interface), tilt-controlled | ✅ |
| 017 | [SD_Card_Read_Write](Examples/017_SD_Card_Read_Write) | Read/write an SD card, driven over UART + the user button |  |
| 018 | [FOTA_STM32_nano](Examples/018_FOTA_STM32_nano) | WiFi firmware-over-the-air bootloader via an ESP8266 and a companion Flask update server |  |
| 019 | [OLED_News_Ticker](Examples/019_OLED_News_Ticker) | Scrolling news headlines on an OLED, pulled from the NYT API |  |
| 020 | [Bouncy_Ball](Examples/020_Bouncy_Ball) | Tilt-controlled ball physics toy on the round TFT LCD | ✅ |
| 021 | [Nano_watch_ui](Examples/021_Nano_watch_ui) | Work-in-progress smartwatch UI skeleton (currently just an LED blink) |  |
| — | [fastbit_nano_board_test](Examples/fastbit_nano_board_test) | Currently the Flappy Bird game reusing the same drivers as 010/016 — see its README for a note on a manufacturing test script (`nano_mfg_host.py`) that this firmware doesn't yet implement | ✅ |

## Getting started

1. Open the example project you want in STM32CubeIDE (`Examples/<project>/.project`).
2. If the project uses the IMU, pick the `NANO_BOARD_V2_0`/`NANO_BOARD_V2_1` macro in `Core/Inc/main.h` matching your board's actual IMU chip (see [Supported boards](#supported-boards) — v3.0 boards use `NANO_BOARD_V2_0`).
3. Build and flash — v2.0/v2.1 boards need an external ST-Link probe wired to the SWD header; v3.0 has one built in.
4. Each project's own `README.md` has details specific to that example (wiring notes, gameplay/usage instructions, required external services, etc.).
