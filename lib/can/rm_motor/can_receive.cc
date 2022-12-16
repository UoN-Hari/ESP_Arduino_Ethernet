#include <rm_motor/can_receive.h>

namespace Motor {

static std::map<uint8_t, motor_rx_msg_t> map_motor_msg;

void update_feedback () {
    twai_status_info_t twai_status_info;

    twai_get_status_info (&twai_status_info);

    if (twai_status_info.msgs_to_rx != 0) {
        twai_message_t rx_data;

        CAN::receive (&rx_data, pdMS_TO_TICKS (1));

        if (rx_data.identifier > 0x200 && rx_data.identifier < 0x20C) {
            uint8_t motor_id = rx_data.identifier - 0x200;
            motor_rx_msg_t motor_msg;

            motor_msg.encoder = rx_data.data[0] << 8 | rx_data.data[1];
            motor_msg.angular_vel = rx_data.data[2] << 8 | rx_data.data[3];
            motor_msg.torque_current = rx_data.data[4] << 8 | rx_data.data[5];
            motor_msg.temperature = rx_data.data[6];

            map_motor_msg[motor_id - 1] = motor_msg;
        }
    }
}

motor_rx_msg_t get_motor_msg (motor_type_t motor_type, uint8_t motor_id) {
    if (motor_type == motor_6020) {
        return map_motor_msg[motor_id - 1 + 4];
    }
    else {
        return map_motor_msg[motor_id - 1];
    }
}

}