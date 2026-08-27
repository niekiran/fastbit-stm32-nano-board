import csv
import datetime as dt
import sys
import time
import re
import serial
from serial.tools import list_ports

BAUD = 115200
READ_TIMEOUT = 0.2
CMD_TIMEOUT_S = 20

# CH340/CH340N common VID/PID. If your board enumerates differently, we still fallback by name.
CH340_VID = 0x1A86
CH340_PID = 0x7523

RE_TEST   = re.compile(r"^TEST:(.+)$")
RE_RESULT = re.compile(r"^RESULT:(PASS|FAIL)\b")
RE_DONE   = re.compile(r"^DONE$")

CSV_FILE = "nano_mfg_log.csv"

FIRMWARE_MENU = {
    "m": "Show menu",
    "d": "Default (Parallel LCD -> SPI LCD)",
    "a": "All tests",
    "1": "LED test",
    "2": "Button test",
    "3": "Oscillator ready test",
    "4": "MPU6050 test",
    "p": "Parallel LCD test",
    "s": "SPI LCD test",
    "q": "Stop",
}

def autodetect_port():
    ports = list_ports.comports()

    # 1) VID/PID match
    for p in ports:
        if p.vid == CH340_VID and p.pid == CH340_PID:
            return p.device

    # 2) fallback by description/hwid string
    for p in ports:
        desc = (p.description or "").lower()
        hwid = (p.hwid or "").lower()
        if "ch340" in desc or "ch340" in hwid or "1a86:7523" in hwid:
            return p.device

    # 3) if only one port exists, use it
    if len(ports) == 1:
        return ports[0].device

    return None

def open_serial(port):
    return serial.Serial(port, BAUD, timeout=READ_TIMEOUT)

def drain(ser, seconds=0.5):
    t0 = time.time()
    while time.time() - t0 < seconds:
        _ = ser.read(256)

def read_command_output(ser, timeout_s=CMD_TIMEOUT_S):
    t0 = time.time()
    lines = []
    result = None

    while time.time() - t0 < timeout_s:
        raw = ser.readline()
        if not raw:
            continue
        line = raw.decode(errors="replace").strip()
        if not line:
            continue

        print(line)
        lines.append(line)

        m = RE_RESULT.match(line)
        if m:
            result = m.group(1)

        if RE_DONE.match(line):
            break

    return result, lines

def log_csv(row):
    file_exists = False
    try:
        with open(CSV_FILE, "r", encoding="utf-8", newline=""):
            file_exists = True
    except FileNotFoundError:
        pass

    with open(CSV_FILE, "a", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=row.keys())
        if not file_exists:
            w.writeheader()
        w.writerow(row)

def host_menu():
    print("\n=== HOST MENU ===")
    for k, v in FIRMWARE_MENU.items():
        print(f"  {k}  - {v}")
    print("  x  - Exit")
    print("\nTip: press 'd' for default sequence (parallel then SPI).")

def main():
    port = sys.argv[1] if len(sys.argv) > 1 else autodetect_port()
    if not port:
        print("ERROR: Could not auto-detect serial port.")
        print("Run like: python nano_mfg_host.py COM6   (Windows)")
        print("or:       python nano_mfg_host.py /dev/ttyUSB0 (Linux)")
        sys.exit(2)

    operator = input("Operator name: ").strip() or "UNKNOWN"
    board_id  = input("Board ID (sticker/QR): ").strip() or "UNKNOWN"

    print(f"\nOpening {port} @ {BAUD} ...")
    with open_serial(port) as ser:
        # let board print boot menu
        time.sleep(0.4)
        drain(ser, 0.2)

        host_menu()

        while True:
            cmd = input("\nSelect test [default=d]> ").strip().lower()
            if cmd == "":
                cmd = "d"
            if cmd == "x":
                break
            if cmd not in FIRMWARE_MENU:
                print("Unknown command. Try again.")
                continue

            # send single char
            ser.write(cmd.encode("ascii", errors="ignore"))

            result, lines = read_command_output(ser)

            # summarize in CSV
            now = dt.datetime.now().isoformat(timespec="seconds")
            row = {
                "timestamp": now,
                "operator": operator,
                "board_id": board_id,
                "port": port,
                "cmd": cmd,
                "cmd_desc": FIRMWARE_MENU.get(cmd, ""),
                "result": result if result else "NO_RESULT",
                "log": " | ".join(lines[-80:]),  # keep last part of log
            }
            log_csv(row)

            print(f"\nHOST: logged -> {CSV_FILE}")
            print(f"HOST: command result -> {row['result']}")

if __name__ == "__main__":
    main()
