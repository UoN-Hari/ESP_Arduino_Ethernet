#ifndef ETHERNET_ETH_ROSMSG_H
#define ETHERNET_ETH_ROSMSG_H

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <ethernet.h>

class RosETH {
private:
    char* buffer = nullptr;
public:
    RosETH (/* args */);
    ~RosETH ();

    /**
     * @brief Getting ros_msgs from eth port
     *
     * @param msg The buffer to store the deserialized ros_msg
     *
     * @return false is no data receiving form eth port,
     *         and true is have data received
     */
    bool getMsg (geometry_msgs::TwistStamped* msg);
    bool getMsg (geometry_msgs::Twist* msg);
};



#endif