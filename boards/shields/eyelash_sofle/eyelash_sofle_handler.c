#include <zephyr/kernel.h>
#include <zmk/events/layer_state_changed.h>
#include <dt-bindings/zmk/rgb.h>
#include <zmk/rgb_underglow.h>
#include <zmk/endpoints.h>

/* Define Colors (Hue 0-360, Saturation 0-100, Brightness 0-100) */
/* You can find Hue values at: https://hslpicker.com/ */

int layer_led_listener(const zmk_event_t *eh) {
    const struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (ev == NULL) return 0;

    switch (ev->layer) {
        case 0: // COLEMAK (Green)
            zmk_rgb_underglow_set_hsv((struct zmk_led_hsv){.h = 160, .s = 100, .v = 50});
            break;
        case 1: // SYM_LEFT (Blue)
        case 2: // SYM_RIGHT (Cyan)
            zmk_rgb_underglow_set_hsv((struct zmk_led_hsv){.h = 200, .s = 100, .v = 50});
            break;
        case 3: // NAV_ARR (Orange)
        case 4: // NAV_MOUSE (Yellow)
            zmk_rgb_underglow_set_hsv((struct zmk_led_hsv){.h = 30, .s = 100, .v = 50});
            break;
        case 5: // UTIL (Purple)
            zmk_rgb_underglow_set_hsv((struct zmk_led_hsv){.h = 280, .s = 100, .v = 50});
            break;
        default: // DEFAULT / EMPTY (White)
            zmk_rgb_underglow_set_hsv((struct zmk_led_hsv){.h = 0, .s = 0, .v = 50});
            break;
    }
    return 0;
}

ZMK_LISTENER(layer_led_listener, layer_led_listener);
ZMK_SUBSCRIPTION(layer_led_listener, zmk_layer_state_changed);