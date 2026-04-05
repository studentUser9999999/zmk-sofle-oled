#include <zephyr/kernel.h>
#include <dt-bindings/zmk/rgb.h>
#include <zmk/rgb_underglow.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/endpoints.h>

// This function tells the keyboard what to do when a layer changes
static int dt_layer_led_listener(const zmk_event_t *eh) {
    // Get the layer state change event
    const struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (ev == NULL) {
        return 0;
    }

    // Check if RGB is actually on
    bool is_on;
    if (zmk_rgb_underglow_get_state(&is_on) != 0 || !is_on) {
        return 0;
    }

    // Change color based on the NEWLY activated layer
    switch (ev->layer) {
        case 0: // COLEMAK
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 160, .s = 100, .b = 50});
            break;
        case 1: // SYM_LEFT
        case 2: // SYM_RIGHT
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 200, .s = 100, .b = 50});
            break;
        case 3: // NAV_ARR
        case 4: // NAV_MOUSE
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 30,  .s = 100, .b = 50});
            break;
        case 5: // UTIL
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 280, .s = 100, .b = 50});
            break;
        default:
            zmk_rgb_underglow_set_hsb((struct zmk_led_hsb){.h = 0,   .s = 0,   .b = 50});
            break;
    }

    return 0;
}

// Register the listener to the ZMK Event Manager
ZMK_LISTENER(layer_led_listener, dt_layer_led_listener);
ZMK_SUBSCRIPTION(layer_led_listener, zmk_layer_state_changed);