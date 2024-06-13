/**
 * Copyright (c) 2024 tapiocode
 * https://github.com/tapiocode
 * MIT License
 */

#include "pico_led_easings.h"
#include "hardware/pwm.h"

static void set_led_level(const uint *pins, const uint count, uint16_t level) {
    for (uint i = 0; i < count; i++) {
        pwm_set_gpio_level(pins[i], level);
    }
}

/**
 * @brief Initialize PWM pins for LEDs
 *
 * @param pins Array of LED pins
 * @param count Number of LED pins
 * @param invert true to invert PWM output, false otherwise
 */
void led_easings_init_pins(const uint *pins, const uint count, const uint invert) {
    for (uint i = 0; i < count; i++) {
        gpio_set_function(pins[i], GPIO_FUNC_PWM);
        pwm_set_enabled(pwm_gpio_to_slice_num(pins[i]), true);
        if (invert) {
            pwm_set_output_polarity(pwm_gpio_to_slice_num(pins[i]), true, true);
        }
    }
}

/**
 * @brief Fade initialized leds with given function
 *
 * @param pins Array of LED pins
 * @param count Number of LED pins
 * @param fade_fn Function to calculate fade value (see the header file)
 * @param direction true for on, false for off
 * @param delay_ms Delay between fade steps, likely to be small, eg. 5
 */
void led_easings_fade(const uint *pins, const uint count, float (*fade_fn)(float x), bool direction, uint32_t delay_ms) {
    float i, x;
    for (i = 0.0; i < 1.0; i += 0.01) {
        x = fade_fn(direction ? i : 1 - i);
        set_led_level(pins, count, x * LED_MAX_LEVEL);
        busy_wait_ms(delay_ms);
    }
    set_led_level(pins, count, direction ? LED_MAX_LEVEL : 0);
}
