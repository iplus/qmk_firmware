# ploopy-nano2-qmk

This repository contains a custom QMK keymap for the Ploopy Nano 2 trackball.

It includes **only a single `keymap.c` file** (not the full QMK firmware tree).

Current version: `v0.2.1`

---

## Target

- **Keyboard**: `ploopyco/nano_2/rev2_003`
- **Keymap name**: e.g. `my_keymap`

---

## How to use

1. Clone or download the official QMK firmware repository.
2. Copy this repository’s `keymap.c` into the appropriate keymap directory, for example:

   ```
   qmk_firmware/keyboards/ploopyco/nano_2/rev2_003/keymaps/my_keymap/keymap.c
   ```

3. Configure QMK environment and build the firmware:

   ```
   qmk compile -kb ploopyco/nano_2/rev2_003 -km my_keymap
   ```

4. Flash the resulting firmware to your Ploopy Nano 2 following the usual QMK / Ploopy flashing instructions.

---

## AI assistance

This keymap was created with the assistance of AI-based coding tools (Windsurf, ChatGPT 5.2, Claude Opus 4.5).  
All generated code was reviewed and modified by the author before being committed.

Some parts of the layer behavior and helper logic were initially suggested by these AI tools and then adapted for this specific device.

---

## Upstream projects

This keymap is intended to be used with:

- **QMK Firmware** – https://qmk.fm  
- **Ploopy Nano 2 firmware tree** inside the official QMK repository (the `ploopyco/nano_2` target).

This repository only contains a single `keymap.c` file and does *not* include the full QMK source tree.

The initial behavior is loosely based on the default Nano 2 keymap provided by Ploopy / QMK, then customized for this workflow.

---

## License and warranty

This repository is distributed under the terms of the **GPL-2.0** license (see `LICENSE`).  

- **1-click tap**: Left click
- **1-click hold (no move, 250ms)**: Right click (tap)
- **2-click hold (no move, 250ms)**: Middle click (scroll click)
- **1-click hold + move**: Left drag (momentary)
- **2-click hold + move**: Scroll mode (momentary)

In scroll mode, trackball movement is converted into wheel scrolling (`h/v`) and cursor movement (`x/y`) is suppressed.

---

## Tuning

You can adjust the feel by changing these `#define` values near the top of `keymap.c`:

- `RIGHTCLICK_HOLD_THRESHOLD` (default: `250` ms)
- `MIDDLECLICK_HOLD_THRESHOLD` (default: `250` ms)
- `SCROLL_ARM_THRESHOLD` (default: `120` ms)
- `DOUBLECLICK_THRESHOLD` (default: `250` ms)
- `DRAG_ARM_THRESHOLD` (default: `40` ms)
- `MOVE_THRESHOLD_DRAG` (default: `1`)
- `MOVE_THRESHOLD_SCROLL` (default: `3`)
- `SCROLL_DIVISOR_H / SCROLL_DIVISOR_V` (default: `17`)

---

## Release notes

### v0.2.1

- Improved left-drag start reliability by suppressing the first pointer movement report when entering drag mode (ensures the OS sees button-down before movement).

---

## Release (UF2)

- **Tagging**: Create a git tag for each binary release (example: `v0.2.1`).
- **Asset**: Attach the generated `.uf2` file to the GitHub Release for that tag.
- **Filename example**: `ploopyco_nano_2_rev2_003_my_keymap.uf2`

---

## License

This project is distributed under the GPL-2.0 license. See `LICENSE`.

---
