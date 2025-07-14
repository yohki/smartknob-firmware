#pragma once
#include "apps/app.h"
#include "notify/motor_notifier/motor_notifier.h"
#include "notify/wifi_notifier/wifi_notifier.h"
#include "notify/os_config_notifier/os_config_notifier.h"

class MyApp
{
public:
    MyApp(SemaphoreHandle_t mutex);

    void render();

    EntityStateUpdate update(AppState state);
    EntityStateUpdate updateStateFromKnob(PB_SmartKnobState state);

    void handleEvent(WiFiEvent event);

    void setWiFiNotifier(WiFiNotifier *wifi_notifier);
    void setOSConfigNotifier(OSConfigNotifier *os_config_notifier);
    void setMotorNotifier(MotorNotifier *motor_notifier);
    void triggerMotorConfigUpdate();
    void handleNavigationEvent(NavigationEvent event);

    void setMotorConfig(int i);

private:
    SemaphoreHandle_t mutex_;

    uint8_t current_position = 0;
    char firmware_version[16];

    PB_SmartKnobConfig current_config;

    PB_SmartKnobConfig config_disc_1 = PB_SmartKnobConfig{
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
        1,
        45 * PI / 180,
        2,
        1,
        0.55,
        "ONBOARDING",
        0,
        {},
        0,
        20,
    };

    PB_SmartKnobConfig config_cont_270 = PB_SmartKnobConfig{
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
        270,
        2 * PI / 180,
        0,
        1,
        0.5,
        "ONBOARDING",
        0,
        {},
        0,
        90,
    };

    PB_SmartKnobConfig config_disc_2 = PB_SmartKnobConfig{
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
        2,
        60 * PI / 180,
        2,
        1,
        0.55,
        "ONBOARDING",
        0,
        {},
        0,
        20,
    };

    // Windchime cont.
    PB_SmartKnobConfig config_cont_360 = PB_SmartKnobConfig{
        0,
        0,
        0,
        0,
        360,
        2 * PI / 180,
        2.5,
        1,
        0.7,
        "ONBOARDING",
        1,
        {90},
        0,
        73,
    };

    WiFiNotifier *wifi_notifier;
    OSConfigNotifier *os_config_notifier;
    MotorNotifier *motor_notifier;
};