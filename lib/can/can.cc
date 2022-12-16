#include <can.h>

void CAN::open (gpio_num_t TX_PIN, gpio_num_t RX_PIN, can_baudrate_t baudrate) {
    twai_general_config_t set_pin;
    twai_timing_config_t set_baudrate;
    twai_filter_config_t set_filter;
    esp_err_t driver_stat;
    esp_err_t start_stat;

    set_pin = TWAI_GENERAL_CONFIG_DEFAULT (TX_PIN, RX_PIN, TWAI_MODE_NORMAL);
    set_filter = TWAI_FILTER_CONFIG_ACCEPT_ALL ();
    
    switch (baudrate) {
    case b50K:
        set_baudrate = TWAI_TIMING_CONFIG_50KBITS ();
        break;
    case b100k:
        set_baudrate = TWAI_TIMING_CONFIG_100KBITS ();
        break;
    case b125k:
        set_baudrate = TWAI_TIMING_CONFIG_125KBITS ();
        break;
    case b250k:
        set_baudrate = TWAI_TIMING_CONFIG_250KBITS ();
        break;
    case b500k:
        set_baudrate = TWAI_TIMING_CONFIG_500KBITS ();
        break;
    case b800k:
        set_baudrate = TWAI_TIMING_CONFIG_800KBITS ();
        break;
    case b1000k:
        set_baudrate = TWAI_TIMING_CONFIG_1MBITS ();
        break;
    default:
        break;
    }

    driver_stat = twai_driver_install (&set_pin, &set_baudrate, &set_filter);    
    start_stat = twai_start ();

    if (Serial) {
        Serial.println ("-------- Initializing CAN device --------");
        switch (driver_stat) {
        case ESP_OK:
            Serial.println ("- CAN driver is installed");
            break;
        case ESP_ERR_INVALID_ARG:
            Serial.println ("- Install CAN driver failed: Invalid arguments");
            break;
        case ESP_ERR_NO_MEM:
            Serial.println ("- Install CAN driver failed: Memory is insufficient");
            break;
        case ESP_ERR_INVALID_STATE:
            Serial.println ("- Install CAN driver failed: Driver already installed");
            break;
        default:
            break;
        }

        switch (start_stat)
        {
        case ESP_OK:
            Serial.println ("- Device is on running state");
            break;
        case ESP_ERR_INVALID_STATE:
            Serial.println ("- CAN driver running error: Driver is not in stopped state, or is not installed");
        default:
            break;
        }
    }
}

void CAN::close () {
    twai_stop ();
    twai_driver_uninstall ();
}