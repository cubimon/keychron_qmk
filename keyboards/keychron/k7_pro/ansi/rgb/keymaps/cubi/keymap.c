/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// clang-format off
enum custom_keycodes {
  // mouse
  KC_MOUSE_UP,
  KC_MOUSE_DOWN,
  KC_MOUSE_LEFT,
  KC_MOUSE_RIGHT,
  KC_MOUSE_WHEEL_UP,
  KC_MOUSE_WHEEL_DOWN,
  KC_MOUSE_WHEEL_LEFT,
  KC_MOUSE_WHEEL_RIGHT,
  KC_MOUSE_BUTTON_LEFT,
  KC_MOUSE_BUTTON_RIGHT,
  KC_MOUSE_BUTTON_MIDDLE,
  KC_MOUSE_SPEED_0,
  KC_MOUSE_SPEED_1,
  KC_MOUSE_SPEED_2,
  KC_MOUSE_SPEED_3,
};

enum layers{
  MAC_BASE,
  WIN_BASE,
  MAC_FN1,
  WIN_FN1,
  FN2,
  META,
  CUBI_BASE,
  CUBI_ARROW,
  CUBI_MOUSE,
  CUBI_SYMBOL,
  CUBI_FUNCTION,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_68(
     LT(META, KC_ESC),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,           KC_DEL,
     KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,            KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN1),MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

[WIN_BASE] = LAYOUT_ansi_68(
     LT(META, KC_ESC),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,           KC_DEL,
     KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,            KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN1),MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

[MAC_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,            RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,            RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[FN2] = LAYOUT_ansi_68(
     KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[META] = LAYOUT_ansi_68(
     KC_TRNS,  TO(CUBI_BASE),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_BASE] = LAYOUT_ansi_68(
     QK_GRAVE_ESCAPE,        KC_1,            KC_2,           KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,             KC_0,            KC_MINS,                 KC_EQL,  KC_BSPC,           KC_DEL,
     LT(CUBI_MOUSE, KC_TAB), KC_Q,            KC_W,           KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,             KC_P,            KC_LBRC,                 KC_RBRC, KC_BSLS,           KC_HOME,
     MO(CUBI_SYMBOL),        LALT_T(KC_A),    KC_S,           KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,             LALT_T(KC_SCLN), LT(CUBI_ARROW, KC_QUOT),          KC_ENT,            KC_PGUP,
     LSFT_T(KC_ESC),         LCTL_T(KC_Z),    LSFT_T(KC_X),   KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  LSFT_T(KC_DOT),   LCTL_T(KC_SLSH),                                   KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL, KC_LOPTN,      KC_LCMMD,                                                      KC_SPC,                                         KC_RCMMD,        MO(MAC_FN1),             MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

[CUBI_ARROW] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_BSPC,  KC_UP,    KC_DEL,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PGUP,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_HOME,  KC_PGDN,  KC_END,   KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                 KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_MOUSE] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,              KC_TRNS,              KC_TRNS,               KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_MOUSE_UP,      KC_TRNS,          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_MOUSE_WHEEL_LEFT,  KC_MOUSE_WHEEL_DOWN,  KC_MOUSE_WHEEL_RIGHT,  KC_TRNS,  KC_TRNS,  KC_MOUSE_LEFT,    KC_MOUSE_DOWN,    KC_MOUSE_RIGHT,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_MOUSE_SPEED_0,     KC_MOUSE_SPEED_1,     KC_MOUSE_SPEED_2,      KC_TRNS,  KC_TRNS,  KC_MOUSE_SPEED_0, KC_MOUSE_SPEED_1, KC_MOUSE_SPEED_2, KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,              KC_TRNS,              KC_TRNS,               KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                                                     KC_TRNS,                                                        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_SYMBOL] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  MO(CUBI_FUNCTION), KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,           KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_KP_1,  KC_KP_2,  KC_KP_3,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,           KC_TRNS,                               KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_FUNCTION] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F19,  KC_F20,  KC_F21,  KC_F24,  KC_TRNS,  KC_TRNS,  KC_F7,   KC_F8,   KC_F9,   KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F16,  KC_F17,  KC_F18,  KC_F23,  KC_TRNS,  KC_TRNS,  KC_F4,   KC_F5,   KC_F6,   KC_TRNS,           KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F13,  KC_F14,  KC_F15,  KC_F22,  KC_TRNS,  KC_TRNS,  KC_F1,   KC_F2,   KC_F3,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                            KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),
};
