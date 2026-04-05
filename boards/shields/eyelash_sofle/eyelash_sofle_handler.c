#include <zephyr/kernel.h>
#include <zmk/events/layer_state_changed.h>
#include <dt-bindings/zmk/rgb.h>
#include <zmk/rgb_underglow.h>
#include <zmk/endpoints.h>

int layer_led_listener(const zmk_event_t *eh) {
    const struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (ev == NULL) return 0;

    // CHECK: Is the RGB actually turned on?
    bool is_on;
    if (zmk_rgb_underglow_get_state(&is_on) != 0) return 0;
    if (!is_on) return 0; 

    switch (ev->layer) {
        case 0: // COLEMAK (Green)
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 160, .s = 100, .b = 50});
            break;
        case 1: // SYM_LEFT (Blue)
        case 2: // SYM_RIGHT (Blue)
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 200, .s = 100, .b = 50});
            break;
        case 3: // NAV_ARR (Orange)
        case 4: // NAV_MOUSE (Orange)
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 30,  .s = 100, .b = 50});
            break;
        case 5: // UTIL (Purple)
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 280, .s = 100, .b = 50});
            break;
        default:
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 0,   .s = 0,   .b = 50});
            break;
    }
    return 0;
}

ZMK_LISTENER(layer_led_listener, layer_led_listener);
ZMK_SUBSCRIPTION(layer_led_listener, zmk_layer_state_changed);