# BM16S Keymap - Matthew de Verteuil

This keymap configures the BM16S macropad as a numpad with RGB controls.

## Layers

### Base Layer (0)
A standard numpad layout with numbers 0-9, decimal point, comma, plus, minus, and enter.

### Function Layer (1)
Accessed by holding the top-right key, this layer provides RGB lighting controls and volume adjustment.

- Top row: Reset, RGB speed increase/decrease
- Second row: RGB mode cycle, RGB brightness controls, Volume up
- Third row: RGB toggle, RGB hue controls, Volume down
- Bottom row: RGB mode reverse cycle, RGB saturation controls, Mute

## Build
```
qmk compile -kb bm16s -km mverteuil
```