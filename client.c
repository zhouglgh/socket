#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  

#define PORT 8000
#define bytes_per_time 64
#define GB 1024*1024*1024

struct datas {
    int sock_fd;
    int connect_fd;
    struct sockaddr_in saddr;

};

void send_packets(struct datas *robot, unsigned int packets);
int main(int argc, char* argv[])
{  
	if( argc != 3){  
		printf("usage: ./client <ipaddress> <packetnumbers>\n");  
		exit(0);  
	}  

    unsigned int packets = atoi(argv[3]);
    struct datas *robot = (struct datas*)malloc(sizeof(struct datas));

    /**
     * 创建新的socket.
     */
	if( (robot->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
		exit(0);  
	}  
    /**
     * 服务器地址。
     */
	memset(&robot->saddr, 0, sizeof(struct sockaddr_in));  
	robot->saddr.sin_family = AF_INET;  
	robot->saddr.sin_port = htons(PORT);  
	if( inet_pton(AF_INET, argv[1], &robot->saddr.sin_addr) <= 0){  
		printf("inet_pton error for %s\n",argv[1]);  
		exit(0);  
	}  


    /**
     * 连接服务器。
     */
	if( connect(robot->sock_fd, (struct sockaddr*)&robot->saddr, sizeof(robot->saddr)) < 0){  
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
		exit(0);  
	}  

    /**
     * 发送数据
     */
    send_packets(robot,packets);
	close(robot->sock_fd);  
    free(robot);
    robot=0;
    return 0;
} 

void send_packets(struct datas *robot, unsigned int packets)
{
    char  *data = malloc(bytes_per_time);;
    memset(data,'a',bytes_per_time);
    while(1)
    {
        if( send(robot->sock_fd, data, bytes_per_time, 0) < 0)  
        {  
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
            exit(0);  
        }  
    }
    free(data);
    data=0;
}
