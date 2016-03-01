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
#include <pthread.h>

using namespace std;
#define DEFAULT_PORT 3526
#define MAXLINE 4096


int main(int argc, char** argv)
{
    int    socket_fd, connect_fd;
    struct sockaddr_in     servaddr;
    char    buff[4096];
    int     n;
	
	Open_PWM();    

    //开启UART4
    //system("echo BB-UART4 > /sys/devices/bone_capemgr.9/slots");
	//����MPU6050��ȡ�߳�
	pthread_t threadID;
	int threadRet=pthread_create(&threadID,NULL,BBB_MPU6050,NULL);
	if(threadRet)
		{
			printf("Create thread error!");
			return 1;		
		}

    //初始化Socket
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //初始化
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT

    //将本地地址绑定到所创建的套接字上
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //开始监听是否有客户端连接
    if( listen(socket_fd, 10) == -1){
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    printf("======waiting for client's request======\n");
    while(1){
//阻塞直到有客户端连接，不然多浪费CPU资源。
        if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
        {
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        return 0;
        }
        else{
        	n = recv(connect_fd, buff, MAXLINE, 0);
        	buff[n]='\0';
			int ret;
			ret=strcmp(buff,"unlock_speeder");
			printf("%d",ret);
			if(!strcmp(buff,"unlock_speeder"))
			{
				
				
				sleep(1);
				system("echo 19000000 > /sys/devices/ocp.3/pwm_test_P8_13.15/duty");
				system("echo 19000000 > /sys/devices/ocp.3/pwm_test_P9_14.16/duty");
				system("echo 19000000 > /sys/devices/ocp.3/pwm_test_P9_21.17/duty");
				system("echo 19000000 > /sys/devices/ocp.3/pwm_test_P9_42.18/duty");
				close(connect_fd);
				continue;
			}
			if(!strcmp(buff,"keep_up"))
				{
					close(connect_fd);
					continue;
				}
			else{
				printf("recv msg from client: %s\n", buff);
        		int duty=atoi(buff);
				SetPWM_P9_14(0,duty);
      			SetPWM_P8_13(0,duty);			    
				SetPWM_P9_21(0,duty);
				SetPWM_P9_42(0,duty);
        		close(connect_fd);
			}
        	
        }
    }
	//pthread_join(threadID,NULL);
}

