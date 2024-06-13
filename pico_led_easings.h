
#include "pico/stdlib.h"
#include "math.h"

/**
 * Easing functions, see: https://easings.net
 */

static inline float led_easings_linear(float x) {
    return x - .01;
}
static inline float led_easings_in_out_cubic(float x) {
    return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}
static inline float led_easings_ease_in_expo(float x) {
    return x == 0 ? 0 : pow(2, 10 * x - 10);
}
static inline float led_easings_ease_out_expo(float x) {
    return x == 1 ? 1 : 1 - pow(2, -10 * x);
}

static const uint16_t LED_MAX_LEVEL = 256 * 256 - 1;

void led_easings_fade(const uint *pins, const uint count, float (*fade_fn)(float x), bool direction, uint32_t delay_ms);
void led_easings_init_pins(const uint *pins, const uint count, const uint invert);
