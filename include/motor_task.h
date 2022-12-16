#ifndef CAN_TASK_H
#define CAN_TASK_H

#include <Arduino.h>
#include <can.h>

namespace Control
{

void CreateThread();
void MotorControl_thread (void* pvParam);
void RxMsg_thread (void* pvParam);

}

#endif