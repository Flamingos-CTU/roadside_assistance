#pragma once

constexpr int start_button_pin = 2;
constexpr int servo_left = 5;
constexpr int servo_right = 6;

constexpr uint8_t leftServoZeroPos = 88;
constexpr uint8_t rightServoZeroPos = 87;

struct sens_environment{
  bool obstacleFront;
  bool obstacleLeft;
  bool obstacleBack;
  bool obstacleRight;
  bool blackLM; // line sensor middle detecting black
  bool blackLL; // line sensor front left detecting black
  bool blackLR; // line sensor front right detecting black
  bool blackLML;// line sensor front middle left detecting black
  bool blackLMR;// line sensor front middle right detecting black
  bool blackLRL;// line sensor rear middle left detecting black
  bool blackLRR;// line sensor rear middle right detecting black
  };

