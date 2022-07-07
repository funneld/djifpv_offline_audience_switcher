# DJI FPV Offline 50 to 25Mbit mode switcher

The Audience mode in the goggles menu becomes inaccessible when they're in 50Mbit mode from previous flights. Also you can't switch from 50 to 25Mbits without an Airunit connected. This package tries to solve that.


## Usage

Hold the "Channel down" button for 8-10 seconds to switch from 50 to the 25Mbit mode.


## Installation

Install:
- `download ipk`
- `adb push package-name.ipk /blackbox`
- `opkg install /blackbox/package-name.ipk`


Or manually:
- `make ipk`
- `adb push package-name.ipk`
- `opkg install /blackbox/package-name.ipk`

