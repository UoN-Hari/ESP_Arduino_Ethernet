#ifndef CAN_TRANSMIT_H
#define CAN_TRANSMIT_H

#include <Arduino.h>
#include <rm_motor/can_receive.h>
#include <can.h>

typedef struct {
    int16_t current[7];
} motor_tx_msg_t;

typedef enum {
    M2006_M3508_ID_1TO4 = 0x200,
    M2006_M3508_ID_5TO7 = 0x1ff,
    GM6020_ID_1TO4 = 0x1ff,
    GM6020_ID_5TO7 = 0x2ff,
} motor_tx_header;

namespace Motor {

void send_current (motor_tx_header tx_header, motor_tx_msg_t tx_msg);

}

#endif