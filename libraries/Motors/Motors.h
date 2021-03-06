#ifndef Motors_h
#define Motors_h

#define STANDBY_SPEED 850

#include "PID.h"

class Motors
{
  public:
    void setup_pids();
    void calc_thrust_level_mode(float angle_pitch, float angle_roll, int gyro_x, int gyro_y, int tx_pitch, int tx_roll, int tx_throttle, int tx_yaw);
    void calc_thrust_debug(int tx_pitch, int tx_roll, int tx_throttle, int tx_yaw);
    int get_front_left_thrust() { return front_left_thrust; }
    int get_front_right_thrust() { return front_right_thrust; }
    int get_rear_left_thrust() { return rear_left_thrust; }
    int get_rear_right_thrust() { return rear_right_thrust; }
  private:
    int front_left_thrust, front_right_thrust, rear_left_thrust, rear_right_thrust;
    PID *pid_acro_pitch;
    PID *pid_acro_roll;
    PID *pid_level_pitch;
    PID *pid_level_roll;
    float total_pitch, total_roll;
    int standby_speed;
};

#endif