/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

// tap dance keycodes
enum td_keycodes {
    MSE_BTN4_LAYER_1,
    MSE_BTN5_LAYER_2
};

enum custom_keycodes {
    EXIT_DRAG_SCROLL = SAFE_RANGE,
    DPI_UP,
    DPI_DOWN
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

static td_state_t td_state; 

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `resolved` and `reset` functions for each tapdance keycode
void td_mse_btn4_resolved(tap_dance_state_t *state, void *user_data);
void td_mse_btn4_reset(tap_dance_state_t *state, void *user_data);

void td_mse_btn5_resolved(tap_dance_state_t *state, void *user_data);
void td_mse_btn5_reset(tap_dance_state_t *state, void *user_data);

// drag scroll functions
void toggle_drag_scroll(void);
void set_dpi(uint16_t dpi);

static bool is_drag_scroll_active = false;
// These are based on defaults defined in config.h
static uint8_t dpi_opts_size = 6;
static uint8_t dpi_index = 3;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base layer
    [0] = LAYOUT(
        KC_BTN1, KC_BTN3, KC_BTN2,
        TD(MSE_BTN4_LAYER_1), TD(MSE_BTN5_LAYER_2)
    ),
    // button 4 (back) held layer
    [1] = LAYOUT(
        KC_BTN3, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS
    ),
    // button 5 (fwd) held layer
    [2] = LAYOUT(
        DPI_DOWN, KC_TRNS, DPI_UP,
          KC_TRNS, KC_TRNS
    ),
    // drag scroll layer
    [3] = LAYOUT(
        EXIT_DRAG_SCROLL, EXIT_DRAG_SCROLL, EXIT_DRAG_SCROLL,
          EXIT_DRAG_SCROLL, EXIT_DRAG_SCROLL
    )
};

void keyboard_post_init_user() {
}

// Maybe if we used post init for setting the initial DPI that would work?
// Just use the pre-defined DPI keycodes for switching

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // returning false skips all further processing of the key
    // returning true lets QMK send the press/release events
    if (record->event.pressed) {
        switch (keycode) {
            case EXIT_DRAG_SCROLL:
                toggle_drag_scroll();
                layer_move(0);
                return false;
            case DPI_UP:
                uint16_t new_dpi_index = dpi_index < (dpi_opts_size - 1) ? ++dpi_index : dpi_index;
                set_dpi(new_dpi_index);
                return false;
            case DPI_DOWN:
                new_dpi_index = dpi_index > 0 ? --dpi_index : 0;
                set_dpi(new_dpi_index);
                return false;
            default:
                return true;
        }
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (is_drag_scroll_active) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else if (IS_LAYER_ON(1) && (mouse_report.x > 0 || mouse_report.y > 0)) {
        toggle_drag_scroll();
        layer_move(3);
    }

    return mouse_report;
}

void toggle_drag_scroll() {
    is_drag_scroll_active = !is_drag_scroll_active;
    set_dpi(is_drag_scroll_active ? 0 : dpi_index);
}

void set_dpi(uint16_t dpi_index) {
    keyboard_config.dpi_config = dpi_index;
    eeconfig_update_kb(keyboard_config.raw);
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        // Interrupted means some other button was pressed in the tapping term
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    }

    if (state->count == 2) {
        if (state->interrupted) {
            return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }

    } else {
        return TD_UNKNOWN; // Any number higher than the maximum state value you return above
    }
}

void td_mse_btn4_resolved(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_HOLD:
            layer_on(1);
        break;
        default:
        break;
    }
}

void td_mse_btn4_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_BTN4);
        break;
        case TD_SINGLE_HOLD:
            layer_off(1);
        break;
        default:
        break;
    }
}

void td_mse_btn5_resolved(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_HOLD:
            layer_on(2);
        break;
        default:
        break;
    }
}

void td_mse_btn5_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_BTN5);
        break;
        case TD_SINGLE_HOLD:
            layer_off(2);
        break;
        default:
        break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `resolved` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [MSE_BTN4_LAYER_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mse_btn4_resolved, td_mse_btn4_reset),
    [MSE_BTN5_LAYER_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mse_btn5_resolved, td_mse_btn5_reset)
};
