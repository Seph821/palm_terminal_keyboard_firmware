// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "config.h"
#include "analog.h"

// Define proper, unique custom keycodes for all joystick functions
enum custom_keycodes {
    PS_UP = SAFE_RANGE,
    PS_DN,
    PS_LF,
    PS_RT,
    KEY_PS_X,
    KEY_PS_O,
    KEY_PS_SQUARE,
    KEY_PS_TRIANGLE,
    KEY_PS_L1,
    KEY_PS_R1,
    KEY_PS_L2,
    KEY_PS_R2,
    KEY_PS_SHARE,
    KEY_PS_OPTIONS
};

// Tracking states
static uint8_t dpad_state = 0;
#define BIT_UP    (1 << 0)
#define BIT_DOWN  (1 << 1)
#define BIT_LEFT  (1 << 2)
#define BIT_RIGHT (1 << 3)

bool l3_pressed = false;
bool r3_pressed = false;

void matrix_scan_user(void) {
    // L3 (Direct Pin D0)
    bool l3_now = !gpio_read_pin(D0);
    if (l3_now != l3_pressed) {
        l3_pressed = l3_now;
        if (l3_pressed) register_joystick_button(10);
        else unregister_joystick_button(10);
    }

    // R3 (Direct Pin D1)
    bool r3_now = !gpio_read_pin(D1);
    if (r3_now != r3_pressed) {
        r3_pressed = r3_now;
        if (r3_pressed) register_joystick_button(11);
        else unregister_joystick_button(11);
    }
}

// Clean Hat/D-pad updating state routine
void update_joystick_hat(void) {
    if ((dpad_state & BIT_UP) && (dpad_state & BIT_RIGHT))        joystick_set_hat(HAT_NORTHEAST);
    else if ((dpad_state & BIT_DOWN) && (dpad_state & BIT_RIGHT)) joystick_set_hat(HAT_SOUTHEAST);
    else if ((dpad_state & BIT_DOWN) && (dpad_state & BIT_LEFT))  joystick_set_hat(HAT_SOUTHWEST);
    else if ((dpad_state & BIT_UP) && (dpad_state & BIT_LEFT))    joystick_set_hat(HAT_NORTHWEST);
    else if (dpad_state & BIT_UP)                                 joystick_set_hat(HAT_UP);
    else if (dpad_state & BIT_DOWN)                               joystick_set_hat(HAT_DOWN);
    else if (dpad_state & BIT_LEFT)                               joystick_set_hat(HAT_LEFT);
    else if (dpad_state & BIT_RIGHT)                              joystick_set_hat(HAT_RIGHT);
    else                                                          joystick_set_hat(HAT_CENTER);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;

    switch (keycode) {
        // D-PAD
        case PS_UP: if (pressed) dpad_state |= BIT_UP;    else dpad_state &= ~BIT_UP;    update_joystick_hat(); return false;
        case PS_DN: if (pressed) dpad_state |= BIT_DOWN;  else dpad_state &= ~BIT_DOWN;  update_joystick_hat(); return false;
        case PS_LF: if (pressed) dpad_state |= BIT_LEFT;  else dpad_state &= ~BIT_LEFT;  update_joystick_hat(); return false;
        case PS_RT: if (pressed) dpad_state |= BIT_RIGHT; else dpad_state &= ~BIT_RIGHT; update_joystick_hat(); return false;

        // Joystick Buttons Interceptions (Indices match your config.h map layout)
        case KEY_PS_X:        if (pressed) register_joystick_button(0);  else unregister_joystick_button(0);  return false;
        case KEY_PS_O:        if (pressed) register_joystick_button(1);  else unregister_joystick_button(1);  return false;
        case KEY_PS_SQUARE:   if (pressed) register_joystick_button(2);  else unregister_joystick_button(2);  return false;
        case KEY_PS_TRIANGLE: if (pressed) register_joystick_button(3);  else unregister_joystick_button(3);  return false;
        case KEY_PS_L1:       if (pressed) register_joystick_button(4);  else unregister_joystick_button(4);  return false;
        case KEY_PS_R1:       if (pressed) register_joystick_button(5);  else unregister_joystick_button(5);  return false;
        case KEY_PS_L2:       if (pressed) register_joystick_button(6);  else unregister_joystick_button(6);  return false;
        case KEY_PS_R2:       if (pressed) register_joystick_button(7);  else unregister_joystick_button(7);  return false;
        case KEY_PS_SHARE:    if (pressed) register_joystick_button(8);  else unregister_joystick_button(8);  return false;
        case KEY_PS_OPTIONS:  if (pressed) register_joystick_button(9);  else unregister_joystick_button(9);  return false;
        
        default: return true; // Pass all normal keyboard inputs through natively
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,       KC_8,    KC_9,       KC_0,    KC_MINS,    KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,       KC_I,    KC_O,       KC_P,    KC_LBRC,    KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,       KC_K,    KC_L,       KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,       KC_M,    KC_COMM,    KC_DOT,  KC_SLSH,             KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                    KC_NO,                 KC_RALT, MO(1),               KC_APP,              KC_RCTL,
        
        // Swapped macros out for our safe custom keycodes defined above
        KEY_PS_L1, KEY_PS_L2, PS_UP, PS_DN, PS_LF, PS_RT, KEY_PS_SHARE, KEY_PS_OPTIONS, KEY_PS_O, KEY_PS_SQUARE, KEY_PS_X, KEY_PS_TRIANGLE, KEY_PS_R2, KEY_PS_R1
    ),
    [1] = LAYOUT_60_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,     KC_F7,      KC_F8,   KC_F9,     KC_F10,     KC_F11,     KC_F12,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_UP,   KC_E,     KC_R,    KC_T,    KC_Y,      KC_U,       KC_I,    KC_O,      KC_PSCR,    KC_SCRL,    KC_PAUS, KC_BSLS,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_F,    KC_G,    KC_H,      KC_J,       KC_K,    KC_INS,    KC_HOME,    KC_PGUP,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,      KC_N,       KC_M,    KC_DEL,    KC_END,     KC_PGDN,             KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                    KC_NO,                 KC_RALT, KC_TRNS,               KC_APP,              KC_RCTL,
        
        KEY_PS_L1, KEY_PS_L2, PS_UP, PS_DN,  PS_LF, PS_RT, KEY_PS_SHARE, KEY_PS_OPTIONS, KEY_PS_O, KEY_PS_SQUARE, KEY_PS_X, KEY_PS_TRIANGLE, KEY_PS_R2, KEY_PS_R1
    )
};

// Joystick hardware axes configuration remain unchanged...
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F0, 900, 575, 285),
    JOYSTICK_AXIS_IN(F1, 900, 575, 285),
    JOYSTICK_AXIS_IN(F2, 900, 575, 285),
    JOYSTICK_AXIS_IN(F3, 900, 575, 285),
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Only move the mouse if Layer 2 is currently active
    if (IS_LAYER_ON(1)) {
        // Read joystick values (0-1023)
        uint16_t x_val = adc_read(F0);
        uint16_t y_val = adc_read(F1);
        
        // Convert to relative movements and apply deadzones/scaling
        mouse_report.x = (x_val - 512) / 4; 
        mouse_report.y = (y_val - 512) / 4; 
    }
    
    // Returns empty/zeroed mouse reports if Layer 2 is inactive
    return mouse_report;
}