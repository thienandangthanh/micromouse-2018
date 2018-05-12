// test_stepper.ino
#include <CheapStepper.h>
#define IN_A_1 2
#define IN_A_2 3
#define IN_A_3 4
#define IN_A_4 5

#define IN_B_1 6
#define IN_B_2 7
#define IN_B_3 8
#define IN_B_4 9
CheapStepper stepper_left(IN_A_1, IN_A_2, IN_A_3, IN_A_4);
CheapStepper stepper_right(IN_B_1, IN_B_2, IN_B_3, IN_B_4);
#define offset_A 1  // true - CW; 0 = false - CCW
#define offset_B 1  // true
// #define ONE_REVOLUTION 836417  // 204*4096 //4096*65*3.14 // 2*pi*R = pi*d // d = 65mm
unsigned long int ONE_REVOLUTION = 836417;  // 204*4096 //4096*65*3.14 // 2*pi*R = pi*d // d = 65mm
// steps to turn with 1 wheel
// steps to turn with 2 wheel: TURN_STEPS*2
// #define TURN_STEPS 572624 //572624.376  // 286312.188*2 //4096*(1/4)*89*2*pi
unsigned long int TURN_STEPS = 572624; //572624.376  // 286312.188*2 //4096*(1/4)*89*2*pi
#define RPM 20
// sets speed (10-24 rpm, hi-low torque)
// <6 rpm blocked in code, may overheat
// 23-24rpm may skip

// don't need to use these
/*
stepper.step(moveClockwise);
// stepper.stepCW();
stepper.step(!moveClockwise);
// stepper.stepCCW();
*/

// should use these ones
/*stepper_left.newMove(offset_A, numSteps);
stepper_right.newMove(offset_B, numSteps);
stepper_left.newMoveDegrees(offset_A, deg);
stepper_right.newMoveDegrees(offset_B, deg);*/

void go_forward(int _numSteps) {
  stepper_left.newMove(offset_A, _numSteps);
  stepper_right.newMove(offset_B, _numSteps);
}
void go_back(int _numSteps) {
  stepper_left.newMove(!offset_A, _numSteps);
  stepper_right.newMove(!offset_B, _numSteps);
}
void turn_left() {
  // turn with both wheel
  stepper_left.newMove(offset_A, TURN_STEPS / 2);
  stepper_right.newMove(offset_B, TURN_STEPS / 2);
  // turn with only one wheel
  stepper_right.newMove(offset_B, TURN_STEPS);
}
void turn_right() {
  // turn with both wheel
  stepper_left.newMove(offset_A, TURN_STEPS / 2);
  stepper_right.newMove(offset_B, TURN_STEPS / 2);
  // turn with only one wheel
  stepper_left.newMove(offset_A, TURN_STEPS);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepper_left.setRpm(RPM);
  stepper_right.setRpm(RPM);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Go forward");
  go_forward(ONE_REVOLUTION);
  delay(1000);
  /*Serial.println("Go back");
  go_back(ONE_REVOLUTION);
  delay(1000);
  Serial.println("Turn left");
  turn_left();
  delay(1000);
  Serial.println("Turn right");
  turn_right();
  delay(1000);*/
}
