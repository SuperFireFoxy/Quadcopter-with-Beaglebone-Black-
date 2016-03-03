/* 2014-0629 by Frank.gao
 * Test application for BBB_I2C
 *
 * Check:device ID access,
 *	initialize,
 *	read speed,
 *	cycle read,
 *	FUNCTIONS... 
 *
 * Copyright 2014 Frank.gao, fridaysun@msn.com
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "BBB_I2C.h"
#include "MPU6050.h"
#include "BBB_MPU6050.h"
#include <math.h>
#include "BBB_PWM.h"

int16_t ax,ay,az; 
int16_t gx,gy,gz;
using namespace std;
/*姿态融合后的角度数据*/
float XAngle;
float YAngle;
float ZAngle;
/*陀螺仪角速度*/
float gXDegreeRate;
float gYDegreeRate;
float gZDegreeRate;

float AZres,GZres,AXres,GXres,AYres,GYres;
/*陀螺仪每次采样时间差*/
double difference;

pid pidXres,pidYres,pidZres;
void *BBB_MPU6050(void *ptr){
	MPU6050 MPU;
	BBB_I2C BBB_I2C;
	uint8_t rxbuf;
	uint8_t txbuf = 0xaa;
	uint8_t addr = 0x54;  // i2c slave address for E2PROM A[2:0]=3'b000
//	uint8_t addr = 0x68;  // i2c slave address for MPU6050
	uint8_t offset = 0x55;
	uint8_t bitnum = 0x00;
	uint8_t DEV_ID;
	
	uint8_t bitlength = 0x04;
	uint8_t bitstart = 0x00;	
	
	cout << "Testing the MPU6050 00.00.01" << endl;
	if (MPU.testConnection() < 1){
		printf ("Device ID not match!\n");
		exit(1);
	}
	
	if (MPU.initialize() < 1) {
		printf ("MPU initialize fail!\n");
		exit(1);
	}
	
	struct timespec start, end, timepcs;
	clock_gettime( CLOCK_REALTIME, &start );	//must linked with the "librt" library to use these functions

//read 1000 times 
/*	for(int i=0;i<1000;i++){
	MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	clock_gettime( CLOCK_REALTIME, &timepcs );
    double difference = (timepcs.tv_sec - start.tv_sec) + (double)(timepcs.tv_nsec - start.tv_nsec)/1000000000.0d;
	printf ("ax\tay\taz\t:\tgx\tgy\tgz [Time:%f Sec]\n", difference);
	printf ("%d\t%d\t%d\t:\t%d\t%d\t%d\n",ax,ay,az,gx,gy,gz);
	printf ("%d\t%d\t%d\t:\t%d\t%d\t%d\n",ax/16384,ay/16384,az/16384,gx/33,gy/32.8,gz/32.8);
 	}
   	clock_gettime( CLOCK_REALTIME, &end );
     	double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
	printf ("Take [ %f ] Sec to finish 1000 times read\n", difference);
	*/
		

// cycle read
/*	while(1){
	MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    	clock_gettime( CLOCK_REALTIME, &timepcs );
    	double difference = (timepcs.tv_sec - start.tv_sec) + (double)(timepcs.tv_nsec - start.tv_nsec)/1000000000.0d;
	printf ("ax\tay\taz\t:\tgx\tgy\tgz [Time:%f Sec]\n", difference);
	printf ("%d\t%d\t%d\t:\t%d\t%d\t%d\n",ax,ay,az,gx,gy,gz);
	}
*/	
	int i=0;
	while(1){
		   
		   MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		   
		   
		   clock_gettime( CLOCK_REALTIME, &timepcs );
		   difference = (timepcs.tv_sec - start.tv_sec) + (double)(timepcs.tv_nsec - start.tv_nsec)/1000000000.0d;
		   MPU6050_GetAngle(ax,ay,az,gx,gy,gz);
		   PIDUpdate(XAngle,YAngle,ZAngle,0,0,0,&pidXres,&pidYres,&pidZres);
		   clock_gettime( CLOCK_REALTIME, &start);
		   if(i=1000)
		   	{	
			   printf ("ax\tay\taz\t:\tgx\tgy\tgz [Time:%f Sec]\n", difference);
			   printf ("%d\t%d\t%d\t:\t%d\t%d\t%d\n",ax,ay,az,gx,gy,gz);		   
			   printf ("%f\t%f\t%f\t:\n%f\t%f\t%f\n%f\t%f\t%f\n",AXres,AYres,AZres,GXres,GYres,GZres,XAngle,YAngle,ZAngle);
			   printf ("%f\t%f\t%f\n",pidXres.pidterm,pidYres.pidterm,pidZres.pidterm);
			   i=1;	
		   }
		   else{
			i++;	
		   }
	}

	//return 0;
}
float MPU6050_GetAngle(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz)
{
	gXDegreeRate=gx/32.8;
	gYDegreeRate=gy/32.8;
	gZDegreeRate=gz/32.8;
	
			//temp=(sqrt(ax*ax+ay*ay))/az;
	AZres=atan2(sqrt(ax*ax+ay*ay),az)*180/3.14;  //加速度计结果
	GZres=ZAngle-gZDegreeRate*difference;
	ZAngle=0.95*GZres+0.05*AZres;
		
			//temp=ax/(sqrt(ay*ay+az*az));
	AXres=atan2(ax,sqrt(ay*ay+az*az))*180/3.14;  //加速度计结果
	GXres=XAngle-gXDegreeRate*difference;
	XAngle=0.95*GXres+0.05*AXres;
		
			//temp=ay/(sqrt(ay*ay+az*az));
	AYres=atan2(ay,sqrt(ax*ax+az*az))*180/3.14;  //加速度计结果
	GYres=YAngle-gYDegreeRate*difference;
	YAngle=0.95*GYres+0.05*AYres;
		
}
float PIDUpdate(float nowXAngle,float nowYAngle,float nowZAngle,float targetXAngle,float targetYAngle,float targetZAngle,pid *pidX,pid *pidY,pid *pidZ)
{
	float Xerror=nowXAngle-targetXAngle;
	float Yerror=nowYAngle-targetYAngle;
	float Zerror=nowZAngle-targetZAngle;
	//printf ("%f\t%f\t%f\t error\n",Xerror,Yerror,Zerror);
	pidX->Pgain=1.5;
	pidX->Igain=2;
	pidY->Pgain=1.5;
	pidY->Igain=2;
	pidZ->Pgain=1.5;
	pidZ->Igain=2;
	if(Xerror>=-1.5 && Xerror<=1.5)
		{
		pidX->lasterror=Xerror;
		pidX->pidterm=0;
		}
	else
		{
		pidX->Pterm=pidX->Pgain*Xerror;
		pidX->Dterm=pidX->Dgain*(Xerror-pidX->lasterror);
		pidX->lasterror=Xerror;
		pidX->pidterm=pidX->Pterm+pidX->Dterm;
		}
	
	if(Yerror>=-1.5 && Yerror<=1.5)
		{
		pidY->lasterror=Yerror;
		pidY->pidterm=0;
		}
	else{
		pidY->Pterm=pidY->Pgain*Yerror;
		pidY->Dterm=pidY->Dgain*(Yerror-pidY->lasterror);
		pidY->lasterror=Yerror;
		pidY->pidterm=pidY->Pterm+pidY->Dterm;
		}
	
	if(Zerror>=-1.5 && Zerror<=1.5) 
		{
		pidZ->lasterror=Zerror;
		pidZ->pidterm=0;
		}
	else
		{
		pidZ->Pterm=pidZ->Pgain*Zerror;
		pidZ->Dterm=pidZ->Dgain*(Zerror-pidZ->lasterror);
		pidZ->lasterror=Zerror;
		pidZ->pidterm=pidZ->Pterm+pidZ->Dterm;
		}
	//printf ("%f\t%f\t%f\t pidterm\n",pidX->pidterm,pidY->pidterm,pidZ->pidterm);
	return 1;
	
}


