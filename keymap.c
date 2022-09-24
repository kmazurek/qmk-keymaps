#include QMK_KEYBOARD_H

enum layers {
    DEF,
    SYM,
    NAV,
    UTIL,
};

#include "g/keymap_combo.h"

#define SYM_OS OSL(SYM)
#define RALT_OS OSM(MOD_RALT)
#define NAV_OS OSL(NAV)
#define SFT_OS OSM(MOD_LSFT)
#define UTIL_OS OSL(UTIL)

#define ALT_F LALT_T(KC_F)
#define ALT_6 LALT_T(KC_6)
#define CTRL_A LCTL_T(KC_A)
#define CTRL_0 LCTL_T(KC_0)
#define GUI_D LGUI_T(KC_D)
#define GUI_5 LGUI_T(KC_5)
#define SFT_S LSFT_T(KC_S)
#define SFT_4 LSFT_T(KC_4)

#define ALT_J LALT_T(KC_J)
#define ALT_MIN LALT_T(KC_MINS)
#define CTRL_SCN LCTL_T(KC_SCLN)
#define CTRL_RBRC LCTL_T(KC_RBRC)
#define GUI_K LGUI_T(KC_K)
#define GUI_EQL LGUI_T(KC_EQL)
#define SFT_L LSFT_T(KC_L)
#define SFT_LBRC LSFT_T(KC_LBRC)

enum custom_keycodes {
        VTERM_ON = SAFE_RANGE,
        VTERM_OFF,
        LYR_CLEAR
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VTERM_OFF:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                tap_code_delay(KC_F1, 50);
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
            }
            break;
        case TERM_OFF:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                tap_code_delay(KC_F7, 50);
                unregister_code(KC_LCTL);
                unregister_code(KC_LALT);
            }
            break;
        case LYR_CLEAR:
            if (record->event.pressed) {
                layer_clear();
            }
    }
    return true;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case escTab:
            return 300;
    }
    return COMBO_TERM;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
        KC_ESC,   KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,  KC_Y,  KC_U,   KC_I,     KC_O,    KC_P,      KC_TAB,
        KC_BSPC,  CTRL_A,  SFT_S,  GUI_D,  ALT_F,  KC_G,  KC_H,  ALT_J,  GUI_K,    SFT_L,   CTRL_SCN,  KC_QUOT,
        SFT_OS,   KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,  KC_N,  KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,   SFT_OS,
                                RALT_OS,  SYM_OS,  KC_SPC,  KC_ENT,  NAV_OS,  RALT_OS
    ),

    [SYM] = LAYOUT(
        KC_ESC,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,   KC_RPRN,    KC_GRV,
        KC_BSPC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  ALT_MIN,  GUI_EQL,  SFT_LBRC,  CTRL_RBRC,  KC_BSLS,
        SFT_OS,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UNDS,  KC_PLUS,  KC_LCBR,   KC_RCBR,    SFT_OS,
                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    [NAV] = LAYOUT(
        KC_ESC,   XXXXXXX,  KC_7,   KC_8,   KC_9,   XXXXXXX,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,    XXXXXXX,  KC_GRV,
        KC_BSPC,  CTRL_0,   SFT_4,  GUI_5,  ALT_6,  KC_G,     KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  XXXXXXX,  KC_BSLS,
        SFT_OS,   XXXXXXX,  KC_1,   KC_2,   KC_3,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_COMM,  KC_DOT,    KC_SLSH,  SFT_OS,
                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    [UTIL] = LAYOUT(
        KC_F1,      KC_F2,    KC_F3,  KC_F4,  KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
        LYR_CLEAR,   KC_LCTL,     KC_LSFT,   KC_LGUI,   KC_LALT,   XXXXXXX,  XXXXXXX,  KC_LALT,  KC_LGUI,  KC_LSFT,  KC_LCTL,  VTERM_OFF,
        XXXXXXX,    XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TERM_OFF,
                                _______,  _______,  _______,  _______,  _______,  _______
    ),
};
