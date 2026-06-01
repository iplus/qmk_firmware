// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// LED off by default; cheapino.c skips startup RGB dance when this is set.
#undef RGBLIGHT_DEFAULT_VAL
#define RGBLIGHT_DEFAULT_VAL 0
#define CHEAPINO_SKIP_RGB_BOOT_FLASH

// Boot color stages on startup (see cheapino.h).
#define CHEAPINO_BOOT_LED_DIAG
// Pause on each boot-diagnostic color (ms).
#define CHEAPINO_BOOT_LED_STAGE_MS 400
// Brief cyan flash when USB is up, then LED goes to normal status (off/layer).
#define CHEAPINO_BOOT_LED_USB_MS 120

// Brightness for layer / caps indicators (0–255).
#ifndef CHEAPINO_RGB_STATUS_VAL
#define CHEAPINO_RGB_STATUS_VAL 30
#endif

// Faint green when swap_lctl_lgui is off (Windows mapping).
#ifndef CHEAPINO_RGB_WIN_VAL
#define CHEAPINO_RGB_WIN_VAL 4
#endif
