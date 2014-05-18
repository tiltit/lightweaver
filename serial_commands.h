#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H



/**
 * CMD_MOTOR : {uint8t speed, int16_t steps}
 */
#define CMD_MOTOR1            1
#define CMD_MOTOR2            2

/* CMD_LED_COLOR : {uint8_t r, g, b} */
#define CMD_LED_COLOR         3

#define CMD_RELEASE_MOTOR1    4
#define CMD_RELEASE_MOTOR2    5

#define CMD_SHUTTER_OPEN       6
#define CMD_SHUTTER_CLOSE      7


#endif