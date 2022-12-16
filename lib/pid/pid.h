#ifndef PID_H
#define PID_H

#include <Arduino.h>

#define saturation(input, max) \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }


class PID {
private:
    float pid[3];
    float limit;
    float i_limit;

    float error[2];

    float i_output;
    float output;
public:
    PID (float _kp, float _ki, float _kd, float _limit, float _i_limit);
    ~PID ();

    float calc (float _set, float _ref);
    float calc (float _offset, float _angle, float _angular_vel);
};

#endif