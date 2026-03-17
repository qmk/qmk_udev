# qmk_udev

A small program that udev uses to identify QMK keyboards, allowing user access to select endpoints.

# Installation

## Prebuilt Binaries

Download the binary for your architecture and `50-qmk.rules` from the [latest release](https://github.com/qmk/qmk_udev/releases/latest), then install them:

**x86-64:**

    wget https://github.com/qmk/qmk_udev/releases/latest/download/qmk_id-linuxX64 -O qmk_id

**ARM64:**

    wget https://github.com/qmk/qmk_udev/releases/latest/download/qmk_id-linuxARM64 -O qmk_id

**RISC-V 64:**

    wget https://github.com/qmk/qmk_udev/releases/latest/download/qmk_id-linuxRV64 -O qmk_id

Then install the binary and rules file:

    wget https://github.com/qmk/qmk_udev/releases/latest/download/50-qmk.rules
    sudo install -m755 -D qmk_id /usr/lib/udev/qmk_id
    sudo install -m644 -D 50-qmk.rules /etc/udev/rules.d/50-qmk.rules
    sudo udevadm control --reload
    sudo udevadm trigger

## Building from Source

Clone this repository and use `make` to build and install:

    make PREFIX=/usr/local
    sudo make install PREFIX=/usr/local
    sudo udevadm control --reload
    sudo udevadm trigger
