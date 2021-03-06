#include "TxRx.h"

void TxRx::receive() 
{
  switch(read_switcher) { // reads one channel per cycle, this reduced cycle time from ~70ms to ~20ms
  case 1:
    rx_ch1 = pulseIn(A0, HIGH, 25000);
    break;
  case 2:
    rx_ch2 = pulseIn(A1, HIGH, 25000);
    break;
  case 3:
    rx_ch3 = pulseIn(A2, HIGH, 25000);
    break;
  default:
    rx_ch4 = pulseIn(A3, HIGH, 25000);
    read_switcher = 0;
    break;
  }
  read_switcher += 1;
}

void TxRx::update()
{
  roll = 0; // ch1;
  pitch = 0; // ch2;
  throttle = rx_ch3 - 100;
  yaw = 0; // ch4;
  // roll = ch1;
  // pitch = ch2;
  // yaw = ch4;
  // roll /= 8;
  // pitch /= 8;
  // yaw /= 8;
}