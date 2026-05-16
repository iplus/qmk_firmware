#include "matrix.h"
#include "quantum.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#define COL_SHIFTER ((uint16_t)1)

#define ENC_ROW 3
#define ENC_A_COL 2
#define ENC_B_COL 4
#define ENC_BUTTON_COL 0

static bool colABPressed              = false;
static bool encoderPressed            = false;
static bool encoderRotatedWhileHeld   = false;

void clicked(void) {
#ifdef CONSOLE_ENABLE
    uprintln("enc: action=click -> KC_MPLY");
#endif
    tap_code(KC_MPLY);
}

void turned(bool clockwise) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    uint16_t keycode;

    if (encoderPressed) {
        encoderRotatedWhileHeld = true;
    }

    if (encoderPressed) {
        keycode = clockwise ? KC_MPRV : KC_MNXT;
#ifdef CONSOLE_ENABLE
        uprintf("enc: turn %s btn=1 shift=%u -> track %s\n", clockwise ? "CW" : "CCW", !!(mods & MOD_MASK_SHIFT), clockwise ? "MPRV" : "MNXT");
#endif
    } else if (mods & MOD_MASK_SHIFT) {
        keycode = clockwise ? KC_MRWD : KC_MFFD;
#ifdef CONSOLE_ENABLE
        uprintf("enc: turn %s btn=0 shift=1 -> seek %s\n", clockwise ? "CW" : "CCW", clockwise ? "MRWD" : "MFFD");
#endif
    } else {
        keycode = clockwise ? KC_VOLD : KC_VOLU;
#ifdef CONSOLE_ENABLE
        uprintf("enc: turn %s btn=0 shift=0 -> vol %s\n", clockwise ? "CW" : "CCW", clockwise ? "VOLD" : "VOLU");
#endif
    }
    tap_code(keycode);
}

void fix_encoder_action(matrix_row_t current_matrix[]) {
    matrix_row_t encoder_row = current_matrix[ENC_ROW];

#ifdef CONSOLE_ENABLE
    static matrix_row_t last_encoder_row   = 0;
    static bool         last_btn_pressed = false;
    const bool          btn_pressed        = encoder_row & (COL_SHIFTER << ENC_BUTTON_COL);
    if (encoder_row != last_encoder_row || btn_pressed != last_btn_pressed) {
        uprintf("enc: row %04X btn_col%u=%u held=%u (bits: ", encoder_row, ENC_BUTTON_COL, btn_pressed, encoderPressed);
        for (uint8_t b = 0; b < 12; b++) {
            if (encoder_row & (COL_SHIFTER << b)) {
                uprintf("%u ", b);
            }
        }
        uprintln(")");
        last_encoder_row   = encoder_row;
        last_btn_pressed   = btn_pressed;
    }
#endif

    if (encoder_row & (COL_SHIFTER << ENC_BUTTON_COL)) {
        if (!encoderPressed) {
            encoderRotatedWhileHeld = false;
#ifdef CONSOLE_ENABLE
            uprintln("enc: btn down");
#endif
        }
        encoderPressed = true;
    } else {
        // Click only on release without rotation while held
        if (encoderPressed) {
            encoderPressed = false;
#ifdef CONSOLE_ENABLE
            if (encoderRotatedWhileHeld) {
                uprintln("enc: btn up, rotated=1 -> click suppressed");
            } else {
                uprintln("enc: btn up, rotated=0 -> click");
            }
#endif
            if (!encoderRotatedWhileHeld) {
                clicked();
            }
            encoderRotatedWhileHeld = false;
        }
    }

    // Check which way the encoder is turned:
    bool colA = encoder_row & (COL_SHIFTER << ENC_A_COL);
    bool colB = encoder_row & (COL_SHIFTER << ENC_B_COL);

    if (colA && colB) {
        colABPressed = true;
    } else if (colA) {
        if (colABPressed) {
            // A+B followed by A means clockwise
            colABPressed = false;
            turned(true);
        }
    } else if (colB) {
        if (colABPressed) {
            // A+B followed by B means counter-clockwise
            colABPressed = false;
            turned(false);
        }
    }
    current_matrix[ENC_ROW] = 0;
}
