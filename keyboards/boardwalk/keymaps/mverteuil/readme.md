# Matthew de Verteuil's Boardwalk Layout

My custom keymap for the Boardwalk keyboard.

## Features
- Ortholinear 65% layout with Ergodox-style middle thumb keys
- QWERTY main layer
- LOWER and RAISE layers for symbols, numbers, and media controls
- ADJUST layer for RGB control and system functions
- ARROWS layer for arrow key navigation
- Tap dance functionality for brackets and punctuation
- Unicode cat emojis 🐱 and 🐈 in the corner keys

## Special Functions
- Triple-function brackets: tap once for ( ), twice for [ ], thrice for { }
- Dual-function space keys: space when tapped, LOWER or RAISE when held
- RGB control in the ADJUST layer
- Arrow keys navigation shortcut layer

## Build
```
qmk compile -kb boardwalk -km mverteuil
```