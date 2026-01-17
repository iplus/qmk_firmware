#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "quantum.h"
#include "process_combo.h"
#include "print.h"

// #include "env.h"

void keyboard_post_init_user(void) {
    // Ensure RGUI is always GUI (never swapped with RALT)
    keymap_config.raw = eeconfig_read_keymap();
    keymap_config.swap_ralt_rgui = false;
    keymap_config.swap_rctl_rgui = false;
    keymap_config.swap_lalt_lgui = true;
    keymap_config.swap_lctl_lgui = true;
    eeconfig_update_keymap(keymap_config.raw);

#ifdef CONSOLE_ENABLE
    // Customise these values to desired behaviour
    debug_enable   = true;
    //debug_matrix   = true;
    debug_keyboard = true;
    // debug_mouse=true;
#endif
}

enum ferris_layers {
  _AL1,
  _AL2,
  _SML,
  _SMR,
  _NM1,
  _NM2,
  _NUM,
  _FUN,
  _FN1,
  _FN2,
  _AL,
  _QWT,
  _SYSTAB,
  _SYS,
  _GAME,
  _NMG,
};

#define XX_M LT(0, DV_M)
#define XX_ENT LT(_SYS, KC_ENT)
#define XX_TAB LT(_SYS, KC_TAB)
#define XXX_TAB LT(_SYSTAB, KC_TAB)
#define XX_ESC LT(_SYS, KC_ESC)
#define SYS_U LT(_SYS, DV_U)
#define SYS_S LT(_SYS, DV_S)
#define SYSL_U LT(_SYSTAB, DV_U)
#define SYS_K LT(_SYS, DV_K)
#define SYS_H LT(_SYS, DV_H)
#define CPY_PST LT(_SYS, KC_NO)
#define SFT_SPC SFT_T(KC_SPACE)
#define CTL_COMM RCTL_T(DV_COMM)
#define CTL_BSPC LCTL_T(KC_BSPC)
#define ALT_DOT RALT_T(DV_DOT)
#define GUI_P RGUI_T(DV_P)
#define GUI_G RGUI_T(DV_G)
#define ALT_C RALT_T(DV_C)
#define CTL_R RCTL_T(DV_R)
#define SMR_E LT(_SMR, DV_E)
#define SML_T LT(_SML, DV_T)
#define NM1_A LT(_NM1, DV_A)
#define NM2_O LT(_NM2, DV_O)
#define NUM_A LT(_NUM, DV_A)
#define NUM_O LT(_NUM, DV_O)
#define FUN_O LT(_FUN, DV_O)
#define FUN_QUOT LT(_FUN, DV_QUOT)
#define FUN_A LT(_FUN, DV_A)
#define FN2_N LT(_FN2, DV_N)
#define FN1_S LT(_FN1, DV_S)
#define FUN_KC_A LT(_FUN, KC_A)
#define NUM_KC_O LT(_NUM, KC_O)
#define SMR_KC_E LT(_SMR, KC_E)
#define SYSL_KC_U LT(_SYSTAB, KC_U)
#define SML_KC_H LT(_SML, KC_H)
#define CTL_KC_COMM RCTL_T(KC_COMM)
#define ALT_KC_DOT RALT_T(KC_DOT)
#define GUI_KC_P RGUI_T(KC_P)

enum custom_keycodes {
    REPEAT = SAFE_RANGE,
    ALT_TAB
};

enum {
    TD_ESC_L,
    TD_ENT_S,
    TD_TAB_A
};


#define XX_L TD(TD_ESC_L)
#define XX_S TD(TD_ENT_S)
#define XX_TAB_A TD(TD_TAB_A)

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_L] = ACTION_TAP_DANCE_DOUBLE(DV_L, KC_ESC),
    [TD_ENT_S] = ACTION_TAP_DANCE_DOUBLE(DV_S, KC_ENT),
    [TD_TAB_A] = ACTION_TAP_DANCE_DOUBLE(DV_A, KC_TAB)
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
    DV_QUOT    , CTL_COMM, ALT_DOT, GUI_P  , DV_Y,        DV_F   , GUI_G  , ALT_C  , CTL_R  , DV_L,
    FUN_A      , NUM_O   , SMR_E  , SYSL_U , DV_I,        DV_D   , SYS_H  , SML_T  , DV_N   , DV_S,
    DV_SCLN    , DV_Q    , DV_J   , DV_K   , DV_X,        DV_B   , XX_M   , DV_W   , DV_V   , DV_Z,
                                CTL_BSPC, SFT_SPC,  OSL(_AL2), QK_LEAD
  ),
  [_AL2] = LAYOUT(
    KC_LBRC, DV_X   , DV_I   , DV_Y   , XXXXXXX,      XXXXXXX, DV_F   , DV_D   , DV_B   , KC_QUOT,
    DV_SCLN, DV_Q   , DV_J   , SYS_K  , XXXXXXX,      XXXXXXX, XX_M   , DV_W   , DV_V   , DV_Z,
    DV_DLR , DV_EXLM, DV_AMPR, DV_BSLS, XXXXXXX,      XXXXXXX, DV_SLSH, DV_HASH, DV_AT  , DV_PERC,
                                 KC_RCTL, KC_LSFT,  KC_RGUI, KC_RALT
  ),
  [_SYSTAB] = LAYOUT(
    KC_CAPS, KC_MS_BTN3 , CPY_PST   , XXXXXXX , XXXXXXX,      XXXXXXX, CPY_PST, KC_UP  , KC_BSPC , XX_ESC,
    XXX_TAB, KC_MS_BTN2 , KC_MS_BTN1, _______ , XXXXXXX,      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XX_ENT,
    XXXXXXX, DV_Q    , XXXXXXX, XXXXXXX , XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
                                KC_RCTL, KC_LSFT,   KC_RGUI, KC_RALT
  ),
  [_SYS] = LAYOUT(
    KC_CAPS, KC_VOLU , KC_PGUP, KC_VOLD , XXXXXXX,      XXXXXXX, CPY_PST, KC_UP  , KC_DEL , XX_ESC,
    KC_TAB , KC_HOME , KC_PGDN, KC_END ,  XXXXXXX,      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XX_ENT,
    XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
                                 KC_RCTL, KC_LSFT,  KC_RGUI, KC_RALT
  ),
  /*
[]{}    +X*.
<>()    -o/=
*/
  [_SML] = LAYOUT(
    DV_LBRC, DV_RBRC, DV_LCBR, DV_RCBR, XXXXXXX,      XXXXXXX, DV_PLUS, XXXXXXX, DV_ASTR, DV_DOT ,
    DV_LABK, DV_RABK, DV_LPRN, DV_RPRN, XXXXXXX,      XXXXXXX, DV_MINS, _______, DV_SLSH, DV_EQL ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_RCTL, KC_LSFT,  KC_RGUI, KC_RALT
  ),
/*
;^X`    #@%/
:$o~    $!&\
*/
  [_SMR] = LAYOUT(
    DV_SCLN, DV_CIRC, XXXXXXX, DV_GRV , XXXXXXX,      XXXXXXX, DV_HASH, DV_AT  , DV_PERC, DV_SLSH,
    DV_COLN, DV_DLR , _______, DV_TILD, XXXXXXX,      XXXXXXX, DV_DLR , DV_EXLM, DV_AMPR, DV_BSLS,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_RCTL, KC_LSFT,  KC_RGUI, KC_RALT
  ),
  //
  [_NUM] = LAYOUT(
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, DV_5   , DV_6   , DV_7   , DV_8   ,
    KC_LCTL, KC_PDOT, KC_LGUI, KC_LALT, XXXXXXX,       XXXXXXX, DV_1   , DV_2   , DV_3   , DV_4   ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 KC_RCTL, KC_LSFT,    DV_0, DV_9
  ),
  [_FUN] = LAYOUT(
    _______, _______, _______, _______, XXXXXXX,      XXXXXXX, KC_F5  , KC_F6  , KC_F7  , KC_F8  ,
    _______, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_F11, KC_F12, KC_F13, KC_F14,
                                 KC_RCTL, KC_LSFT,    KC_F10, KC_F9
  ),
  // qwerty
  //[_GAME] = LAYOUT(
  //  KC_LCTL, KC_Q, KC_W, KC_E, KC_T,              KC_I, KC_G,    KC_UP  , KC_B    , KC_ESC,
  //  KC_LSFT, KC_A, KC_S, KC_D, KC_G,              KC_H, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,
  //  KC_LGUI, KC_Z, KC_X, KC_C, KC_B,              KC_N, KC_Y,    KC_M,    KC_J ,    KC_O,
  //                LT(_NMG, KC_R), KC_SPACE,  KC_LSFT, KC_LGUI
  //),
  // dvorak
  [_GAME] = LAYOUT(
    KC_RCTL, DV_Q, DV_W, DV_E, DV_T,              KC_I, KC_VOLD, KC_UP  , KC_VOLU , KC_ESC,
    KC_RSFT, DV_A, DV_S, DV_D, DV_G,              KC_H, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,
    KC_RALT, DV_Z, DV_X, DV_C, DV_B,              KC_N, KC_MPLY, KC_MNXT, C(DV_T) ,   KC_M,
                  LT(_NMG, DV_R), KC_SPACE,  ALT_TAB, TO(_AL1)
  ),
  [_NMG] = LAYOUT(
    DV_Z, KC_1 , KC_2,  KC_3,    KC_ESC,      XXXXXXX, _______, KC_VOLU, _______, TO(_AL1),
    KC_TAB , DV_C , DV_X,  DV_F,    DV_I,      XXXXXXX, KC_MPLY, KC_VOLD, KC_MNXT, _______,
    KC_M,    KC_F5, KC_F6, DV_Y,    DV_V  ,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, _______,  _______, _______
  ),
  [_QWT] = LAYOUT(
    KC_SCLN   , CTL_KC_COMM, ALT_KC_DOT, GUI_KC_P  , KC_Y,        KC_G   , KC_G  , KC_C  , KC_R  , KC_L,
    FUN_KC_A  , NUM_KC_O, SMR_KC_E, SYSL_KC_U  , KC_I,        KC_D   , SML_KC_H  , KC_T  , KC_N  , KC_S,
    KC_SCLN   , KC_Q   , KC_J  , KC_K  , KC_X,        KC_B   , KC_M   , KC_W , KC_V , KC_Z,
                                CTL_BSPC, SFT_SPC,    ALT_TAB, TO(_AL1)
  ),
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

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

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
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                if (record->event.pressed) {
                    tap_dance_action_t *action;
                    action = &tap_dance_actions[TD_INDEX(keycode)];
                    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                    last_keycode = tap_hold->tap;
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
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case XX_M: // "Ь" on press, "Ъ" on hold
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RBRC); // Intercept hold function to send Ъ
                return false;
            }
           break;
        case XX_ESC:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(keymap_config.swap_lctl_lgui ?  C(S(KC_1)) : KC_PSCR);
                return false;
            }
           break;
        case XX_ENT:
            if (!record->tap.count && record->event.pressed) {
                // on hold CTRL+ENT
                tap_code16(keymap_config.swap_lctl_lgui ? G(KC_ENT) : C(KC_ENT));
                return false;
            }
           break;
        case SYS_U:
        case SYS_H:
        case SYSL_U:
            if (!record->event.pressed && intab) {
		           intab = false;
               last_keycode = KC_TAB;
               last_modifier = keymap_config.swap_lalt_lgui ? MOD_MASK_ALT : MOD_MASK_GUI;
               unregister_code(keycode_config(KC_LALT));
               layer_clear();
               return false;
	          }
            break;
        case XXX_TAB:
            if(record->event.pressed && (!((MOD_BIT(KC_RCTL)) & get_mods())) ) {
              if(!intab) {
                  intab = true;
                  register_code(keycode_config(KC_LALT));
			            tap_code16(KC_TAB);
                  return false;
              }
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
                tap_code16( keymap_config.swap_lalt_lgui ? G(DV_C) : C(DV_C));
            } else if (record->event.pressed) {
                // Intercept hold function to send Ctrl-V
                tap_code16( keymap_config.swap_lalt_lgui ? G(DV_V) : C(DV_V));
            }
            return false;
        case KC_LCTL:
            // swich off OSL on second press
            if(!record->event.pressed && is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            break;
            /*
        case SYS_K:
            if(record->event.pressed && is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            break;
            */
         case ALT_TAB:
            if (record->event.pressed) {
              // when keycode QMKBEST is pressed
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
      //send_string_with_delay(PASSWORD, 50);
    } else if (leader_sequence_one_key(DV_L)) {
      tap_code16(C(A(KC_DEL)));
    } else if (leader_sequence_one_key(TD(TD_ESC_L))) {
      tap_code16(C(A(KC_DEL)));
    } else if (leader_sequence_one_key(DV_S)) {
      tap_code(KC_MPLY);
    } else if (leader_sequence_one_key(DV_N)) {
      tap_code(KC_MNXT);
    } else if (leader_sequence_one_key(DV_H)) {
      tap_code(KC_MPLY);
    } else if (leader_sequence_one_key(DV_T)) {
      tap_code(KC_MUTE);
    } else if (leader_sequence_one_key(REPEAT) || leader_sequence_one_key(CTL_BSPC) || leader_sequence_one_key(KC_BSPC)) {
      keymap_config.raw = eeconfig_read_keymap();
      keymap_config.swap_ralt_rgui = false;
      keymap_config.swap_rctl_rgui = false;
      keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
      keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
      eeconfig_update_keymap(keymap_config.raw);
    } else if (leader_sequence_one_key(OSL(_AL2))) {
      layer_on(_GAME);
    } else if (leader_sequence_one_key(DV_Q) || leader_sequence_one_key(KC_SPACE)) {
      layer_on(_QWT);
    }
}
