#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MEH(KC_M),
        LCTL(LGUI(LALT(KC_RIGHT))),
        LGUI(LSFT(KC_G))
    ),
    [1] = LAYOUT(
        KC_NO,
        KC_NO,
        KC_NO
    ),
    [2] = LAYOUT(
        KC_NO,
        KC_NO,
        KC_NO
    )
};