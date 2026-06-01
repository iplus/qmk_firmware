#include "wait.h"
#include "quantum.h"
#include "cheapino.h"

#ifdef RGBLIGHT_ENABLE
void cheapino_boot_led_stage(uint8_t stage) {
#    ifdef CHEAPINO_BOOT_LED_DIAG
    /* Wide hue steps so orange/yellow/magenta read clearly on one WS2812. */
    static const uint8_t hues[] = {0, 21, 43, 85, 170, 213, 128};
    static const uint8_t vals[] = {255, 255, 255, 255, 255, 255, 255};
    static const uint8_t sats[] = {255, 255, 255, 255, 255, 255, 255};
    if (stage < 7 && is_rgblight_initialized) {
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(1);
        rgblight_sethsv_noeeprom(hues[stage], sats[stage], vals[stage]);
    }
#    else
    (void)stage;
#    endif
}

void cheapino_boot_led_show(uint8_t stage) {
    cheapino_boot_led_stage(stage);
#    ifdef CHEAPINO_BOOT_LED_STAGE_MS
    wait_ms(CHEAPINO_BOOT_LED_STAGE_MS);
#    endif
}

void cheapino_boot_led_usb_ok(void) {
    cheapino_boot_led_stage(6);
#    ifdef CHEAPINO_BOOT_LED_USB_MS
    wait_ms(CHEAPINO_BOOT_LED_USB_MS);
#    endif
}
#else
void cheapino_boot_led_stage(uint8_t stage) {
    (void)stage;
}

void cheapino_boot_led_show(uint8_t stage) {
    (void)stage;
}

void cheapino_boot_led_usb_ok(void) {}
#endif

// This is to keep state between callbacks, when it is 0 the
// initial RGB flash is finished
uint8_t _hue_countdown = 50;

// These are to keep track of user selected color, so we
// can restore it after RGB flash
uint8_t _hue;
uint8_t _saturation;
uint8_t _value;

// Do a little 2.5 seconds display of the different colors
// Use the deferred executor so the LED flash dance does not
// stop us from using the keyboard.
// https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-executor-registration
uint32_t flash_led(uint32_t next_trigger_time, void *cb_arg) {
    if (!is_rgblight_initialized) {
        return 0;
    }
    rgblight_sethsv(_hue_countdown * 5, 230, 70);
    _hue_countdown--;
    if (_hue_countdown == 0) {
        // Finished, reset to user chosen led color
        rgblight_sethsv(_hue, _saturation, _value);
        return 0;
    } else {
        return 50;
    }
}

void keyboard_post_init_kb(void) {
#ifdef CHEAPINO_BOOT_LED_DIAG
    cheapino_boot_led_show(0);
#endif

    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;

    // Store user selected rgb hsv:
    _hue = rgblight_get_hue();
    _saturation = rgblight_get_sat();
    _value = rgblight_get_val();

    // Flash a little on start (keymaps can set CHEAPINO_SKIP_RGB_BOOT_FLASH to skip).
#ifndef CHEAPINO_SKIP_RGB_BOOT_FLASH
    defer_exec(50, flash_led, NULL);
#endif

    keyboard_post_init_user();

#ifdef CHEAPINO_BOOT_LED_DIAG
    cheapino_boot_led_show(4);
    cheapino_boot_led_show(5);
#endif
}

// Make the builtin RGB led show different colors per layer:
// This seemed like a good idea but turned out pretty annoying,
// to me at least... Uncomment the lines below to enable
/*
uint8_t get_hue(uint8_t layer) {
    switch (layer) {
        case 6:
            return 169;
        case 5:
            return 43;
        case 4:
            return 85;
        case 3:
            return 120;
        case 2:
            return 180;
        case 1:
            return 220;
        default:
            return 0;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t sat = rgblight_get_sat();
    uint8_t val = rgblight_get_val();
    uint8_t hue = get_hue(get_highest_layer(state));
    rgblight_sethsv(hue, sat, val);
    return state;
}
*/
