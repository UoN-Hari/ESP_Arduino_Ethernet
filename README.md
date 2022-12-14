# ESP32-ROS-ETH
__This repository is a part of AnywhereInLoop project__  

### Introduction
This is an template PlatformIO project for ESP32-ETH-Kit, please use PIO-IDE to open this project and the dependency will be installed by PIO-IDE automatically.  

This project realized the communication between PC and ESP32 through UDP. Support the ros_msg data format.
  
### Mention
This project did __not__ initialize a ROS node in ESP32. To transmitting data, an extra node is required for building interface between ROS and ESP32.

### Manual
The file structure is shown below:
```python
.
├── includes # Headers are here
│   └── README
├── lib # Self-defined libiraries
│   ├── ethernet
│   ├── README
│   └── ros_lib # Generated By ROS_Serial
├── platformio.ini # Project configuration file
├── README.md # This file
├── src # Source codes are here
│   ├── eth_task.cc # Ethernet have an individual thread
│   └── main.cpp # main task is used for initialize device
└── test # Unused
    └── README
```
  
For self-defined libiraries, here gives using guidance:
```python
ethernet
├── ethernet.cc
├── ethernet.h # Initialize connection and create a thread
└── ros_eth
    ├── eth_rosmsg.cc
    └── eth_rosmsg.h # Defines the receiviable format of ros_msg
```
In `ethernet.h`, The `class Ethernet_t` is defined as a singuleton class, which can only get the instance by using function below:
```cpp
Ethernet_t::getInstance()
```
Here are provided API in `ethernet.h`:
```cpp
void Ethernet_thread(void* pvParameter);
bool Init(IPAddress static_ip, IPAddress gateway, IPAddress subnet);
void getETHStatus();
```

The function 
```cpp
void Ethernet_thread(void* pvParameter);
```
have an weak define in `ethernet.cc`, which can be overwrite by user, is an FreeRTOS thread entry function.

In `ros_eth/eth_rosmsg.h`, Here provided 2 often used ros_msg format, you can override the function due to your requirements:
```cpp
bool getMsg(geometry_msgs::Twist* msg);
bool getMsg(geometry_msgs::TwistStamped* msg);
```
