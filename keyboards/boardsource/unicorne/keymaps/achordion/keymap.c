#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "features/achordion.h"

enum layer_names {
    _BAS,
    _NUM,
    _NAV,
    _MED,
    _BRC,
    _SYM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BAS] = LAYOUT_split_3x6_3(
      KC_ESC,       KC_Q,         KC_W,         KC_E,             KC_R,             KC_T,      KC_Y,     KC_U,             KC_I,         KC_O,         KC_P,            KC_LBRC, 
      KC_TAB,       LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D),     LSFT_T(KC_F),     KC_G,      KC_H,     RSFT_T(KC_J),     RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT, 
      KC_LSFT,      KC_Z,         KC_X,         KC_C,             KC_V,             KC_B,      KC_N,     KC_M,             KC_COMM,      KC_DOT,       KC_SLSH,         KC_RBRC, 
                                                LT(_NUM,KC_CAPS), MO(_NAV),         MO(_BRC),  KC_ENT,   LT(_SYM,KC_SPC),  MO(_MED)
      ),
    [_NUM] = LAYOUT_split_3x6_3(
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_7,     KC_8,     KC_9,   KC_NO,  KC_NO, 
      KC_NO,    KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  KC_NO,    KC_NO,    KC_4,     KC_5,     KC_6,   KC_0,   KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_1,     KC_2,     KC_3,   KC_NO,  KC_NO, 
                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
    [_NAV] = LAYOUT_split_3x6_3(
      KC_TRNS, KC_TRNS,     KC_TRNS,    SGUI(KC_LBRC),  SGUI(KC_RBRC),  KC_TRNS,  KC_TRNS,  RGUI(KC_LEFT),  KC_UP,    RGUI(KC_RGHT),  KC_TRNS,  KC_TRNS, 
      KC_TRNS, KC_LCTL,     KC_LALT,    KC_LGUI,        KC_LSFT,        KC_TRNS,  KC_TRNS,  KC_LEFT,        KC_DOWN,  KC_RGHT,        KC_BSPC,  KC_TRNS, 
      KC_TRNS, LGUI(KC_Z),  LGUI(KC_X), LGUI(KC_C),     LGUI(KC_V),     KC_TRNS,  KC_TRNS,  RALT(KC_LEFT),  KC_TRNS,  RALT(KC_RGHT),  KC_TRNS,  KC_TRNS, 
                                        KC_TRNS,        KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS
      ),
    [_MED] = LAYOUT_split_3x6_3(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
      KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, RGB_TOG, KC_NO, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, 
      KC_NO, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
    [_BRC] = LAYOUT_split_3x6_3(
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LPRN,  KC_RPRN, KC_AMPR, KC_NO,   KC_NO, 
      KC_NO,    KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  KC_NO,    KC_NO,    KC_LCBR,  KC_RCBR, KC_PIPE, KC_BSLS, KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LBRC,  KC_RBRC, KC_QUES, KC_SLSH, KC_NO, 
                                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
    [_SYM] = LAYOUT_split_3x6_3(
      KC_NO,    KC_GRV,  KC_NO,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_EXLM, KC_AT,   KC_UNDS, KC_EQL,  KC_CIRC, KC_NO,   KC_RSFT,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_NO, 
      KC_NO,    KC_TILD, KC_NO,   KC_MINS, KC_PLUS, KC_ASTR, KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
      )
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

void housekeeping_task_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand.
  switch (tap_hold_keycode) {
    case LT(_NUM,KC_CAPS): 
      return true;
    case LT(_SYM,KC_SPC):
      return true;
    case LGUI_T(KC_D):
      if (other_keycode == KC_TAB) { return true; }
      break;
    case RGUI_T(KC_K):
      if (other_keycode == LT(_SYM,KC_SPC)) { return true; }
      break;
  }
  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
    case MOD_LGUI:
      return true;

    default:
      return false;
  }
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
