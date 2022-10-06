#include "motor_task.h"

namespace Control {

Motor motor;
struct cmd_current cmd_current = {0};
volatile motor_feedback feedback;

/**
 * @brief Create a Thread object
 * 
 * @brief Thread name: motor_ctl_thread
 * @brief Thread entry function: Control::MotorControl_thread
 * @brief Thread stack size: 1024 bytes
 * @brief Thread parameters: NONE
 * @brief Thread running core: CPU1
 */
void CreateThread() {
    TaskHandle_t hControlThread;

    xTaskCreatePinnedToCore (
		Control::MotorControl_thread,
		"motor_ctl_thread",
       	1024,
       	NULL,
       	5,
       	&hControlThread,
       	ARDUINO_RUNNING_CORE
	);
}

/**
 * @brief The motor control thread
 * @brief Operating frequency: 1000Hz
 * @brief Using hardware: CAN
 * 
 * @param pvParam Reserved
 */
void MotorControl_thread(void* pvParam) {
    uint32_t time_cnt = 0;
    for (;;) {
        motor.UpdatingFeedback();

        cmd_current.value[0] = 1000;
        
        motor.TransmittingMsg(M3508_ID_1TO4, &cmd_current);
        vTaskDelay(1);
    }
}

Motor::Motor() {}
Motor::~Motor() {}

/**
 * @brief Send control data to motor
 * 
 * @param STD_ID The CAN ID for controlling motor, only accepts:
 * @param STD_ID M3508_ID_1TO4
 * @param STD_ID M3508_ID_5TO7
 * @param STD_ID M6020_ID_1TO4
 * @param STD_ID M6020_ID_5TO7
 * @param STD_ID M2006_ID_1TO4
 * @param STD_ID M2006_ID_5TO7
 * 
 * @param current The control current (voltage) applied to the motor
 * @param current For one specified ID, have 4 variables to control 4 motors with different ID.
 */
void Motor::TransmittingMsg(ControlID STD_ID, struct cmd_current* current) {
    tx_message.identifier = (uint32_t)STD_ID;
    tx_message.flags = TWAI_MSG_FLAG_NONE;
    tx_message.data_length_code = 8;

    for (uint8_t i = 0; i < 4; i++) {
        tx_message.data[2*i] = (uint8_t)(current->value[i] >> 8);
        tx_message.data[2*i+1] = (uint8_t)current->value[i];
    }

    twai_transmit(&tx_message, 1);
}

/**
 * @brief Receiving feedback value send by motor
 * @brief This function has not been implemented for multiple motors
 * TODO: Implement the function to accept multiple motors data
 */
void Motor::UpdatingFeedback() {
    twai_receive(&rx_message, 1);

    if (rx_message.identifier > 0x200 && rx_message.identifier < 0x20C) {
        feedback.encoder = (int16_t)((rx_message.data[0] << 8) | (uint8_t)rx_message.data[1]);
        feedback.speed_rpm = (int16_t)((rx_message.data[2] << 8) | (uint8_t)rx_message.data[3]);
        feedback.torque_current = (int16_t)((rx_message.data[4] << 8) | (uint8_t)rx_message.data[5]);
        feedback.temperature = rx_message.data[6];
    }

}

}
