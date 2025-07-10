#include "myapp.h"

MyApp::MyApp(SemaphoreHandle_t mutex) : App(mutex)
{
    root_level_motor_config = motor_config1;
    root_level_motor_config.position = current_position;
    LOGI("MyApp initialized!");
}

EntityStateUpdate MyApp::updateStateFromKnob(PB_SmartKnobState state)
{
    LOGI("Position: %d", state.current_position);
    return EntityStateUpdate();
}