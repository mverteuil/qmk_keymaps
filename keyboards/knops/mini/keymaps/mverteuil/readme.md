# Matthew de Verteuil's Knops Mini Keymap

This keymap configures the Knops Mini with three main layers:

## Layers

### Layer 0: Media Controls
- Top row: Layer Access, Volume Up, Play/Pause
- Bottom row: Previous Track, Volume Down, Next Track

### Layer 1: Copy & Paste
- Top row: Layer Access, Undo (Ctrl+Z), Redo (Ctrl+Shift+Z)
- Bottom row: Cut (Ctrl+X), Copy (Ctrl+C), Paste (Ctrl+V)

### Layer 2: Spectacles Window Management
- Top row: Next Third (tap) / Layer Access (hold), Top Half, Maximize
- Bottom row: Previous Third, Bottom Half, Next Display

### Layer Select
- Access by holding the top-left key on any layer
- Top row: None, None, Reset/Boot
- Bottom row: Layer 0, Layer 1, Layer 2

## Features
- LED indicators for active layer
- Tap dance functionality for dual-purpose keys
- Optimized for macOS window management using Spectacles

## Build
```
qmk compile -kb knops/mini -km mverteuil
```