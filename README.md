# Matthew de Verteuil's QMK Keyboard Layouts

This repository contains all my custom keyboard layouts for various keyboards.

## Overview

### Ortholinear Keyboards
- **Preonic**: Main keyboard with standard and 2x2u spacebar layouts
- **Boardwalk**: 65% ortholinear keyboard with Ergodox-style thumb keys

### Macropads
- **BM16S**: 16-key macropad
- **Knops Mini**: 6-key macropad
- **Binepad BN003**: 3-key macropad

### Rotary Encoders
- **Binepad BNR1**: Single rotary encoder with two variants:
  - **Pagey**: Auto page scrolling
  - **Otter**: Auto mouse movement
- **DMQ SPIN**: Multi-function rotary encoder macropad

## Features

Most of my ortholinear keyboard layouts include:
- Tap dance functionality for brackets, punctuation and special characters
- LOWER and RAISE layers with layer-specific sounds
- Media controls and navigation keys
- RGB lighting controls when available

## Building

To build any of these keymaps with QMK:

1. Clone this repository to `<qmk_firmware_dir>/users/mverteuil` and ensure the keyboard keymaps are in their proper directories
2. Compile with QMK CLI: 
```
qmk compile -kb <keyboard> -km <keymap>
```

Example:
```
qmk compile -kb preonic/rev3 -km mverteuil
```

## License

These keymaps are licensed under GPL-2.0, same as QMK firmware.