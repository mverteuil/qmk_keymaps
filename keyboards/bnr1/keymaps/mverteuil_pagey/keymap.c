/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "print.h"
#include <stdlib.h>

#define MIN_PAGEY_DELAY 25  // ms between page movements
#define MAX_PAGEY_DELAY 2000  // ms between page movements
#define PAGEY_DELAY_ATOM 25 // ms

bool     pagey_active = false;
int      pagey_delay = 1000; // ms
uint32_t pagey_timer = 0;

// Page movement keys
uint16_t page_directions[4] = {
    KC_PAGE_UP,
    KC_PAGE_UP,
    KC_PAGE_UP,
    KC_PAGE_UP,
};

enum custom_keycodes {
    PAGEY = SAFE_RANGE, // Toggle page movement
    FAST,               // Faster paging
    SLOW,               // Slower paging
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case PAGEY: // When you press custom PAGEY keycode
            if (record->event.pressed) {
                pagey_active = !pagey_active;  // Toggle page movement
                pagey_timer  = timer_read32(); // Reset pagey timer
            }
            break;
        case FAST: // When you turn clockwise
            if (pagey_delay > MIN_PAGEY_DELAY) {
                pagey_delay -= PAGEY_DELAY_ATOM;
            }
            break;
        case SLOW: // When you turn counterclockwise
            if (pagey_delay < MAX_PAGEY_DELAY) {
                pagey_delay += PAGEY_DELAY_ATOM;
            }
            break;

    }
    uprintf("Pagey | active: %d | speed: %d\n", pagey_active, pagey_delay);
    return true;
}

void matrix_scan_user(void) {
    if (pagey_active) {
        // Check if it's been current delay milliseconds since the last page movement
        if (timer_elapsed32(pagey_timer) > pagey_delay) {
            uint16_t page_key = page_directions[rand() % 4];
            int moves_per_turn = rand() % 5;
            uprintf("Pagey moves %d times\n", moves_per_turn);
            for (int i = 0; i < moves_per_turn; i++) {
                SEND_STRING(SS_DELAY(1));
                tap_code(page_key);          // Send random page direction
            }
            pagey_timer = timer_read32(); // Reset pagey timer
        }
    }
}

// clang-format off
enum {
    _L0,
} keyboard_layers;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_ortho_1x1(
        PAGEY
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_L0] = { ENCODER_CCW_CW(SLOW, FAST) },
};
#endif
// clang-format on