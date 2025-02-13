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
#include "pws.h"
#include "k7_pro.h"

// clang-format off

// mouse speeds
#define MOUSE_SPEED_DEFAULT 1000l
#define MOUSE_SPEED_0 100l
#define MOUSE_SPEED_1 500l
#define MOUSE_SPEED_2 2000l

#define MOUSE_WHEEL_SPEED_DEFAULT 30l
#define MOUSE_WHEEL_SPEED_0 10l
#define MOUSE_WHEEL_SPEED_1 50l
#define MOUSE_WHEEL_SPEED_2 100l

#define TIME_BETWEEN_MOVEMENT_DEFAULT 1000000l / MOUSE_SPEED_DEFAULT
#define TIME_BETWEEN_MOVEMENT_0 1000000l / MOUSE_SPEED_0
#define TIME_BETWEEN_MOVEMENT_1 1000000l / MOUSE_SPEED_1
#define TIME_BETWEEN_MOVEMENT_2 1000000l / MOUSE_SPEED_2

#define TIME_BETWEEN_WHEEL_MOVEMENT_DEFAULT 1000000l / MOUSE_WHEEL_SPEED_DEFAULT
#define TIME_BETWEEN_WHEEL_MOVEMENT_0 1000000l / MOUSE_WHEEL_SPEED_0
#define TIME_BETWEEN_WHEEL_MOVEMENT_1 1000000l / MOUSE_WHEEL_SPEED_1
#define TIME_BETWEEN_WHEEL_MOVEMENT_2 1000000l / MOUSE_WHEEL_SPEED_2

struct MouseState {
  bool up;
  bool down;
  bool left;
  bool right;
  bool wheel_up;
  bool wheel_down;
  bool wheel_left;
  bool wheel_right;
  bool button_left;
  bool button_right;
  bool button_middle;
  uint32_t time_between_movement;
  uint32_t time_between_wheel_movement;
  uint32_t last_movement_time;
  uint32_t last_wheel_movement_time;
} mouse_state = {
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  TIME_BETWEEN_MOVEMENT_DEFAULT,
  TIME_BETWEEN_WHEEL_MOVEMENT_DEFAULT,
  0,
  0,
};

enum custom_keycodes {
  // mouse
  KC_MOUSE_UP = NEW_SAFE_RANGE,
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
  KC_WIN_PW,
  KC_AUML, // ä
  KC_OUML, // ö
  KC_UUML, // ü
  KC_SSS, // ß
  UC_EURO, // €
};

enum layers{
  MAC_BASE,
  WIN_BASE,
  CUBI_BASE,
  MAC_FN1,
  WIN_FN1,
  FN2,
  META,
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
     QK_GRAVE_ESCAPE,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,                     KC_MINS,                 KC_EQL,  KC_BSPC,          KC_DEL,
     LT(CUBI_MOUSE, KC_TAB), KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,                     KC_LBRC,                 KC_RBRC, KC_BSLS,          KC_HOME,
     MO(CUBI_SYMBOL),        KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     LT(CUBI_ARROW, KC_SCLN),  LT(CUBI_ARROW, KC_QUOT),          KC_ENT,           KC_PGUP,
     LSFT_T(KC_ESC),         KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                                                    KC_RSFT, KC_UP,   KC_PGDN,
     KC_LCTL,                KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,                  MO(MAC_FN1),             MO(FN2), KC_LEFT, KC_DOWN, KC_RGHT),

[CUBI_BASE] = LAYOUT_ansi_68(
     QK_GRAVE_ESCAPE,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,                     KC_MINS,                 KC_EQL,  KC_BSPC,          KC_DEL,
     LT(CUBI_MOUSE, KC_TAB), KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,                     KC_LBRC,                 KC_RBRC, KC_BSLS,          KC_HOME,
     MO(CUBI_SYMBOL),        KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     LT(CUBI_ARROW, KC_SCLN),  LT(CUBI_ARROW, KC_QUOT),          KC_ENT,           KC_PGUP,
     LSFT_T(KC_ESC),         KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                                                    KC_RSFT, KC_UP,   KC_PGDN,
     KC_LCTL,                KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,                  MO(MAC_FN1),             MO(FN2), KC_LEFT, KC_DOWN, KC_RGHT),

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
     KC_TILD,  KC_F1,          KC_F2,         KC_F3,         KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,   KC_TRNS,            KC_TRNS,
     KC_TRNS,  TO(CUBI_BASE),  TO(MAC_BASE),  TO(WIN_BASE),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_WIN_PW, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  DM_REC1,        DM_RSTP,       DM_PLY1,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  DM_REC2,        DM_RSTP,       DM_PLY2,       KC_TRNS,  BAT_LVL,  KC_TRNS,  KC_TRNS,  KC_APP,   KC_RALT,  KC_RCTL,                       KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,                                          KC_TRNS,                                KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[META] = LAYOUT_ansi_68(
     KC_TRNS,  TO(CUBI_BASE),  TO(MAC_BASE),  TO(WIN_BASE),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,        KC_TRNS,                                          KC_TRNS,                                KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

// [CUBI_BASE] = LAYOUT_ansi_68(
//      QK_GRAVE_ESCAPE,        KC_1,            KC_2,           KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,             KC_0,            KC_MINS,                 KC_EQL,  KC_BSPC,           KC_DEL,
//      LT(CUBI_MOUSE, KC_TAB), KC_Q,            KC_W,           KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,             KC_P,            KC_LBRC,                 KC_RBRC, KC_BSLS,           KC_HOME,
//      MO(CUBI_SYMBOL),        LALT_T(KC_A),    KC_S,           KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,             LALT_T(KC_SCLN), LT(CUBI_ARROW, KC_QUOT),          KC_ENT,            KC_PGUP,
//      LSFT_T(KC_ESC),         LCTL_T(KC_Z),    LSFT_T(KC_X),   KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  LSFT_T(KC_DOT),   LCTL_T(KC_SLSH),                                   KC_RSFT,  KC_UP,   KC_PGDN,
//      KC_LCTL, KC_LOPTN,      KC_LCMMD,                                                      KC_SPC,                                         KC_RCMMD,        MO(MAC_FN1),             MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

[CUBI_ARROW] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PGUP,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_BSPC,  KC_UP,    KC_DEL,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_APP,   KC_HOME,  KC_PGDN,  KC_END,    KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                 KC_LCTL,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_MOUSE] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,              KC_MOUSE_WHEEL_UP,    KC_TRNS,               KC_TRNS,  KC_TRNS,                KC_TRNS,          KC_MOUSE_UP,      KC_TRNS,          KC_TRNS,                KC_SSS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_MOUSE_WHEEL_LEFT,  KC_MOUSE_WHEEL_DOWN,  KC_MOUSE_WHEEL_RIGHT,  KC_TRNS,  KC_MOUSE_BUTTON_MIDDLE, KC_MOUSE_LEFT,    KC_MOUSE_DOWN,    KC_MOUSE_RIGHT,   KC_MOUSE_BUTTON_RIGHT,  KC_UUML, KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_MOUSE_SPEED_0,     KC_MOUSE_SPEED_1,     KC_MOUSE_SPEED_2,      KC_TRNS,  KC_TRNS,                KC_MOUSE_SPEED_0, KC_MOUSE_SPEED_1, KC_MOUSE_SPEED_2, KC_OUML,                KC_AUML,           KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,              KC_TRNS,              KC_TRNS,               KC_TRNS,  KC_TRNS,                KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                                   KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                                                     KC_MOUSE_BUTTON_LEFT,                                                         KC_TRNS,                KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_SYMBOL] = LAYOUT_ansi_68(
     KC_TRNS,  QK_UNICODE_MODE_MACOS,           QK_UNICODE_MODE_LINUX, QK_UNICODE_MODE_WINDOWS,  QK_UNICODE_MODE_WINCOMPOSE,  KC_TRNS,  KC_TRNS,  KC_NUM,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,                         KC_KP_7,               KC_KP_8,                  KC_KP_9,                     KC_TRNS,  KC_TRNS,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  MO(CUBI_FUNCTION),               KC_KP_4,               KC_KP_5,                  KC_KP_6,                     KC_KP_0,  KC_TRNS,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_KP_0,  KC_TRNS,            KC_PSCR,            KC_TRNS,
     KC_TRNS,  KC_TRNS,                         KC_KP_1,               KC_KP_2,                  KC_KP_3,                     KC_TRNS,  KC_TRNS,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,                         KC_TRNS,                                                                                KC_LCTL,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[CUBI_FUNCTION] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F19,  KC_F20,  KC_F21,  KC_F24,  KC_TRNS,  KC_F7,    KC_F8,   KC_F9,   KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F16,  KC_F17,  KC_F18,  KC_F23,  KC_TRNS,  KC_F4,    KC_F5,   KC_F6,   KC_F11,  KC_TRNS,          KC_TRNS,          KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_F13,  KC_F14,  KC_F15,  KC_F22,  KC_TRNS,  KC_F1,    KC_F2,   KC_F3,   KC_F10,                    KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                            KC_LCTL,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /*if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }*/

  // reset time for mouse
  if (keycode >= KC_MOUSE_UP && keycode <= KC_MOUSE_RIGHT) {
    if (!mouse_state.up && !mouse_state.down && !mouse_state.left && !mouse_state.right) {
      mouse_state.last_movement_time = timer_read32();
    }
  }
  if (keycode >= KC_MOUSE_WHEEL_UP && keycode <= KC_MOUSE_WHEEL_RIGHT) {
    if (!mouse_state.wheel_up && !mouse_state.wheel_down && !mouse_state.wheel_left && !mouse_state.wheel_right) {
      mouse_state.last_wheel_movement_time = timer_read32();
    }
  }

  // number of pressed speed buttons
  static int mouse_speed_buttons_pressed = 0;

  switch (keycode) {
    case KC_MOUSE_UP:
      mouse_state.up = record->event.pressed;
      break;
    case KC_MOUSE_DOWN:
      mouse_state.down = record->event.pressed;
      break;
    case KC_MOUSE_LEFT:
      mouse_state.left = record->event.pressed;
      break;
    case KC_MOUSE_RIGHT:
      mouse_state.right = record->event.pressed;
      break;
    case KC_MOUSE_WHEEL_UP:
      mouse_state.wheel_up = record->event.pressed;
      break;
    case KC_MOUSE_WHEEL_DOWN:
      mouse_state.wheel_down = record->event.pressed;
      break;
    case KC_MOUSE_WHEEL_LEFT:
      mouse_state.wheel_left = record->event.pressed;
      break;
    case KC_MOUSE_WHEEL_RIGHT:
      mouse_state.wheel_right = record->event.pressed;
      break;
    // TODO: somehow left and right are mixed
    case KC_MOUSE_BUTTON_LEFT:
      mouse_state.button_right = record->event.pressed;
      break;
    case KC_MOUSE_BUTTON_RIGHT:
      mouse_state.button_left = record->event.pressed;
      break;
    case KC_MOUSE_BUTTON_MIDDLE:
      mouse_state.button_middle = record->event.pressed;
      break;
    case KC_MOUSE_SPEED_0:
      if (record->event.pressed) {
        mouse_state.time_between_movement = TIME_BETWEEN_MOVEMENT_0;
        mouse_state.time_between_wheel_movement = TIME_BETWEEN_WHEEL_MOVEMENT_0;
        mouse_speed_buttons_pressed++;
      } else {
        mouse_speed_buttons_pressed--;
      }
      break;
    case KC_MOUSE_SPEED_1:
      if (record->event.pressed) {
        mouse_state.time_between_movement = TIME_BETWEEN_MOVEMENT_1;
        mouse_state.time_between_wheel_movement = TIME_BETWEEN_WHEEL_MOVEMENT_1;
        mouse_speed_buttons_pressed++;
      } else {
        mouse_speed_buttons_pressed--;
      }
      break;
    case KC_MOUSE_SPEED_2:
      if (record->event.pressed) {
        mouse_state.time_between_movement = TIME_BETWEEN_MOVEMENT_2;
        mouse_state.time_between_wheel_movement = TIME_BETWEEN_WHEEL_MOVEMENT_2;
        mouse_speed_buttons_pressed++;
      } else {
        mouse_speed_buttons_pressed--;
      }
      break;
    case KC_WIN_PW:
    if (record->event.pressed) {
        SEND_STRING(WIN_PW);
      }
      break;
      case KC_AUML:
    if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
            keyboard_report->mods & MOD_BIT(KC_RSFT)) {
          send_unicode_string("Ä");
        } else {
          send_unicode_string("ä");
        }
      }
      return false;
    case KC_OUML:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
            keyboard_report->mods & MOD_BIT(KC_RSFT)) {
          send_unicode_string("Ö");
        } else {
          send_unicode_string("ö");
        }
      }
      return false;
    case KC_UUML:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
            keyboard_report->mods & MOD_BIT(KC_RSFT)) {
          send_unicode_string("Ü");
        } else {
          send_unicode_string("ü");
        }
      }
      return false;
    case KC_SSS:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
            keyboard_report->mods & MOD_BIT(KC_RSFT)) {
          send_unicode_string("ẞ");
        } else {
          send_unicode_string("ß");
        }
      }
      return false;

  }

  // reset mouse speed to default if no speed button is pressed
  if (mouse_speed_buttons_pressed == 0) {
    mouse_state.time_between_movement = TIME_BETWEEN_MOVEMENT_DEFAULT;
    mouse_state.time_between_wheel_movement = TIME_BETWEEN_WHEEL_MOVEMENT_DEFAULT;
  }

  return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user() {
  uint32_t now = timer_read32();
  report_mouse_t mouseReport = pointing_device_get_report();

  // mouse movement
  uint32_t movement_steps = 0;
  if (mouse_state.up || mouse_state.down || mouse_state.left || mouse_state.right) {
    uint32_t time_diff_movement = TIMER_DIFF_32(now, mouse_state.last_movement_time);
    movement_steps = (time_diff_movement * 1000l) / mouse_state.time_between_movement;
    mouse_state.last_movement_time += (movement_steps * mouse_state.time_between_movement) / 1000l;
  }
  if (movement_steps > 127) movement_steps = 127;
  if (mouse_state.up) {
    mouseReport.y = -movement_steps;
  } else if (mouse_state.down) {
    mouseReport.y = movement_steps;
  }
  if (mouse_state.left) {
    mouseReport.x = -movement_steps;
  } else if (mouse_state.right) {
    mouseReport.x = movement_steps;
  }
  // mouse wheel movement
  uint32_t wheel_movement_steps = 0;
  if (mouse_state.wheel_up || mouse_state.wheel_down || mouse_state.wheel_left || mouse_state.wheel_right) {
    uint32_t time_diff_wheel_movement = TIMER_DIFF_32(now, mouse_state.last_wheel_movement_time);
    wheel_movement_steps = (time_diff_wheel_movement * 1000l) / mouse_state.time_between_wheel_movement;
    mouse_state.last_wheel_movement_time += (wheel_movement_steps * mouse_state.time_between_wheel_movement) / 1000l;
  }
  if (wheel_movement_steps > 127) wheel_movement_steps = 127;
  if (mouse_state.wheel_up) {
    mouseReport.v = wheel_movement_steps;
  } else if (mouse_state.wheel_down) {
    mouseReport.v = -wheel_movement_steps;
  }
  if (mouse_state.wheel_left) {
    mouseReport.h = -wheel_movement_steps;
  } else if (mouse_state.wheel_right) {
    mouseReport.h = wheel_movement_steps;
  }
  // buttons
  if (mouse_state.button_left) {
    mouseReport.buttons |= MOUSE_BTN2;
  } else {
    mouseReport.buttons &= ~MOUSE_BTN2;
  }
  if (mouse_state.button_right) {
    mouseReport.buttons |= MOUSE_BTN1;
  } else {
    mouseReport.buttons &= ~MOUSE_BTN1;
  }
  if (mouse_state.button_middle) {
    mouseReport.buttons |= MOUSE_BTN3;
  } else {
    mouseReport.buttons &= ~MOUSE_BTN3;
  }

  pointing_device_set_report(mouseReport);
}
