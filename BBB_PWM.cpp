#include "BBB_PWM.h"
#include <stdio.h>
#include <stdlib.h>

void Open_PWM()
{
  //¿ªÆôPWM
    FILE *stream=NULL;
    stream=fopen(PWM_File"pwm_test_P8_13.15/run","r+");
    if(stream==NULL)
    {

    	system("echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots");
    	system("echo bone_pwm_P8_13 > /sys/devices/bone_capemgr.9/slots");
		system("echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.9/slots");
		system("echo bone_pwm_P9_21 > /sys/devices/bone_capemgr.9/slots");
		system("echo bone_pwm_P9_42 > /sys/devices/bone_capemgr.9/slots");
		
    }
	system("echo 0 > /sys/devices/ocp.3/pwm_test_P8_13.15/run");
	system("echo 0 > /sys/devices/ocp.3/pwm_test_P9_14.16/run");
	system("echo 0 > /sys/devices/ocp.3/pwm_test_P9_21.17/run");
	system("echo 0 > /sys/devices/ocp.3/pwm_test_P9_42.18/run");
	system("echo 20000000 > /sys/devices/ocp.3/pwm_test_P8_13.15/period");
	system("echo 20000000 > /sys/devices/ocp.3/pwm_test_P9_14.16/period");
	system("echo 20000000 > /sys/devices/ocp.3/pwm_test_P9_21.17/period");
	system("echo 20000000 > /sys/devices/ocp.3/pwm_test_P9_42.18/period");
	system("echo 18000000 > /sys/devices/ocp.3/pwm_test_P8_13.15/duty");
	system("echo 18000000 > /sys/devices/ocp.3/pwm_test_P9_14.16/duty");
	system("echo 18000000 > /sys/devices/ocp.3/pwm_test_P9_21.17/duty");
	system("echo 18000000 > /sys/devices/ocp.3/pwm_test_P9_42.18/duty");
	system("echo 1 > /sys/devices/ocp.3/pwm_test_P8_13.15/run");
	system("echo 1 > /sys/devices/ocp.3/pwm_test_P9_14.16/run");
	system("echo 1 > /sys/devices/ocp.3/pwm_test_P9_21.17/run");
	system("echo 1 > /sys/devices/ocp.3/pwm_test_P9_42.18/run");								
	
    
    
}
void SetPWM_P8_13(int period,int duty)
{
	

	FILE *stream_duty=NULL;
	FILE *stream_period=NULL;


	char buff[50];
    sprintf(buff,"%d",duty);
    printf("buff=%s \n",buff);
    int length=0;
    for(int m=0;(buff[m])!='\0';m++)
    {
    	 length++;
    }
    printf("length=%d \n",length);		
    stream_duty=fopen(PWM_File"pwm_test_P8_13.15/duty","r+");
    fwrite(buff,sizeof(char),length,stream_duty);
    fclose(stream_duty);
	

}
void SetPWM_P9_14(int period,int duty)
{
	

	FILE *stream_duty=NULL;
	FILE *stream_period=NULL;


	char buff[50];
    sprintf(buff,"%d",duty);
    printf("buff=%s \n",buff);
    int length=0;
    for(int m=0;(buff[m])!='\0';m++)
    {
    	 length++;
    }
    printf("length=%d \n",length);		
    stream_duty=fopen(PWM_File"pwm_test_P9_14.16/duty","r+");
    fwrite(buff,sizeof(char),length,stream_duty);
    fclose(stream_duty);

}
void SetPWM_P9_21(int period,int duty)
{
	

	FILE *stream_duty=NULL;
	FILE *stream_period=NULL;


	char buff[50];
    sprintf(buff,"%d",duty);
    printf("buff=%s \n",buff);
    int length=0;
    for(int m=0;(buff[m])!='\0';m++)
    {
    	 length++;
    }
    printf("length=%d \n",length);		
    stream_duty=fopen(PWM_File"pwm_test_P9_21.17/duty","r+");
    fwrite(buff,sizeof(char),length,stream_duty);
    fclose(stream_duty);

}
void SetPWM_P9_42(int period,int duty)
{
	

	FILE *stream_duty=NULL;
	FILE *stream_period=NULL;


	char buff[50];
    sprintf(buff,"%d",duty);
    printf("buff=%s \n",buff);
    int length=0;
    for(int m=0;(buff[m])!='\0';m++)
    {
    	 length++;
    }
    printf("length=%d \n",length);		
    stream_duty=fopen(PWM_File"pwm_test_P9_42.18/duty","r+");
    fwrite(buff,sizeof(char),length,stream_duty);
    fclose(stream_duty);

}


//		FILE *stream=NULL;
//		stream=fopen(Dev_Tree"slots","w");
//		fwrite("am33xx_pwm",sizeof(char),10,stream);
//		fclose(stream);
//		stream=fopen(Dev_Tree"slots","w");
//		fwrite("bone_pwm_P8_13",sizeof(char),14,stream);
//		fclose(stream);

