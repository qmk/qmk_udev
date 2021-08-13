# qmk_udev

A small program that udev uses to identify QMK keyboards.

# Installation

Clone this repository and use `make` to build and install this program:

    make PREFIX=/usr/local

# Linux Packages

This program is included in all of the [QMK packages for Linux](https://github.com/qmk/qmk_fpm).

# Binary Download

You can always download a statically compiled copy of the newest version from the [`latest` Release](https://github.com/qmk/qmk_udev/releases/latest) running one of these commands:

Wget:

    wget https://github.com/qmk/qmk_udev/releases/latest/download/qmk_id

Curl:

    curl -LO https://github.com/qmk/qmk_udev/releases/latest/download/qmk_id
