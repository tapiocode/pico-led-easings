cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico_led_easings VERSION 1.0 LANGUAGES C CXX ASM)

add_executable(pico_led_easings
        pico_led_easings.c
        main.c
        )

target_link_libraries(pico_led_easings
        pico_stdlib
        hardware_pwm
        )

# # Initialize the SDK
pico_sdk_init()

# # create map/bin/hex file etc.
pico_add_extra_outputs(pico_led_easings)
