#include QMK_KEYBOARD_H

#define MAXIMIZ LALT(LGUI(KC_F))
#define NXTDSPL LCTL(LALT(LGUI(KC_RIGHT)))
#define BTMHALF LALT(LGUI(KC_DOWN))
#define TOPHALF LALT(LGUI(KC_UP))
#define NXTTHRD SS_LCTL(SS_LALT(SS_TAP(X_RIGHT)))
#define PRVTHRD LCTL(LALT(KC_LEFT))

#define LT_MSTP LT(_LAYER_SELECT, KC_MSTP)
#define LT_ESC LT(_LAYER_SELECT, KC_ESC)
#define LT_NXTH TD(TD_SPEC)

enum layer_led_mode {
    ALL_LAYERS_OFF = -1,
    LAYER_0,
    LAYER_1,
    LAYER_2,
    LAYER_3,
    LAYER_4,
    LAYER_5,
    ALL_LAYERS_ON,
};

enum mini_layers {
    _MEDIA,
    _COPYPASTA,
    _SPECTACLES,
    _LAYER_3,
    _LAYER_4,
    _LAYER_5,
    _LAYER_SELECT,
};

enum { TD_SPEC = 0 };

void td_spectacles_finish(tap_dance_state_t *state, void *user_data);
void td_spectacles_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for spectacles macro, hold for layer toggle */
    [TD_SPEC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spectacles_finish, td_spectacles_reset),
};

/*
 *   Key Layout
 *   _____   _____   _____
 *  |     | |     | |     |
 *  |  1  | |  2  | |  3  |
 *  |_____| |_____| |_____|
 *   _____   _____   _____
 *  |     | |     | |     |
 *  |  4  | |  5  | |  6  |
 *  |_____| |_____| |_____|
 *
 *  Hold 1 and:
 *    - press 4, 5, or 6 to change layers
 *    - press 3 to reset, or press and hold 3 to enter DFU programming mode
 *
 *  If something prevents you from using the above to reprogram, you can hold 3 while powering on as a fallback.
 */

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *  Layer 0 (Media Keys)
     *   _____   _____   _____
     *  |     | |     | |     |
     *  |Stop | |VolUp| |Play |
     *  |_____| |_____| |_____|
     *   _____   _____   _____
     *  |     | |     | |     |
     *  |Prev | |VolDn| |Next |
     *  |_____| |_____| |_____|
     *
     */
    [_MEDIA] = LAYOUT(
        LT_MSTP, KC_VOLU, KC_MPLY,
        KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /*
     *  Layer 1 (Copy and Paste Macros)
     *   _____   _____   _____
     *  |     | |     | |     |
     *	| ESC | |Ctl+Z| |CSf+Z|
     *	|_____| |_____| |_____|
     *   _____   _____   _____
     *  |     | |     | |     |
     *	|Ctl+X| |Ctl+C| |Ctl+V|
     *	|_____| |_____| |_____|
     *
     */

    [_COPYPASTA] = LAYOUT(
        LT_ESC,  LCTL(KC_Z), LCTL(LSFT(KC_Z)),
        LCTL(KC_X), LCTL(KC_C), LCTL(KC_V)
    ),

    /*
     *   Layer 2 (Spectacles Macros)
     *   _LT&_   _____   _____
     *  | Win | | Win | | Win |
     *  | Next| | Top | |Mximze
     *  |_1/3_| |_1/2_| |_____|
     *   _____	 _____	 _____
     *  | Win | | Win | | Win |
     *  | Prev| | Bot | | Next|
     *  |_1/3_| |_1/2_| |Displ|
     *
     */
    [_SPECTACLES] = LAYOUT(
        LT_NXTH,TOPHALF,MAXIMIZ,
        PRVTHRD,BTMHALF,NXTDSPL
    ),

    /*
     *  Layer 6 (Layer Select/Reset)
     *   _____   _____   _____
     *  |     | |     | |     |
     *  |None | |None | |Reset|
     *  |_____| |_____| |_____|
     *   _____   _____   _____
     *  |Layer| |Layer| |Layer|
     *  |  0  | |  1  | |  2  |
     *  |_____| |_____| |_____|
     *
     *  Layers 0, 1, and 2 have the top left button held to activate this layer.
     *  Then press the specific layer to switch to it.
     *
     */
    [_LAYER_SELECT] = LAYOUT(
        _______, _______, QK_BOOT,
        TO(_MEDIA),TO(_COPYPASTA),TO(_SPECTACLES)
    )
};
/* clang-format on */

/*
 *	Knops Mini LED Numbers:
 *   _____   _____   _____
 *  |     | |     | |     |
 *  |  1  | |  2  | |  3  |    <---
 *  |_____| |_____| |_____|       |      These LEDs are called 'Switch LEDs'
 *   _____   _____   _____        |----- To turn on/off these leds, use:
 *  |     | |     | |     |       |          set_switch_led( [1-6], [true/false]);
 *  |  4  | |  5  | |  6  |    <---
 *  |_____| |_____| |_____|
 *
 *	 < 0 >   < 1 >   < 2 >     <---      These front-LEDs are called 'Layer LEDs'
 *                                       To turn on/off these leds, use:
 *                                           set_layer_led( [0-2], [true/false] );
 */

void set_switch_led(int ledId, bool state) {
    switch (ledId) {
        case 1:
            writePinLow(D7);
            break;
        case 2:
            writePinLow(readPin(B7) ? C6 : C7);
            break;
        case 3:
            writePinLow(D4);
            break;
        case 4:
            writePinLow(E6);
            break;
        case 5:
            writePinLow(B4);
            break;
        case 6:
            writePinLow(D6);
            break;
    }
}

void set_layer_led(int layerLedMode) {
    writePinLow(B6);
    writePinHigh(D5);
    writePinLow(B0);

    switch (layerLedMode) {
        case ALL_LAYERS_OFF:
            break;
        case LAYER_0:
            writePinHigh(B6);
            break;
        case LAYER_1:
            writePinLow(D5);
            break;
        case LAYER_2:
            writePinHigh(B0);
            break;
        case LAYER_3:
            writePinHigh(B6);
            writePinLow(D5);
            break;
        case LAYER_4:
            writePinLow(D5);
            writePinHigh(B0);
            break;
        case LAYER_5:
            writePinHigh(B6);
            writePinHigh(B0);
            break;
        default:
            writePinHigh(B6);
            writePinLow(D5);
            writePinHigh(B0);
            break;
    }
}

void led_init_animation(void) {
    for (int i = ALL_LAYERS_OFF; i <= ALL_LAYERS_ON; i++) {
        set_layer_led(i);
        wait_ms(100);
    }

    set_layer_led(LAYER_0);
}

/*
 * This function led_set_layer gets called when you switch between layers.
 * It allows you to turn on and off leds for each different layer and do
 * other cool stuff.
 */
void led_set_layer(int layer) {
    switch (layer) {
        case ALL_LAYERS_OFF:
            set_switch_led(1, false);
            set_switch_led(2, false);
            set_switch_led(3, false);
            set_switch_led(4, false);
            set_switch_led(5, false);
            set_switch_led(6, false);

        case _LAYER_SELECT:
            set_switch_led(1, false);
            set_switch_led(2, false);
            set_switch_led(3, false);
            set_switch_led(4, true);
            set_switch_led(5, true);
            set_switch_led(6, true);
            break;

        default:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, true);
            set_switch_led(5, true);
            set_switch_led(6, true);
            break;
    }

    set_layer_led(layer);
}

void keyboard_pre_init_user(void) {
    setPinOutput(D7);  // Switch 1 LED
    setPinOutput(C6);  // Switch 2 LED Pin1
    setPinOutput(C7);  // Switch 2 LED Pin2
    setPinOutput(D4);  // Switch 3 LED
    setPinOutput(E6);  // Switch 4 LED
    setPinOutput(B4);  // Switch 5 LED
    setPinOutput(D6);  // Switch 6 LED
    setPinOutput(D5);  // Layer 0 LED
    setPinOutput(B6);  // Layer 1 LED
    setPinOutput(B0);  // Layer 2 LED

    led_init_animation();
}

// Runs on layer change, no matter where the change was initiated
layer_state_t layer_state_set_user(layer_state_t state) {
    set_layer_led(get_highest_layer(state));
    led_set_layer(get_highest_layer(state));
    return state;
}

void td_spectacles_finish(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(_LAYER_SELECT);
    } else {
        SEND_STRING(NXTTHRD);
    }
}

void td_spectacles_reset(tap_dance_state_t *state, void *user_data) { layer_off(_LAYER_SELECT); }