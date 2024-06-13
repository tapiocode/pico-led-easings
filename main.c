/**
 * Copyright (c) 2024 tapiocode
 * https://github.com/tapiocode
 * MIT License
 */

#include "pico/stdlib.h"
#include "pico_led_easings.h"

/**
 * For convenience, the demo uses the regular Pico board with board led. You can use a normal LED,
 * just use an available pin and replace it here and ground the other leg.
 */
static const uint led_regular_board[] = { PICO_DEFAULT_LED_PIN };

/**
 * Optionally, add an RGB LED to pins below, or change them to other available pins.
 *
 * Use 3V3 or GND depending on LED type (common anode/cathode). With common anode (3V3),
 * you can correct the inverted fading direction with the init parameter.
 */
static const uint led_rgb[] = { 16, 17, 18 };

static void run_fade_fn(float (*fade_fn)(float x)) {
    uint32_t delay = 7;

    led_easings_fade(led_regular_board, 1, fade_fn, true, delay);
    led_easings_fade(led_regular_board, 1, fade_fn, false, delay);
    sleep_ms(500);

    led_easings_fade(led_rgb, 3, fade_fn, true, delay);
    led_easings_fade(led_rgb, 3, fade_fn, false, delay);
    sleep_ms(500);
}

int main() {
    stdio_init_all();

    // Step 1, initialize any pins used for output

    led_easings_init_pins(led_regular_board, 1, false);
    led_easings_init_pins(led_rgb, 3, false);

    while (true) {
        sleep_ms(1000);

        // Step 2, run through the easing functions

        run_fade_fn(led_easings_linear);
        run_fade_fn(led_easings_in_out_cubic);
        run_fade_fn(led_easings_ease_in_expo);
        run_fade_fn(led_easings_ease_out_expo);
    }
}
