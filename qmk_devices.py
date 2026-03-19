#!/usr/bin/env python3
"""List plugged-in devices that udev tagged as QMK (ID_QMK=1)."""

import subprocess
import sys


def parse_export_db(text: str) -> list[dict]:
    """Parse udevadm info --export-db output into a list of device dicts."""
    devices = []
    current: dict = {}

    for line in text.splitlines():
        if not line:
            if current:
                devices.append(current)
                current = {}
            continue

        tag, _, value = line.partition(": ")
        if tag == "N":
            current["node"] = "/dev/" + value
        elif tag == "E":
            key, _, val = value.partition("=")
            current.setdefault("env", {})[key] = val

    if current:
        devices.append(current)

    return devices


def main() -> None:
    try:
        result = subprocess.run(
            ["udevadm", "info", "--export-db"],
            capture_output=True,
            text=True,
            check=True,
        )
    except FileNotFoundError:
        print("error: udevadm not found", file=sys.stderr)
        sys.exit(1)
    except subprocess.CalledProcessError as e:
        print(f"error: udevadm failed: {e.stderr}", file=sys.stderr)
        sys.exit(1)

    devices = parse_export_db(result.stdout)

    qmk_devices = [
        d for d in devices if d.get("env", {}).get("ID_QMK") == "1" and "node" in d
    ]

    if not qmk_devices:
        print("No QMK devices found.")
        return

    for device in qmk_devices:
        env = device["env"]
        node = device["node"]
        vendor = env.get("ID_VENDOR", "")
        model = env.get("ID_MODEL", "")
        name = f"{vendor} {model}".strip() or "(unknown)"
        kind = env.get("ID_QMK_EP", "unknown")
        print(f"{node}  {name}  [{kind}]")


if __name__ == "__main__":
    main()
