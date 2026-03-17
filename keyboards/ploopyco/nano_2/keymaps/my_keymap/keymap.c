/* Copyright 2025 Yun Ji 
 * Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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
#include "ploopyco.h"

enum custom_keycodes {
    BTN_SMART = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( BTN_SMART )
};

static uint16_t press_time = 0;
static uint16_t last_release_time = 0;
static uint8_t click_count = 0;

static bool btn_smart_down = false;
static uint8_t press_click_count = 0;
static bool hold_action_sent = false;
static bool scroll_mode_triggered = false;
static bool left_drag_momentary = false;

static int16_t scroll_accum_h = 0;
static int16_t scroll_accum_v = 0;

static inline uint8_t u8_abs8(int8_t v) {
    return (uint8_t)(v < 0 ? -v : v);
}

static inline void reset_click_state(void) {
    click_count = 0;
    press_click_count = 0;
}

static inline void reset_scroll_accum(void) {
    scroll_accum_h = 0;
    scroll_accum_v = 0;
}

#define RIGHTCLICK_HOLD_THRESHOLD 250
#define MIDDLECLICK_HOLD_THRESHOLD 250
#define SCROLL_ARM_THRESHOLD 120
#define DOUBLECLICK_THRESHOLD 250

#define DRAG_ARM_THRESHOLD 40

#define MOVE_THRESHOLD_DRAG 1
#define MOVE_THRESHOLD_SCROLL 3

#define MOUSE_BTN_L 0x01

#define SCROLL_DIVISOR_H 17
#define SCROLL_DIVISOR_V 17

static bool scroll_mode = false;
static bool pending_single_click = false;
static uint16_t pending_single_click_time = 0;

void matrix_scan_user(void) {
    if (pending_single_click && timer_elapsed(pending_single_click_time) >= DOUBLECLICK_THRESHOLD) {
        tap_code16(MS_BTN1);
        pending_single_click = false;
    }

    if (!btn_smart_down) {
        return;
    }

    if (is_drag_scroll || scroll_mode) {
        return;
    }

    uint16_t elapsed = timer_elapsed(press_time);

    if (press_click_count == 1) {
        if (!hold_action_sent && !scroll_mode_triggered && elapsed >= RIGHTCLICK_HOLD_THRESHOLD) {
            tap_code16(MS_BTN2);
            hold_action_sent = true;
            reset_click_state();
        }
    } else if (press_click_count == 2) {
        if (!hold_action_sent && !scroll_mode_triggered && elapsed >= MIDDLECLICK_HOLD_THRESHOLD) {
            tap_code16(MS_BTN1);
            tap_code16(MS_BTN1);
            hold_action_sent = true;
            reset_click_state();
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BTN_SMART:
            if (record->event.pressed) {
                pending_single_click = false;
                btn_smart_down = true;
                hold_action_sent = false;
                scroll_mode_triggered = false;
                left_drag_momentary = false;

                uint16_t now = timer_read();

                if (timer_elapsed(last_release_time) < DOUBLECLICK_THRESHOLD && click_count == 1) {
                    click_count = 2;
                } else {
                    click_count = 1;
                }

                press_click_count = click_count;
                press_time = now;
            } else {
                btn_smart_down = false;

                last_release_time = timer_read();

                if (is_drag_scroll) {
                    toggle_drag_scroll();
                    reset_click_state();
                    return false;
                }

                if (scroll_mode) {
                    scroll_mode = false;
                    reset_click_state();
                    reset_scroll_accum();
                    return false;
                }

                if (left_drag_momentary) {
                    left_drag_momentary = false;
                    reset_click_state();
                    return false;
                }

                if (hold_action_sent) {
                    press_click_count = 0;
                    return false;
                }

                if (press_click_count == 2) {
                    if (!scroll_mode_triggered) {
                        toggle_drag_scroll();
                    }
                    reset_click_state();
                } else {
                    pending_single_click = true;
                    pending_single_click_time = last_release_time;
                }
            }
            return false; // BTN_SMART itself is not passed elsewhere

        default:
            return true;
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (btn_smart_down && !is_drag_scroll && !scroll_mode && !scroll_mode_triggered) {
        bool moved_drag = (u8_abs8(mouse_report.x) >= MOVE_THRESHOLD_DRAG || u8_abs8(mouse_report.y) >= MOVE_THRESHOLD_DRAG);
        bool moved_scroll = (u8_abs8(mouse_report.x) >= MOVE_THRESHOLD_SCROLL || u8_abs8(mouse_report.y) >= MOVE_THRESHOLD_SCROLL);
        uint16_t held = timer_elapsed(press_time);

        if (press_click_count == 2) {
            if (held >= SCROLL_ARM_THRESHOLD && moved_scroll) {
                scroll_mode = true;
                scroll_mode_triggered = true;
                reset_click_state();
                reset_scroll_accum();
            }
        } else if (press_click_count == 1 && !hold_action_sent) {
            if (held >= DRAG_ARM_THRESHOLD && moved_drag) {
                left_drag_momentary = true;
                scroll_mode_triggered = true;
                mouse_report.x = 0;
                mouse_report.y = 0;
            }
        }
    }

    if (left_drag_momentary) {
        mouse_report.buttons |= MOUSE_BTN_L;
    } else {
        mouse_report.buttons &= (uint8_t)~MOUSE_BTN_L;
    }

    if (scroll_mode) {
        // Convert current mouse movement to scroll with inverted direction
        int8_t x = mouse_report.x;
        int8_t y = mouse_report.y;

        mouse_report.x = 0;
        mouse_report.y = 0;

        scroll_accum_h += x;
        scroll_accum_v += -y;

        mouse_report.h = (int8_t)(scroll_accum_h / SCROLL_DIVISOR_H);
        mouse_report.v = (int8_t)(scroll_accum_v / SCROLL_DIVISOR_V);

        scroll_accum_h -= (int16_t)mouse_report.h * SCROLL_DIVISOR_H;
        scroll_accum_v -= (int16_t)mouse_report.v * SCROLL_DIVISOR_V;
        // If horizontal scroll is needed:
        // mouse_report.h = -x;
    }
    return mouse_report;
}
