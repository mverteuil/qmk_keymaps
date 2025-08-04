# DMQ SPIN - Matthew de Verteuil's Keymap

Multi-function macropad with three encoders and multiple layers.

## Layers
1. **Spectacle**: Window management shortcuts
2. **Minecraft**: Minecraft mod shortcuts for Litematica, Tweakeroo, and MiniHud
3. **RGB**: RGB lighting controls

## Features
- 3 layers with different functions
- 3 encoders with layer-specific functions
- OLED display showing current layer and RGB mode
- RGB lighting indicating current layer

## Encoders
- **First Encoder**:
  - Spectacle: Up/Down navigation
  - Minecraft: Ctrl+MouseWheel scroll
  - RGB: Hue adjustment
  
- **Second Encoder**:
  - Spectacle: Page Up/Down
  - Minecraft: Litematica menu navigation
  - RGB: Saturation adjustment
  
- **Third Encoder**:
  - Spectacle: Volume control
  - Minecraft: Mod menu navigation
  - RGB: Brightness adjustment

## Build
```
qmk compile -kb dmq_spin -km mverteuil
```