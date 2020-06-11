#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4b4b
#define PRODUCT_ID      0x5922
#define DEVICE_VER      0x0001
#define MANUFACTURER    The_Royal
#define PRODUCT         Toddle Pad
#define DESCRIPTION     "A one-handed keyboard inspired by the wildly expensive *frogpad* keyboard"
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { D5, D4, C6, C7 }
#define MATRIX_COL_PINS { B6, B5, B4, D7, D6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
