// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include"config.h"

#include QMK_KEYBOARD_H

enum custom_keycodes {
    PS_UP = SAFE_RANGE,
    PS_DN,
    PS_LF,
    PS_RT
};

bool l3_pressed = false;
bool r3_pressed = false;

void matrix_scan_user(void) {
    // L3
    bool l3_now = !gpio_read_pin(D0);
    if (l3_now != l3_pressed) {
        l3_pressed = l3_now;
        if (l3_pressed) {
            register_joystick_button(10);
        } else {
            unregister_joystick_button(10);
        }
    }

    // R3
    bool r3_now = !gpio_read_pin(D1);
    if (r3_now != r3_pressed) {
        r3_pressed = r3_now;
        if (r3_pressed) {
            register_joystick_button(11);
        } else {
            unregister_joystick_button(11);
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [0] = LAYOUT_60_ansi(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,      KC_8,    KC_9,      KC_0,    KC_MINS,    KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,      KC_I,    KC_O,      KC_P,    KC_LBRC,    KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,      KC_K,    KC_L,      KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,      KC_M,    KC_COMM,   KC_DOT,  KC_SLSH,             KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                    PS_HOME,              KC_RALT, KC_RGUI,            KC_APP,              KC_RCTL,
        PS_L1,   PS_L2,   PS_UP,   PS_DN,   PS_LF,   PS_RT,   PS_SHARE,  PS_OPTIONS, PS_O,    PS_SQUARE, PS_X,    PS_TRIANGLE, PS_R2,  PS_R1
    )
};

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F0, 900, 575, 285),
    JOYSTICK_AXIS_IN(F1, 900, 575, 285),
    JOYSTICK_AXIS_IN(F2, 900, 575, 285),
    JOYSTICK_AXIS_IN(F3, 900, 575, 285),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    static bool up = false, down = false, left = false, right = false;

    switch (keycode) {
        case PS_UP: up = record->event.pressed; break;
        case PS_DN: down = record->event.pressed; break;
        case PS_LF: left = record->event.pressed; break;
        case PS_RT: right = record->event.pressed; break;
        default: return true;
    }

    if (up && right)       joystick_set_hat(HAT_NORTHEAST);
    else if (down && right) joystick_set_hat(HAT_SOUTHEAST);
    else if (down && left)  joystick_set_hat(HAT_SOUTHWEST);
    else if (up && left)    joystick_set_hat(HAT_NORTHWEST);
    else if (up)            joystick_set_hat(HAT_UP);
    else if (down)          joystick_set_hat(HAT_DOWN);
    else if (left)          joystick_set_hat(HAT_LEFT);
    else if (right)         joystick_set_hat(HAT_RIGHT);
    else                    joystick_set_hat(HAT_CENTER);

    return false;
}
