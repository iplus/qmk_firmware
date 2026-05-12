// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keymap_dvorak.h"

enum cheapino_small_layers {
    _AL1,
    _AL2,
    _SML,
    _SMR,
    _NUM,
    _FUN,
    _SYSTAB,
    _SYS,
    _GAME,
    _NMG,
    _QWT,
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
#define SYS_N LT(_SYS, DV_N)
#define CPY_PST LT(_SYS, KC_NO)
#define SFT_SPC LSFT_T(KC_SPC)
#define SFT_QUOT LSFT_T(DV_QUOT)
#define CTL_COMM RCTL_T(DV_COMM)
#define CTL_BSPC LCTL_T(MS_BTN1)
#define ALT_DOT RALT_T(DV_DOT)
#define GUI_P RGUI_T(DV_P)
#define GUI_G RGUI_T(DV_G)
#define ALT_C RALT_T(DV_C)
#define CTL_R RCTL_T(DV_R)
#define SMR_E LT(_SMR, DV_E)
#define SML_T LT(_SML, DV_T)
#define NUM_A LT(_NUM, DV_A)
#define NUM_O LT(_NUM, DV_O)
#define FUN_O LT(_FUN, DV_O)
#define FUN_QUOT LT(_FUN, DV_QUOT)
#define FUN_A LT(_FUN, DV_A)
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
    ALT_TAB,
};

enum {
    TD_ESC_L,
    TD_ENT_S,
    TD_TAB_A,
    TD_SFT_SPC,
};

#define XX_L TD(TD_ESC_L)
#define XX_S TD(TD_ENT_S)
#define XX_TAB_A TD(TD_TAB_A)
