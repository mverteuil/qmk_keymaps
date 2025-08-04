/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "print.h"
#include <stdlib.h>

#define MIN_OTTER_DELAY 25  // ms between mouse movements
#define MAX_OTTER_DELAY 2000  // ms between mouse movements
#define OTTER_DELAY_ATOM 25 // ms

bool     otter_active = false;
int      otter_delay = 1000; // ms
uint32_t otter_timer  = 0;

// Mouse movement directions
uint16_t mouse_directions[4] = {
    KC_MS_UP,
    KC_MS_DOWN,
    KC_MS_LEFT,
    KC_MS_RIGHT,
};

enum custom_keycodes {
    OTTR = SAFE_RANGE, // Create a keycode to make your toggle initialize
    FAST,              // Faster ottering
    SLOW,              // Slower ottering
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case OTTR: // When you press custom OTTER keycode
            if (record->event.pressed) {
                otter_active = !otter_active;  // Toggle ottering
                otter_timer  = timer_read32(); // Reset otter timer
            }
            break;
        case FAST: // When you turn clockwise
            if (otter_delay > MIN_OTTER_DELAY) {
                otter_delay -= OTTER_DELAY_ATOM;
            }
            break;
        case SLOW: // When you turn counterclockwise
            if (otter_delay < MAX_OTTER_DELAY) {
                otter_delay += OTTER_DELAY_ATOM;
            }
            break;

    }
    uprintf("Otter | active: %d | speed: %d\n", otter_active, otter_delay);
    return true;
}

void matrix_scan_user(void) {
    if (otter_active) {
        // Check if it's been current delay milliseconds since the last ottering
        if (timer_elapsed32(otter_timer) > otter_delay) {
            uint16_t mouse_key = mouse_directions[rand() % 4];
            int moves_per_turn = rand() % 5;
            uprintf("Ottering %d times\n", moves_per_turn);
            for (int i = 0; i < moves_per_turn; i++) {
                SEND_STRING(SS_DELAY(1));
                tap_code(mouse_key);          // Send random mouse direction
            }
            otter_timer = timer_read32(); // Reset otter timer
        }
    }
}

// clang-format off
enum {
    _L0,
} keyboard_layers;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_ortho_1x1(
        OTTR
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_L0] = { ENCODER_CCW_CW(SLOW, FAST) },
};
#endif
// clang-format on