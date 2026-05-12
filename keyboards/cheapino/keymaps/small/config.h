// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// LED off by default; cheapino.c skips startup RGB dance when this is set.
#undef RGBLIGHT_DEFAULT_VAL
#define RGBLIGHT_DEFAULT_VAL 0
#define CHEAPINO_SKIP_RGB_BOOT_FLASH

// Brightness for layer / caps indicators (0–255).
#ifndef CHEAPINO_RGB_STATUS_VAL
#define CHEAPINO_RGB_STATUS_VAL 30
#endif
