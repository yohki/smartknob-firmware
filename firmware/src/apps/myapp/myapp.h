#pragma once
#include "apps/app.h"

class MyApp : public App
{
public:
    MyApp(SemaphoreHandle_t mutex);
    EntityStateUpdate updateStateFromKnob(PB_SmartKnobState state);

private:
    int16_t current_position = 0;

    PB_SmartKnobConfig motor_config1 = PB_SmartKnobConfig{
        // .position = 0,
        // .sub_position_unit = 0,
        // .position_nonce = 0,
        // .min_position = 0,
        // .max_position = 100,
        // .position_width_radians = 2.4 * PI / 180,
        // .detent_strength_unit = 1,
        // .endstop_strength_unit = 1,
        // .snap_point = 1.1,
        // .detent_positions_count = 0,
        // .detent_positions = {},
        // .snap_point_bias = 0,
        // .led_hue = 27,
        0,
        0,
        0,
        0,
        10,
        15 * PI / 180,
        2,
        1,
        0.55,
        "MYAPP",
        0,
        {},
        0,
        20,
    };
};