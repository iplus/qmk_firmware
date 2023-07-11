#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "quantum.h"
#include "process_combo.h"
#include "env.h"

enum ferris_layers {
  _AL1,
  _AL2,
  _SML,
  _SMR,
  _NM1,
  _NM2,
  _FN1,
  _FN2,
  _SYS,
  _GAME,
  _NMG,
};

#define XX_M LT(0, DV_M)
#define XX_ENT LT(_SYS, KC_ENT)
#define XX_TAB LT(_SYS, KC_TAB)
#define XX_ESC LT(_SYS, KC_ESC)
#define SYS_U LT(_SYS, DV_U)
#define SYS_K LT(_SYS, DV_K)
#define SYS_H LT(_SYS, DV_H)
#define CPY_PST LT(_SYS, KC_NO)
#define SFT_SPC SFT_T(KC_SPACE)
#define CTL_COMM CTL_T(DV_COMM)
#define ALT_DOT ALT_T(DV_DOT)
#define GUI_P GUI_T(DV_P)
#define GUI_G GUI_T(DV_G)
#define ALT_C ALT_T(DV_C)
#define CTL_R CTL_T(DV_R)
#define SMR_E LT(_SMR, DV_E)
#define SML_T LT(_SML, DV_T)
#define NM1_A LT(_NM1, DV_A)
#define NM2_O LT(_NM2, DV_O)
#define FN2_N LT(_FN2, DV_N)
#define FN1_S LT(_FN1, DV_S)


enum custom_keycodes {
    REPEAT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  [_] = LAYOUT(
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______,  _______, _______
  ),
  */
  [_AL1] = LAYOUT(
    DV_QUOT, CTL_COMM, ALT_DOT, GUI_P  , DV_Y,        DV_F   , GUI_G  , ALT_C  , CTL_R  , DV_L,
    NM1_A  , NM2_O   , SMR_E  , SYS_U  , DV_I,        DV_D   , SYS_H  , SML_T  , FN2_N  , FN1_S,
    DV_SCLN, DV_Q    , DV_J   , DV_K   , DV_X,        DV_B   , XX_M   , DV_W   , DV_V   , DV_Z,
                                REPEAT, SFT_SPC,  OSL(_AL2), QK_LEAD
  ),
  [_AL2] = LAYOUT(
    KC_LBRC, DV_X   , DV_I   , DV_Y   , XXXXXXX,      XXXXXXX, DV_F   , DV_D   , DV_B   , KC_QUOT,
    DV_SCLN, DV_Q   , DV_J   , SYS_K  , XXXXXXX,      XXXXXXX, XX_M   , DV_W   , DV_V   , DV_Z,
    DV_DLR , DV_EXLM, DV_AMPR, DV_BSLS, XXXXXXX,      XXXXXXX, DV_SLSH, DV_HASH, DV_AT  , DV_PERC,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
  [_SYS] = LAYOUT(
    KC_CAPS, KC_HOME , KC_PGUP, KC_END  , XXXXXXX,      XXXXXXX, CPY_PST, KC_UP  , KC_BSPC , XX_ESC,
    XX_TAB , KC_VOLD , KC_PGDN, KC_VOLU , XXXXXXX,      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XX_ENT,
    XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
  [_GAME] = LAYOUT(
    KC_LCTL, KC_Q, KC_W, KC_E, KC_R,              XXXXXXX, KC_G,    KC_UP  , KC_T    , KC_ESC,
    KC_LSFT, KC_A, KC_S, KC_D, KC_F,              XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
                            LT(_NMG, KC_R), KC_SPACE,  KC_LSFT, KC_LGUI
  ),
  [_NMG] = LAYOUT(
    KC_LGUI, KC_X, KC_C, KC_F, XXXXXXX,      XXXXXXX, _______, _______, _______, TO(_AL1),
    KC_TAB , KC_1, KC_2, KC_3, XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______,  _______, _______
  ),
/*
[]{}    +X*.
<>()    -o/=
*/
  [_SML] = LAYOUT(
    DV_LBRC, DV_RBRC, DV_LCBR, DV_RCBR, XXXXXXX,      XXXXXXX, DV_PLUS, XXXXXXX, DV_ASTR, DV_DOT ,
    DV_LABK, DV_RABK, DV_LPRN, DV_RPRN, XXXXXXX,      XXXXXXX, DV_MINS, _______, DV_SLSH, DV_EQL ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
/*
;^X`    #@%/
:$o~    $!&\
*/
  [_SMR] = LAYOUT(
    DV_SCLN, DV_CIRC, XXXXXXX, DV_GRV , XXXXXXX,      XXXXXXX, DV_HASH, DV_AT  , DV_PERC, DV_SLSH,
    DV_COLN, DV_DLR , _______, DV_TILD, XXXXXXX,      XXXXXXX, DV_DLR , DV_EXLM, DV_AMPR, DV_BSLS,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
// XXXX   4560
// XXXX   1230
  [_NM1] = LAYOUT(
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, DV_4   , DV_5   , DV_6   , DV_0   ,
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, DV_1   , DV_2   , DV_3   , DV_0   ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
// XXXX   7890
// XXXX   4560
  [_NM2] = LAYOUT(
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, DV_7   , DV_8   , DV_9   , DV_0   ,
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, DV_4   , DV_5   , DV_6   , DV_0   ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, DV_1   , DV_2   , DV_3   , XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
// 0456   XXXX
// 0123   XXXX
  [_FN1] = LAYOUT(
    KC_F11 , KC_F4  , KC_F5  , KC_F6  , XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    KC_F10 , KC_F1  , KC_F2  , KC_F3  , XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  ),
// 0789   XXXX
// 0456   XXXX
  [_FN2] = LAYOUT(
    KC_F13 , KC_F7  , KC_F8  , KC_F9  , XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    KC_F12 , KC_F4  , KC_F5  , KC_F6  , XXXXXXX,      XXXXXXX, _______, _______, _______, _______,
    XXXXXXX, KC_F1  , KC_F2  , KC_F3  , XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_LGUI, KC_LSFT,  KC_LCTL, KC_LALT
  )
};

enum combos {
  CMB_PLAY,
  CMB_AL1
};
const uint16_t PROGMEM combo_play[] = {DV_G, DV_C, DV_R, COMBO_END};
const uint16_t PROGMEM combo_al1[] = {DV_H, DV_T, DV_N, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [CMB_PLAY] = COMBO(combo_play, KC_MPLY),
    [CMB_AL1]  = COMBO(combo_al1, TO(_AL1)),
};


const key_override_t delete_key_override = ko_make_basic(MOD_MASK_CTRL, KC_BSPC, KC_DEL);
const key_override_t play_key_override = ko_make_basic(MOD_MASK_CTRL, XX_ESC, KC_MPLY);
const key_override_t volu_key_override = ko_make_basic(MOD_MASK_CTRL, KC_PGUP, KC_VOLU);
const key_override_t vold_key_override = ko_make_basic(MOD_MASK_CTRL, KC_PGDN, KC_VOLD);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &play_key_override,
    &volu_key_override,
    &vold_key_override,
    NULL // Null terminate the array of overrides!
};


// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

// Initialize variables holding the bitfield
// representation of active modifiers.
uint8_t mod_state;
uint8_t oneshot_mod_state;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
        // Early return when holding down a pure layer key
        // to retain modifiers
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
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_keycode);
        } else {
            unregister_code16(last_keycode);
            unregister_mods(last_modifier);
        }
    }
}


static bool intab = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case XX_M: // "Ь" on press, "Ъ" on hold
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RBRC); // Intercept hold function to send Ъ
                return false;
            }
           break;
        case XX_ESC:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_PSCR);
                return false;
            }
           break;
        case XX_ENT:
            if (!record->tap.count && record->event.pressed) {
                // on hold CTRL+ENT
                tap_code16(keymap_config.swap_lalt_lgui ? C(KC_ENT) : G(KC_ENT));
                return false;
            }
           break;
        case SYS_U:
        case SYS_H:
            if (!record->event.pressed && intab) {
		       intab = false;
               last_keycode = KC_TAB;
               last_modifier = keymap_config.swap_lalt_lgui ? MOD_MASK_ALT : MOD_MASK_GUI;
               unregister_code(keycode_config(KC_LGUI));
               layer_clear();
               return false;
	          }
            break;
        case XX_TAB:
            if (record->tap.count && record->event.pressed) {
                // tap
                tap_code16(KC_TAB);
                last_keycode = KC_TAB;
                mod_state = get_mods();
                oneshot_mod_state = get_oneshot_mods();
            } else if (record->event.pressed) {
                // hold for ALT-TAB
                if (!intab) {
                  intab = true;
                  register_code(keycode_config(KC_LGUI));
			            tap_code16(KC_TAB);
                }
            }
            return false;
        case CPY_PST:
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function to send Ctrl-C
                tap_code16( keymap_config.swap_lalt_lgui ? C(DV_C) : G(DV_C));
            } else if (record->event.pressed) {
                // Intercept hold function to send Ctrl-V
                tap_code16( keymap_config.swap_lalt_lgui ? C(DV_V) : G(DV_V));
            }
            return false;
        case KC_LCTL:
            // swich off OSL on second press
            if(!record->event.pressed && is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            break;
        case SYS_K:
            if(record->event.pressed && is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            break;
    }

    process_repeat_key(keycode, record);
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    // automaticaly move to _AL1 when symbol from _AL2 is pressed.
    //if(!record->event.pressed && IS_LAYER_ON(_AL2) && IS_LAYER_OFF(_SYS) && keycode != OSL(_AL2) && keycode != XX_TAB) {
    //  layer_clear();
    //}

    return true;
}

void leader_end_user(void) {
    if (leader_sequence_one_key(DV_P)) {
      send_string_with_delay(PASSWORD, 50);
    } else if (leader_sequence_one_key(DV_L)) {
      layer_on(_GAME);
    } else if (leader_sequence_one_key(DV_S)) {
      tap_code(KC_MPLY);
    } else if (leader_sequence_one_key(DV_N)) {
      tap_code(KC_MNXT);
    } else if (leader_sequence_one_key(DV_H)) {
      tap_code(KC_MPRV);
    } else if (leader_sequence_one_key(DV_T)) {
      tap_code(KC_MUTE);
    } else if (leader_sequence_one_key(REPEAT)) {
      keymap_config.raw = eeconfig_read_keymap();
      keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !keymap_config.swap_lalt_lgui;
      eeconfig_update_keymap(keymap_config.raw);
    }
}
