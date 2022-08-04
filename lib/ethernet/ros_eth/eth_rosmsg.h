#ifndef ETHERNET_ETH_ROSMSG_H
#define ETHERNET_ETH_ROSMSG_H

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <ethernet.h>


class RosETH
{
private:
    char* buffer;
public:
    RosETH(/* args */);
    ~RosETH();

    void getMsg(geometry_msgs::TwistStamped* msg);
    void getMsg(geometry_msgs::Twist* msg);
};



#endif