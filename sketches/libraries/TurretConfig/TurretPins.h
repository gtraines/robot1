#ifndef TURRET_CONFIG__TURRET_PINS_H
#define TURRET_CONFIG__TURRET_PINS_H

#include <Arduino.h>
#include <avr/io.h>

#define TRAVERSE_SERVO 3

#define ELEVATION_MOTOR_POS 23
#define ELEVATION_MOTOR_NEG 22
#define ELEVATION_MOTOR_ENABLE 8
#define ELEVATION_MOTOR_POSITION A0

#define IR_TRIGGER 2

#define IR_SXR_HIT_PIN 12
#define IR_SXR_REAR_PIN 18
#define IR_SXR_RIGHT_PIN 19
#define IR_SXR_LEFT_PIN 20
#define IR_SXR_FRONT_PIN 21

#define ARD_STATUS_GRN 24
#define ARD_STATUS_RED 25

#define ACTY_LED_1 27
#define ACTY_LED_2 31
#define ACTY_LED_3 29

#define MOVE_LED_GRN 50
#define MOVE_LED_RED 51
#define MOVE_LED_BLUE 53

#define CANNON_LED 52

#endif // !TURRET_CONFIG__TURRET_PINS_H

