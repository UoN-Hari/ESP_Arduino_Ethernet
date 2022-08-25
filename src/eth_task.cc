#include <Arduino.h>
#include <ethernet.h>
#include <geometry_msgs/TwistStamped.h>
#include <ros_eth/eth_rosmsg.h>

// char* eth_msg;
RosETH rosmsg;
geometry_msgs::TwistStamped twist;

void Ethernet_thread(void* pvParameter) {
    
    for(;;) {
        if(rosmsg.getMsg(&twist))
            Serial.println(twist.header.stamp.sec);
        vTaskDelay(1000);
    }
}