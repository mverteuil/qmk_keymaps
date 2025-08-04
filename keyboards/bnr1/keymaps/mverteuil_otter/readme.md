# Matthew de Verteuil's BNR1 'Otter' Layout

This layout turns the BNR1 into an automatic mouse mover (named "otter").

## Features
- Press the button to toggle automatic mouse movement on/off
- Rotate the encoder clockwise to increase movement speed
- Rotate the encoder counter-clockwise to decrease movement speed

This is useful for preventing screensavers or sleep mode from activating when you need to keep your computer awake but aren't actively using it.

## Build
```
qmk compile -kb bnr1 -km mverteuil_otter
```