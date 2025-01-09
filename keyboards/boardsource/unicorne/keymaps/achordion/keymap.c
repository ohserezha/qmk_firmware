#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "features/achordion.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC, 
        KC_TAB,  KC_A, LCTL_T(KC_S), LALT_T(KC_D),   LGUI_T(KC_F),    KC_G,    KC_H,    RGUI_T(KC_J),    RALT_T(KC_K),    RCTL_T(KC_L),   RSFT_T(KC_SCLN), KC_QUOT, 
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ESC, 
                                   KC_LGUI, MO(1),   LSFT_T(KC_ENT),   KC_SPC,  LT(2, KC_BSPC),   KC_RALT
        ),
    [1] = LAYOUT_split_3x6_3(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, 
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
                                   _______, _______, _______, _______, _______, _______
        ),
    [2] = LAYOUT_split_3x6_3(
        QK_BOOT, _______, _______, _______, _______, _______, RM_VALU, RM_HUEU, RM_SATU, RM_NEXT, RM_TOGG, _______, 
        EE_CLR,  _______, _______, _______, _______, _______, RM_VALD, RM_HUED, RM_SATD, RM_PREV, CK_TOGG, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
                                   _______, _______, _______, _______, _______, _______
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C