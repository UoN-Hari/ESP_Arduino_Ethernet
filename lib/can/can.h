#ifndef CAN_H
#define CAN_H

#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/twai.h>

using can_frame_data = twai_message_t;

typedef enum {
    b25K,
    b50K,
    b100k,
    b125k,
    b250k,
    b500k,
    b800k,
    b1000k
} can_baudrate_t;

namespace CAN {

/**
 * @brief 打开CAN通讯接口
 * 
 * @param TX_PIN CAN_TX对应引脚，类型为gpio_num_t
 *      - GPIO_NUM_X: The number X pin of ESP32
 *
 * @param RX_PIN CAN_RX对应引脚，类型为gpio_num_t
 *      - GPIO_NUM_X: The number X pin of ESP32
 *
 * @param baudrate 波特率设置，类型为can_baudrate_t
 *      - b25k: Baudrate = 25Kbps
 *      - b50k: Baudrate = 50Kbps
 *      - b100k: Baudrate = 100Kbps
 *      - b125k: Baudrate = 125Kbps
 *      - b250k: Baudrate = 250Kbps
 *      - b500k: Baudrate = 500Kbps
 *      - b800k: Baudrate = 800Kbps
 *      - b1000k: Baudrate = 1Mbps
 */
void open (gpio_num_t TX_PIN, gpio_num_t RX_PIN, can_baudrate_t baudrate);

/**
 * @brief 关闭CAN通讯接口
 * 
 */
void close ();

/**
 * @brief CAN发送函数
 * 
 * @param frame 发送帧内容，类型为can_frame_data
 *      - identifier: CAN_ID
 *      - flag: containing config for EXT and RTR
 *      - data_length_code: The length of data field
 *      - data: data field
 *
 * @param ticks_to_wait 最长等待时间，类型为TickType_t
 *      - pdMS_TO_TICKS(x): maximum wait for x micro seconds
 *
 * @return esp_err_t 返回发送状态
 *      - ESP_OK: Transmission successfully queued/initiated
 *      - ESP_ERR_INVALID_ARG: Arguments are invalid
 *      - ESP_ERR_TIMEOUT: Timed out waiting for space on TX queue
 *      - ESP_FAIL: TX queue is disabled and another message is currently transmitting
 *      - ESP_ERR_INVALID_STATE: TWAI driver is not in running state, or is not installed
 *      - ESP_ERR_NOT_SUPPORTED: Listen Only Mode does not support transmissions
 */
inline esp_err_t send (const can_frame_data frame, TickType_t ticks_to_wait) {
    return twai_transmit ((twai_message_t*)&frame, ticks_to_wait);
}

/**
 * @brief CAN接收函数
 * 
 * @param frame 接收帧内容，类型为can_frame_data
 *      - identifier: CAN_ID
 *      - flag: containing config for EXT and RTR
 *      - data_length_code: The length of data field
 *      - data: data field
 *
 * @param ticks_to_wait 最长等待时间，类型为TickType_t
*      - pdMS_TO_TICKS(x): maximum wait for x micro seconds

 * @return esp_err_t 返回接收状态
 *      - ESP_OK: Message successfully received from RX queue
 *      - ESP_ERR_TIMEOUT: Timed out waiting for message
 *      - ESP_ERR_INVALID_ARG: Arguments are invalid
 *      - ESP_ERR_INVALID_STATE: TWAI driver is not installed
 */
inline esp_err_t receive (const can_frame_data* frame, TickType_t ticks_to_wait) {
    return twai_receive ((twai_message_t*)frame, ticks_to_wait);
}

}

#endif