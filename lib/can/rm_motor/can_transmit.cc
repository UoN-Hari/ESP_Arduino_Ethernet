#include <rm_motor/can_transmit.h>

namespace Motor {

void send_current (motor_tx_header motor_type, motor_tx_msg_t motor_tx_msg) {
    twai_status_info_t twai_status_info;

    twai_get_status_info (&twai_status_info);

    if (twai_status_info.msgs_to_tx == 0) {
        twai_message_t tx_msg;

        tx_msg.identifier = motor_type;
        tx_msg.flags = TWAI_MSG_FLAG_NONE;

        if (motor_type == M2006_M3508_ID_1TO4 || motor_type == GM6020_ID_1TO4) {
            tx_msg.data_length_code = TWAI_FRAME_MAX_DLC;

            for (uint8_t i = 0; i < 4; i++) {
                tx_msg.data[2 * i] = (uint8_t)(motor_tx_msg.current[i] >> 8);
                tx_msg.data[2 * i + 1] = (uint8_t)(motor_tx_msg.current[i]);
            }
        }
        else {
            tx_msg.data_length_code = 6;

            for (uint8_t i = 0; i < 3; i++) {
                tx_msg.data[2 * i] = (uint8_t)(motor_tx_msg.current[i + 4] >> 8);
                tx_msg.data[2 * i + 1] = (uint8_t)(motor_tx_msg.current[i + 4]);
            }
        }
        CAN::send (tx_msg, pdMS_TO_TICKS (1));
    }
}

}