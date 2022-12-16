#include <pid.h>

PID::PID (float _kp, float _ki, float _kd, float _limit, float _i_limit) {
    pid[0] = _kp;
    pid[1] = _ki;
    pid[2] = _kd;

    limit = _limit;
    i_limit = _i_limit;

    output = i_output = error[0] = error[1] = 0.0f;
}

PID::~PID () {}

float PID::calc (float _set, float _ref) {
    error[0] = _set - _ref;
    i_output += pid[1] * error[0];
    saturation (i_output, i_limit);
    output = pid[0] * error[0] + i_output + pid[2] * (error[0] - error[1]);
    saturation (output, limit);
    error[1] = error[0];

    return output;
}

float PID::calc (float _offset, float _angle, float _angular_vel) {
    output = pid[0] * (_angle - _offset) + pid[2] * _angular_vel;
    saturation (output, limit);
    return output;
}