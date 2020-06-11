#include QMK_KEYBOARD_H

enum layer_names {
    _AA,
    _AAAA,
    _BLS,
    _BRS,
    _SYM,
    _OTHER
};



typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

//Declare the functions to be used with your tap dance key(s)

//Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void ql_finished (qk_tap_dance_state_t *state, void *user_data);
void ql_reset (qk_tap_dance_state_t *state, void *user_data);


//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      layer_on(_BLS);
      break;
    case DOUBLE_TAP:
      //check to see if the layer is already set
      if (layer_state_is(_BRS)) {
        //if already set, then switch it off
        layer_off(_BRS);
      } else {
        //if not already set, then switch the layer on
        layer_on(_BRS);
      }
      break;
    }
  }


//Tap Dance Declarations
enum {
  TD_RST = 0,
  TD_EDGES = 2
};

//Tripple-Tap Reset Setup
void dance_rst_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

void ql_reset (qk_tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (ql_tap_state.state==SINGLE_HOLD) {
    layer_off(_BLS);
  }
  ql_tap_state.state = 0;
}

//All Additional Tap Dance Functions Would Go Here.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset),
 [TD_EDGES]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)

};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Alpha 1 Layer
     *
     *      ┌────┬────┬────┬────┬────┐
     *      │ P  │ W  │ R  │ A  │ F  │
     *      ┼────┼────┼────┼────┼────┤
     *      │ D  │ T  │ H  │ E  │ O  │
     * ┌────┼────┼────┼────┼────┼────┼────┐
     * │SHFT│ Y  │ S  │ N  │ I  │ U  │SPAC│
     * │    ├────┴─┬──┴────┴──┬─┴────┤    │
     * │CAPS│ BkSp │  SYMBOL  │ESC/EG│ALP2│
     * └────┴──────┴──────────┴──────┴────┘
     */

[_AA] = LAYOUT_LEFTHAND(
            KC_P,      KC_W,     KC_R,     KC_A,     KC_F,
            KC_D,      KC_T,     KC_H,     KC_E,     KC_O,
            KC_Y,      KC_S,     KC_N,     KC_I,     KC_U,
LSFT_T(KC_CAPS),           KC_BSPC,            TG(_SYM),           TD(TD_EDGES),           LT(_AAAA, KC_SPACE)
),

     /* Alpha 2 Layer
      *
      *      ┌────┬────┬────┬────┬────┐
      *      │ J  │ M  │ B  │ Y  │TAB │
      *      ┼────┼────┼────┼────┼────┤
      *      │ V  │ C  │ L  │ Z  │ Q  │
      * ┌────┼────┼────┼────┼────┼────┼────┐
      * │    │ X  │ G  │ K  │GUI │CTRL│    │
      * │    ├────┴─┬──┴────┴──┬─┴────┤    │
      * │    │Enter │          │      │    │
      * └────┴──────┴──────────┴──────┴────┘
      */

[_AAAA] = LAYOUT_LEFTHAND(
            KC_J,      KC_M,     KC_B,     KC_Y,     KC_TAB,
            KC_V,      KC_C,     KC_L,     KC_Z,     KC_Q,
            KC_X,      KC_G,     KC_K,     KC_LGUI,  KC_LCTL,
_______,           KC_ENTER,            _______,           _______,           _______
),

     /* FUNCTION Layer
      *
      *      ┌────┬────┬────┬────┬────┐
      *      │PgUp│Paus│End │Home│Del │
      *      ┼────┼────┼────┼────┼────┤
      *      │PgDn│ Up │Alt │Ctrl│Ins │
      * ┌────┼────┼────┼────┼────┼────┼────┐
      * │    │Left│Down│Rght│    │    │    │
      * │    ├────┴─┬──┴────┴──┬─┴────┤    │
      * │    │      │          │      │    │
      * └────┴──────┴──────────┴──────┴────┘
      */

[_BLS] = LAYOUT_LEFTHAND(
            KC_PGUP,      KC_PAUSE,     KC_END,     KC_HOME,     KC_DEL,
            KC_PGDN,      KC_UP,        KC_LALT,    KC_RCTL,     KC_INS,
            KC_LEFT,      KC_DOWN,      KC_RIGHT,   _______,     _______,
_______,           _______,            _______,           _______,           _______
),

     /* Default Layer
      *
      *      ┌────┬────┬────┬────┬────┐
      *      │ *  │ 7  │ 8  │ 9  │ ~  │
      *      ┼────┼────┼────┼────┼────┤
      *      │ /  │ 4  │ 5  │ 6  │ +  │
      * ┌────┼────┼────┼────┼────┼────┼────┐
      * │    │ 0  │ 1  │ 2  │ 3  │ .  │    │
      * │    ├────┴─┬──┴────┴──┬─┴────┤    │
      * │    │      │          │      │    │
      * └────┴──────┴──────────┴──────┴────┘
      */

[_BRS] = LAYOUT_LEFTHAND(
            KC_ASTR,      KC_7,     KC_8,     KC_9,     KC_GRAVE,
            KC_SLSH,      KC_4,     KC_5,     KC_6,     KC_PLUS,
            KC_0,         KC_1,     KC_2,     KC_3,     KC_DOT,
_______,           _______,            _______,           _______,           _______
),

     /* Default Layer
      *
      *      ┌────┬────┬────┬────┬────┐
      *      │ ;  │ :  │ *  │ &  │ ?  │
      *      ┼────┼────┼────┼────┼────┤
      *      │ _  │ @  │ -  │ !  │ /  │
      * ┌────┼────┼────┼────┼────┼────┼────┐
      * │    │ {  │ [  │ (  │ <  │ '  │    │
      * │    ├────┴─┬──┴────┴──┬─┴────┤    │
      * │    │      │          │      │    │
      * └────┴──────┴──────────┴──────┴────┘
      */

[_SYM] = LAYOUT_LEFTHAND(
            KC_SCLN,      KC_COLN,         KC_ASTR,         KC_AMPR,         KC_QUES,
            KC_UNDS,      KC_AT,           KC_MINUS,        KC_EXLM,         KC_SLSH,
            KC_LCBR,      KC_LBRC,         KC_LPRN,         KC_LABK,         KC_QUOTE,
_______,           _______,            _______,           _______,           LT(_OTHER, KC_SPACE)

),

     /* Default Layer
      *
      *      ┌────┬────┬────┬────┬────┐
      *      │ #  │ $  │ =  │ +  │ `  │
      *      ┼────┼────┼────┼────┼────┤
      *      │ ^  │ ~  │ |  │ %  │ \  │
      * ┌────┼────┼────┼────┼────┼────┼────┐
      * │    │ }  │ ]  │ )  │ >  │ "  │    │
      * │    ├────┴─┬──┴────┴──┬─┴────┤    │
      * │    │      │          │      │    │
      * └────┴──────┴──────────┴──────┴────┘
      */

[_OTHER] = LAYOUT_LEFTHAND(
            KC_HASH,      KC_DLR,     KC_EQUAL,     KC_PLUS,     KC_GRAVE,
            KC_CIRC,      KC_TILD,     KC_PIPE,     KC_PERC,     KC_BSLS,
            KC_RCBR,      KC_LBRC,     KC_RPRN,     KC_RABK,     KC_DQT,
_______,           _______,            _______,           _______,           _______

)

// Layer Template:
//
// /* </layer name>
//  *
//  *      ┌────┬────┬────┬────┬────┐
//  *      │ Q  │ W  │ E  │ R  │ T  │
//  *      ┼────┼────┼────┼────┼────┤
//  *      │ A  │ S  │ D  │ F  │ G  │
//  * ┌────┼────┼────┼────┼────┼────┼────┐
//  * │    │ Z  │ X  │ C  │ V  │ B  │    │
//  * │    ├────┴─┬──┴────┴──┬─┴────┤    │
//  * │    │ Del  │   Gui    │ Lwr  │    │
//  * └────┴──────┴──────────┴──────┴────┘
//  */
//
// [</layer name>] = LAYOUT_LEFTHAND(
//             _______,      _______,     _______,     _______,     _______,
//             _______,      _______,     _______,     _______,     _______,
//             _______,      _______,     _______,     _______,     _______,
// _______,           _______,            _______,           _______,           _______
// ),
//

};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}


static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _AA:
            oled_write_P(PSTR("1st Alpha\n"), false);
            break;
        case _AAAA:
            oled_write_P(PSTR("2nd Alpha\n"), false);
            break;
        case _BLS:
            oled_write_P(PSTR("FUNCTION\n"), false);
            break;
        case _BRS:
            oled_write_P(PSTR("NUM-NUM\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("SYMBOL\n"), false);
            break;
        case _OTHER:
            oled_write_P(PSTR("OTHER\n"), false);
            break;
        default:
            oled_write_P(PSTR("Err?\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUM ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPS ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCROLL ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
    }
}
#endif


void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(B1);
  writePinLow(B1);
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(B1);
  } else {
    writePinLow(B1);
  }
}

// ˇˇˇˇˇFunction for layer INDICATOR LEDsˇˇˇˇˇ //
uint32_t layer_state_set_user(uint32_t state){
    if (biton32(state) == 3) {
    writePinHigh(B2);
	} else {
		writePinLow(B2);
    }
    if (biton32(state) == 4) {
    writePinHigh(B3);
	} else {
		writePinLow(B3);
    }
    if (biton32(state) == 1) {
    writePinHigh(B7);
	} else {
		writePinLow(B7);
    }
    return state;
 }
