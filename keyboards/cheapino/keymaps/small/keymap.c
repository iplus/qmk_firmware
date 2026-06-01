// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "print.h"

#if __has_include("env.h")
#include "env.h"
#endif

#ifndef PASSWORD
#define PASSWORD ""
#endif

/** Caps / _GAME / _QWT / Windows-mode status LED (single WS2812); default is off.
 *  Pass explicit \p layers from layer_state_set_user: global layer_state is
 *  updated only after that hook returns, so reading layer_state there is stale.
 */
static void cheapino_rgb_status_sync_from(layer_state_t layers) {
#ifdef RGBLIGHT_ENABLE
    if (host_keyboard_led_state().caps_lock) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(0, 0, CHEAPINO_RGB_STATUS_VAL); // white
        return;
    }
    if (layer_state_cmp(layers, _QWT)) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(170, 255, CHEAPINO_RGB_STATUS_VAL); // blue
        return;
    }
    if (layer_state_cmp(layers, _GAME) || layer_state_cmp(layers, _NMG)) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(0, 255, CHEAPINO_RGB_STATUS_VAL); // red
        return;
    }
    if (!keymap_config.swap_lctl_lgui) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(85, 255, CHEAPINO_RGB_WIN_VAL); // faint green (Windows)
        return;
    }
    rgblight_sethsv_noeeprom(0, 0, 0);
#endif
}

static void cheapino_rgb_status_sync(void) {
    cheapino_rgb_status_sync_from(layer_state);
}

void keyboard_post_init_user(void) {
    // Ensure RGUI is always GUI (never swapped with RALT).
    eeconfig_read_keymap(&keymap_config);
    keymap_config.swap_ralt_rgui = false;
    keymap_config.swap_rctl_rgui = false;
    keymap_config.swap_lalt_lgui = true;
    keymap_config.swap_lctl_lgui = true;
    eeconfig_update_keymap(&keymap_config);

#ifdef CONSOLE_ENABLE
    debug_enable   = true;
    debug_keyboard = true;
#endif

    cheapino_rgb_status_sync();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    cheapino_rgb_status_sync_from(state);
    return state;
}

bool led_update_user(led_t led_state) {
    cheapino_rgb_status_sync();
    return true;
}

// Helper: send Alt+Tab (or Cmd+Tab when swap_lalt_lgui).
static void tap_alt_tab(void) {
    eeconfig_read_keymap(&keymap_config);
    if (!keymap_config.swap_lalt_lgui) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB) SS_UP(X_LALT));
    } else {
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
    }
}

enum {
    SFT_SPC_SINGLE_TAP,
    SFT_SPC_SINGLE_HOLD,
    SFT_SPC_DOUBLE_TAP,
};

static int sft_spc_tap_state;

static void sft_spc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            sft_spc_tap_state = SFT_SPC_SINGLE_HOLD;
            register_mods(MOD_BIT(KC_LSFT));
        } else {
            sft_spc_tap_state = SFT_SPC_SINGLE_TAP;
            tap_code(KC_SPACE);
        }
    } else {
        sft_spc_tap_state = SFT_SPC_DOUBLE_TAP;
        tap_alt_tab();
    }
}

static void sft_spc_reset(tap_dance_state_t *state, void *user_data) {
    if (sft_spc_tap_state == SFT_SPC_SINGLE_HOLD) {
        unregister_mods(MOD_BIT(KC_LSFT));
    }
    sft_spc_tap_state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_L]   = ACTION_TAP_DANCE_DOUBLE(DV_L, KC_ESC),
    [TD_ENT_S]   = ACTION_TAP_DANCE_DOUBLE(DV_S, KC_ENT),
    [TD_TAB_A]   = ACTION_TAP_DANCE_DOUBLE(DV_A, KC_TAB),
    [TD_SFT_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_spc_finished, sft_spc_reset),
};

// Used to extract the basic tapping keycode from a dual-role key.
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

uint16_t last_keycode  = KC_NO;
uint8_t  last_modifier = 0;
uint8_t  mod_state;
uint8_t  oneshot_mod_state;

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                return;
        }

        last_modifier = oneshot_mod_state > mod_state ? oneshot_mod_state : mod_state;
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed) {
                    last_keycode = GET_TAP_KC(keycode);
                }
                break;
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                if (record->event.pressed) {
                    tap_dance_action_t *action   = &tap_dance_actions[TD_INDEX(keycode)];
                    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                    last_keycode                 = tap_hold->tap;
                }
                break;
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else if (record->event.pressed) {
        register_mods(last_modifier);
        register_code16(last_keycode);
    } else {
        unregister_code16(last_keycode);
        unregister_mods(last_modifier);
    }
}

static bool intab = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
        case XX_M:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RBRC);
                return false;
            }
            break;
        case XX_ESC:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(keymap_config.swap_lctl_lgui ? C(S(KC_1)) : KC_PSCR);
                return false;
            }
            break;
        case XX_ENT:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(keymap_config.swap_lctl_lgui ? G(KC_ENT) : C(KC_ENT));
                return false;
            }
            break;
        case SYS_U:
        case SYS_H:
        case SYSL_U:
            if (!record->event.pressed && intab) {
                intab         = false;
                last_keycode  = KC_TAB;
                last_modifier = keymap_config.swap_lalt_lgui ? MOD_MASK_ALT : MOD_MASK_GUI;
                unregister_code(keycode_config(KC_LALT));
                layer_clear();
                return false;
            }
            break;
        case XXX_TAB:
            if (record->event.pressed && !(MOD_BIT(KC_RCTL) & get_mods()) && !(MOD_BIT(KC_LSFT) & get_mods())) {
                if (!intab) {
                    intab = true;
                    register_code(keycode_config(KC_LALT));
                    tap_code16(KC_TAB);
                    return false;
                }
            }
            break;
        case XX_TAB:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_TAB);
                last_keycode       = KC_TAB;
                mod_state          = get_mods();
                oneshot_mod_state  = get_oneshot_mods();
            } else if (record->event.pressed) {
                if (!intab) {
                    intab = true;
                    register_code(keycode_config(KC_LGUI));
                    tap_code16(KC_TAB);
                }
            }
            return false;
        case CPY_PST:
            if (record->tap.count && record->event.pressed) {
                tap_code16(keymap_config.swap_lalt_lgui ? G(DV_C) : C(DV_C));
            } else if (record->event.pressed) {
                tap_code16(keymap_config.swap_lalt_lgui ? G(DV_V) : C(DV_V));
            }
            return false;
        case KC_LCTL:
            if (!record->event.pressed && is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            break;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!keymap_config.swap_lalt_lgui) {
                    SEND_STRING(SS_DOWN(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LGUI));
                }
                SEND_STRING(SS_TAP(X_TAB));
            } else {
                if (!keymap_config.swap_lalt_lgui) {
                    SEND_STRING(SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_UP(X_LGUI));
                }
            }
            break;
    }

    process_repeat_key(keycode, record);
    mod_state         = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    return true;
}

void leader_end_user(void) {
    if (leader_sequence_one_key(DV_P)) {
        send_string_with_delay(PASSWORD, 50);
    } else if (leader_sequence_one_key(DV_L)) {
        tap_code16(C(A(KC_DEL)));
    } else if (leader_sequence_one_key(TD(TD_ESC_L))) {
        tap_code16(C(A(KC_DEL)));
    } else if (leader_sequence_one_key(DV_S)) {
        tap_code(KC_MPLY);
    } else if (leader_sequence_one_key(DV_N)) {
        tap_code(KC_MNXT);
    } else if (leader_sequence_one_key(DV_H)) {
        tap_code(MS_BTN4);
    } else if (leader_sequence_one_key(DV_T)) {
        tap_code(KC_MUTE);
    } else if (leader_sequence_one_key(REPEAT) || leader_sequence_one_key(MS_BTN1) || leader_sequence_one_key(CTL_BSPC) || leader_sequence_one_key(KC_BSPC)) {
        eeconfig_read_keymap(&keymap_config);
        keymap_config.swap_ralt_rgui = false;
        keymap_config.swap_rctl_rgui = false;
        keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
        keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
        eeconfig_update_keymap(&keymap_config);
        cheapino_rgb_status_sync();
    } else if (leader_sequence_one_key(OSL(_AL2))) {
        layer_on(_GAME);
    } else if (leader_sequence_one_key(DV_Q) || leader_sequence_one_key(KC_SPACE)) {
        layer_on(_QWT);
    } else if (leader_sequence_one_key(QK_LEAD)) {
        tap_code(KC_ESC);
    }
}
