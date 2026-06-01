// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/** Boot LED stages (CHEAPINO_BOOT_LED_DIAG in keymap config.h):
 *  0 red, 1 orange, 2 yellow, 3 green, 4 blue, 5 magenta, 6 cyan (USB ok).
 */
void cheapino_boot_led_stage(uint8_t stage);
void cheapino_boot_led_show(uint8_t stage);
void cheapino_boot_led_usb_ok(void);
