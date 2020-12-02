#ifndef _MORTOR_H_
#define _MORTOR_H_

#define motor_1 1
#define motor_2 2
#define motor_3 3
#define motor_4 4

extern void tim_motor_init(void);
extern void motor_run(int motor_num,int speed_set);

#endif
