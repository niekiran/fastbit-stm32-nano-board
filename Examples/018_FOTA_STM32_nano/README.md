# 018_FOTA_STM32_nano

## Project Overview
This project implements a WiFi-based firmware-over-the-air (FOTA) bootloader for the STM32 Nano board, using an ESP8266 as the WiFi modem. On every boot, it connects to WiFi, checks a firmware server for the latest available version, downloads and flashes a new application image if one is available, then jumps into the application.

## How it works
1. Connects to WiFi via the ESP8266 (`ESP8266.c`) using the `SSID`/`PASSWORD` defined in `main.c`.
2. Queries the firmware server (see `stm32_fw_web_server - Update - frontend/`, a Flask app) for the current published firmware version and program ID (`firmware_parse.c`, `version.c`).
3. Compares that version against the one stored in flash (`FIRMWARE_VERSION_PAGE_ADDRESS`):
   - If flash is uninitialized, stores the current version and downloads firmware.
   - If the stored and current versions differ, updates the stored version and downloads the new firmware.
   - Otherwise, boots the existing application unchanged.
4. Jumps to the downloaded/existing application (`jump_application()` in `main.c`) and resets.

## Components
- **STM32 Nano board**: Runs the bootloader logic and performs the flash write.
- **ESP8266 WiFi module**: Provides the WiFi/HTTP transport, driven over UART via AT commands.
- **`stm32_fw_web_server - Update - frontend/`**: A separate Flask server (see its own `README.md`) that serves `.bin` firmware files and version/program IDs over a REST API, with a web dashboard for uploading new firmware.

## UART wiring
- **USART1** (PA9/PA10, 115200 baud): PC/debug console — all `print_pc(...)` diagnostic output.
- **USART3** (PB10/PB11): ESP8266 AT-command interface (`RCC_USART3CLKSOURCE_SYSCLK`).

## How to Run
1. Start the firmware server: `cd "stm32_fw_web_server - Update - frontend"`, `pip install -r requirements.txt`, `python app.py`.
2. Upload a `.bin` firmware image via the server's web dashboard at `http://localhost:5000/dashboard`.
3. Set `SSID`/`PASSWORD` in `Core/Src/main.c` to your WiFi network's credentials, and point the ESP8266/firmware-server connection details at your server's address.
4. Flash this bootloader to the STM32 Nano board and power it on.
5. Watch USART1 (115200 baud) for connection and update-check progress; the board downloads and flashes new firmware automatically when the server's version differs from what's stored on the board.
