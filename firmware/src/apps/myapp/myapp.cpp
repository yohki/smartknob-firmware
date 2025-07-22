#include "myapp.h"

MyApp::MyApp(SemaphoreHandle_t mutex) : mutex_(mutex)
{
    LOGI("MyApp initialized!");
    current_config = config_disc_1;
}

void MyApp::render()
{
    current_config.position = current_position;
    motor_notifier->requestUpdate(current_config); // Prevents state after moving back from submenus to be reset to page 0, i.e. moves user to correct page on the onboarding menu.
}

void MyApp::handleNavigationEvent(NavigationEvent event)
{
}

EntityStateUpdate MyApp::update(AppState state)
{
    return updateStateFromKnob(state.motor_state);
}

EntityStateUpdate MyApp::updateStateFromKnob(PB_SmartKnobState state)
{
    if (current_position != state.current_position)
    {
        current_position = state.current_position;
    }
    LOGI("L: %d", state.current_position)
    LOGI("S: %f", state.sub_position_unit)
    EntityStateUpdate new_state;
    return new_state;
}

void MyApp::setMotorNotifier(MotorNotifier *motor_notifier)
{
    this->motor_notifier = motor_notifier;
}

void MyApp::triggerMotorConfigUpdate()
{
    if (this->motor_notifier != nullptr)
    {
        motor_notifier->requestUpdate(current_config);
    }
    else
    {
        LOGW("Motor_notifier is not set");
    }
}

void MyApp::setWiFiNotifier(WiFiNotifier *wifi_notifier)
{
    this->wifi_notifier = wifi_notifier;
}

void MyApp::setOSConfigNotifier(OSConfigNotifier *os_config_notifier)
{
    this->os_config_notifier = os_config_notifier;
}

void MyApp::handleEvent(WiFiEvent event)
{
    switch (event.type)
    {
    case SK_WIFI_AP_STARTED:
    case SK_AP_CLIENT:
    case SK_WEB_CLIENT:
    case SK_WIFI_STA_TRY_NEW_CREDENTIALS:
    case SK_WIFI_STA_TRY_NEW_CREDENTIALS_FAILED:
    case SK_WEB_CLIENT_MQTT:
    case SK_MQTT_TRY_NEW_CREDENTIALS:
    case SK_MQTT_TRY_NEW_CREDENTIALS_FAILED:
    case SK_MQTT_CONNECTED_NEW_CREDENTIALS:
    case SK_MQTT_STATE_UPDATE:
        break;
    default:
        break;
    }
}

void MyApp::setMotorConfig(int i, bool backward)
{
    int rot_amount = 0;
    switch (i)
    {
    case 0: // Blank
    case 5: // Windchime intro
        current_config = config_disc_1;
        // current_config.position = current_position;
        // current_config.position_nonce = current_position;
        // current_config.min_position = current_position;
        // current_config.max_position = current_config.max_position + current_position;
        triggerMotorConfigUpdate();
        LOGI("CONFIG CHANGED, %d", i)
        break;
    case 3: // Wave/Wind (disc.)
        current_config = config_disc_2;
        if (backward)
        {
            current_config.position = 1;
            current_config.position_nonce = 1;
            LOGI("CONFIG CHANGED, %d (INV)", i)
        }
        else
        {
            LOGI("CONFIG CHANGED, %d", i)
        }
        triggerMotorConfigUpdate();
        break;
    case 1: // Snow (cont.)
    case 2: // Bird/Book (cont.)
    case 4: // Car (cont.)
        current_config = config_cont_270;
        rot_amount = 270;
        if (backward)
        {
            current_config.position = current_position + rot_amount;
            current_config.position_nonce = current_position + rot_amount;
            current_config.min_position = current_position - current_config.max_position + rot_amount;
            current_config.max_position = current_position + rot_amount;
            LOGI("CONFIG CHANGED, %d (INV): Min:%d, Max:%d, Cur:%d", i, current_config.min_position, current_config.max_position, current_config.position)
        }
        else
        {
            current_config.position = current_position;
            current_config.position_nonce = current_position;
            current_config.min_position = current_position;
            current_config.max_position = current_position + rot_amount;
            LOGI("CONFIG CHANGED, %d", i)
        }
        triggerMotorConfigUpdate();
        break;
    case 6: // Windchime cont.
        current_config = config_cont_360;
        rot_amount = 360;
        if (backward)
        {
            current_config.position = current_position + rot_amount;
            current_config.position_nonce = current_position + rot_amount;
            current_config.min_position = current_position - current_config.max_position + rot_amount;
            current_config.max_position = current_position + rot_amount;

            for (int i = 0; i < current_config.detent_positions_count; i++)
            {
                current_config.detent_positions[i] = current_config.detent_positions[i] + current_position;
            }
            LOGI("CONFIG CHANGED, %d (INV)", i)
        }
        else
        {
            current_config.position = current_position;
            current_config.position_nonce = current_position;
            current_config.min_position = current_position;
            current_config.max_position = current_position + rot_amount;
            for (int i = 0; i < current_config.detent_positions_count; i++)
            {
                current_config.detent_positions[i] = current_config.detent_positions[i] + current_position;
            }
            LOGI("CONFIG CHANGED, %d", i)
        }
        triggerMotorConfigUpdate();
        break;
    default:
        break;
    }
}