#ifndef ETHERNET_ETHERNET_H
#define ETHERNET_ETHERNET_H

#include <Arduino.h>
#include <ETH.h>
#include <WiFiUdp.h>
#include <AsyncUDP.h>

#define PRIORITY_REALTIME 4u
#define PRIORITY_HIGH     3u
#define PRIORITY_MIDIUM   2u
#define PRIORITY_LOW      1u

#define ETH_ADDR        1
#define ETH_POWER_PIN   5
#define ETH_MDC_PIN     23
#define ETH_MDIO_PIN    18
#define ETH_TYPE        ETH_PHY_IP101
#define ETH_REFCLK      ETH_CLOCK_GPIO0_IN

class Ethernet_t {


/* Thread Parameters */
private:
    TaskHandle_t thread_handler;
    const uint32_t stack_depth = 1024;
    const uint8_t thread_priority = PRIORITY_REALTIME;
    const char* thread_name = "Ethernet";
/* Thread API */
public:
    void CreateThread();
    friend void Ethernet_thread(void* pvParameter);
    friend class RosETH;

/* Ethernet Parameters */
private:
    WiFiUDP udp;
    ETHClass ethernet;
    uint32_t locol_port = 8888;
/* Ethernet API */
public:
    bool Init();
    void PrintETHInfo();


/* Singuleton Parameters */
private:
    static Ethernet_t instance;
/* Constructor and Destructor */
private:
    Ethernet_t();
    ~Ethernet_t();
    Ethernet_t(const Ethernet_t&);
    Ethernet_t& operator=(const Ethernet_t&);
/* Class Instance API */
public:
    static Ethernet_t& getInstance();


};

/* Thread entry function */
extern void Ethernet_thread(void* pvParameter);

#endif