#ifndef _BBB_OPEN_PWM_H_
#define _BBB_OPEN_PWM_H_

#define Dev_Tree "/sys/devices/bone_capemgr.9/"
#define PWM_File "/sys/devices/ocp.3/"



void Open_PWM();
void SetPWM_P8_13(int period,int duty);
void SetPWM_P9_14(int period,int duty);
void SetPWM_P9_21(int period,int duty);
void SetPWM_P9_42(int period,int duty);




#endif

