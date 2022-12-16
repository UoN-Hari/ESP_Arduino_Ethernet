#include <pid.h>
#include <ethernet.h>
#include <rm_motor/can_receive.h>
#include <rm_motor/can_transmit.h>
#include <geometry_msgs/TwistStamped.h>
#include <ros_eth/eth_rosmsg.h>
#include "motor_task.h"

namespace Control {

TaskHandle_t hRxMsgThread;
TaskHandle_t hControlThread;

static motor_rx_msg_t rx_msg;
static float cmd_pos;

void CreateThread () {
    xTaskCreatePinnedToCore (
        Control::RxMsg_thread,
        "rx_msg_thread",
        1024 * 8,
        NULL,
        6,
        &hRxMsgThread,
        ARDUINO_EVENT_RUNNING_CORE
    );

    xTaskCreatePinnedToCore (
        Control::MotorControl_thread,
        "motor_ctl_thread",
        1024 * 8,
        NULL,
        5,
        &hControlThread,
        ARDUINO_RUNNING_CORE
    );
}

void RxMsg_thread (void* pvParam) {
    RosETH rosmsg;
    geometry_msgs::TwistStamped twist;
    int64_t time_cnt[2] = { 0 };
    double thread_freq;
    for (;;) {
        time_cnt[0] = esp_timer_get_time ();
        Motor::update_feedback ();
        rosmsg.getMsg (&twist);

        cmd_pos = twist.twist.angular.z;

        rx_msg = Motor::get_motor_msg (motor_6020, 2);
        
        thread_freq = 1e6 / (time_cnt[0] - time_cnt[1]);
        time_cnt[1] = time_cnt[0];

        Serial.printf ("ECD:%d, RPM:%d, Current:%d, Temp:%d, Task frequency: %.2f\n",
            rx_msg.encoder,
            rx_msg.angular_vel,
            rx_msg.torque_current,
            rx_msg.temperature,
            thread_freq);
        
        vTaskDelay (1);
    }
    vTaskDelete (NULL);
}

void MotorControl_thread (void* pvParam) {
    motor_tx_msg_t tx_msg;
    PID pid_vel (10.0f, 0.0f, 0.0f, 30000.0f, 2000.0f);
    PID pid_pos (0.6f, 0.0f, 0.0f, 300.0f, 50.0f);
    for (;;) {
        
        tx_msg.current[1] = pid_vel.calc(pid_pos.calc ((cmd_pos+180.0f) / 360.0f * 8191.0f, rx_msg.encoder), rx_msg.angular_vel);
        Motor::send_current (GM6020_ID_1TO4, tx_msg);

        vTaskDelay (1);
    }
    vTaskDelete (NULL);
}

}
