// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 13
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 4
// Min 8, max 16
#define JOYSTICK_AXIS_RESOLUTION 8

#define JOYSTICK_HAS_HAT

#define PS_X        JS_0
#define PS_O        JS_1
#define PS_SQUARE   JS_2
#define PS_TRIANGLE JS_3
#define PS_L1       JS_4
#define PS_R1       JS_5
#define PS_L2       JS_6
#define PS_R2       JS_7
#define PS_SHARE    JS_8
#define PS_OPTIONS  JS_9
#define PS_L3       JS_10
#define PS_R3       JS_11
#define PS_HOME     JS_12

#define HAT_CENTER    -1
#define HAT_UP         0
#define HAT_NORTHEAST  1
#define HAT_RIGHT      2
#define HAT_SOUTHEAST  3
#define HAT_DOWN       4
#define HAT_SOUTHWEST  5
#define HAT_LEFT       6
#define HAT_NORTHWEST  7

#define JOYSTICK_AXES_PINS { F0, F1, F2, F3 }

#define DIRECT_PINS { \
    { D0, D1 } \
}
