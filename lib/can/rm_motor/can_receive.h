#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H

#include <Arduino.h>
#include <can.h>
#include <map>

typedef enum {
    motor_2006,
    motor_3508,
    motor_6020
} motor_type_t;

typedef struct {
    uint16_t encoder;
    int16_t angular_vel;
    int16_t torque_current;
    uint8_t temperature;
} motor_rx_msg_t;

namespace Motor {

void update_feedback ();
motor_rx_msg_t get_motor_msg (motor_type_t motor_type, uint8_t motor_id);

}

#endif