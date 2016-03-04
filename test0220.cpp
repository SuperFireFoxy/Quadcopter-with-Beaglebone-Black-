/* File Name: server.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <string>
#include "MPU6050.h"
#include "BBB_I2C.h"
#include "BBB_MPU6050.h"
#include "BBB_PWM.h"
#include "socketCommunication.h"
#include <pthread.h>

using namespace std;
#define DEFAULT_PORT 3526
#define MAXLINE 4096

pthread_t commthreadID;
void * comm_thread_join_status;



int main()
{	
	
	
    
 //   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED); 
	Open_PWM();    
    
	
    pthread_attr_t attr = {0};
	pthread_attr_init (&attr);
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM); 
	sched_param param;
	param.sched_priority=90;
	//pthread_attr_setschedparam(&attr, &param);
	int threadRet=pthread_create(&commthreadID,&attr,socketCommunicate,NULL);
	pthread_setschedparam(commthreadID,SCHED_FIFO,&param);
	if(threadRet)
		{
			printf("Create communication thread error!");
			return 1;		
		}
	
	
	
    
	pthread_join(commthreadID,&comm_thread_join_status);
}

