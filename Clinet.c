
/*

* File:   Client.c

* Author: root

*

* Created on 2019/07/08 20:19

*/



#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <string.h>

#include <errno.h>

#include <netinet/in.h>

#include <arpa/inet.h>



//#define SERVERIP "192.168.0.23"
#define SERVERIP "localhost"

#define SERVERPORT 12345

#define MAXBUFFER 256



int main(int argc, char** argv)

{

	int clientFd, ret;

	struct sockaddr_in serveraddr;

	char buf[MAXBUFFER];

	clientFd = socket(AF_INET, SOCK_STREAM, 0);//����socket

	if (clientFd < 0)

	{

		printf("socket error:%s\n", strerror(errno));

		exit(-1);

	}

	bzero(&serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;

	serveraddr.sin_port = htons(SERVERPORT);

	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);

	ret = connect(clientFd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));//���ӵ�������

	if (ret != 0)

	{

		close(clientFd);

		printf("connect error:%s\n", strerror(errno));

		exit(-1);

	}

	while (1)

	{

		bzero(buf, sizeof(buf));

		scanf("%s", buf);

		write(clientFd, buf, sizeof(buf));//д����

		bzero(buf, sizeof(buf));

		read(clientFd, buf, sizeof(buf));//������

		printf("echo:%s\n", buf);

	}

	close(clientFd);

	return (EXIT_SUCCESS);

}