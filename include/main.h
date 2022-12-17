#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#define CAN_TX_PIN GPIO_NUM_33
#define CAN_RX_PIN GPIO_NUM_35

#define cvt_to_ecd(angle, max_ecd) ((angle) / 360.0f * (max_ecd))

#endif