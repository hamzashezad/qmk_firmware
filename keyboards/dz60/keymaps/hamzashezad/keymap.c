#include QMK_KEYBOARD_H

enum {
	ESGR,
};

enum custom_keycodes {
    WPM_OUTPUT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[ESGR] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
};

enum layers_idx {
	_BL, // Base layer
	_FL, // Function layer
	_RL, // RGB layer
    _ML // Mouse layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT_olivierko(
        TD(ESGR), KC_1,    KC_2,    KC_3,  KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_ESC,   KC_A,    KC_S,    KC_D,  KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, MO(1),   KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_LALT,                 KC_SPC,                                            KC_NO  , KC_RALT, KC_RCTL, KC_NO
    ),

    [_FL] = LAYOUT_olivierko(
        KC_TILDE, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DEL,
        KC_TRNS,  KC_MPRV, KC_UP,   KC_MNXT,  KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), MO(2),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_VOLD, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS,  KC_BRID, KC_BRIU,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS,                    KC_MPLY,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_RL] = LAYOUT_olivierko(
        KC_TRNS, RGB_MODE_PLAIN, RGB_MODE_GRADIENT, RGB_MODE_SWIRL, RGB_MODE_KNIGHT, RGB_MODE_SNAKE, RGB_MODE_RAINBOW, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_RMOD, RGB_HUI, RGB_MOD, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,  RGB_HUD, KC_TRNS, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS,                    RGB_TOG,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ML] = LAYOUT_olivierko(
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, WPM_OUTPUT, KC_MS_UP,   KC_MS_BTN1,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,                    KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WPM_OUTPUT:
            if (record->event.pressed) {
                uint8_t wpm = get_current_wpm();

                char wpm_str[5];

                wpm_str[0] = '0' + wpm / 100;
                wpm_str[1] = '0' + wpm % 100 / 10;
                wpm_str[2] = '0' + wpm % 10;
                wpm_str[4] = 0;

                send_string(wpm_str);
            }
            break;
    }

    return true;
}
