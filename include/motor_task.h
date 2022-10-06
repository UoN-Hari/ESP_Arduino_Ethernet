#ifndef CAN_TASK_H
#define CAN_TASK_H

#include <Arduino.h>
#include <can.h>

namespace Control
{

enum ControlID {
    M3508_ID_1TO4 = 0x200,
    M3508_ID_5TO7 = 0x1ff,
    M6020_ID_1TO4 = 0x1ff,
    M6020_ID_5TO7 = 0x2ff,
    M2006_ID_1TO4 = 0x200,
    M2006_ID_5TO7 = 0x1ff,
};

struct motor_feedback {
    int16_t encoder;
    int16_t speed_rpm;
    int16_t torque_current;
    uint8_t temperature;
};

struct cmd_current {
    int16_t value[4];
};

class Motor {
private:
    twai_message_t tx_message;
    twai_message_t rx_message;
public:
    Motor();
    ~Motor();

    friend void CreateThread();
    friend void MotorControl_thread(void *pvParam);
    
    void UpdatingFeedback();
    void TransmittingMsg(ControlID STD_ID, struct cmd_current* current);
};

extern void CreateThread();
extern void MotorControl_thread(void *pvParam);

}

#endif