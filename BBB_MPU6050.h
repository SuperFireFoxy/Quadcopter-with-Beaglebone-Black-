#ifndef _BBB_MPU6050_H_
#define _BBB_MPU6050_H_
struct pid{
	float Pgain;
	float Pterm;
	
	float Igain;
	float Iterm;
	
	float Dgain;
	float Dterm;
	float sumerror;
	float lasterror;
	float pidterm;
};
float MPU6050_GetAngle(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz);
float PIDUpdate(float nowXAngle,float nowYAngle,float nowZAngle,float targetXAngle,float targetYAngle,float targetZAngle,pid *pidX,pid *pidY,pid *pidZ);


void *BBB_MPU6050(void *ptr);



#endif



