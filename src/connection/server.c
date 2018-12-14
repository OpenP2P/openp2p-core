#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"

int listenfd;
int sockfd;

void init_server(int port) {
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	//AF_INET - IPv4 SOCK_STREAM - TCP
	//support more addresses and udp
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0
		|| listen(listenfd, SOMAXCONN) < 0) {
		if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
			printf("FATAL: Failed to bind the socket\n");
			exit(10);
		}
		if(listen(listenfd, SOMAXCONN) < 0) {
			printf("FATAL: Failed to listen the socket\n");
			exit(11);
		}
	}
}

void accept_conn() {
	sockfd = accept(listenfd, NULL, NULL);
}

int rcv_msg(int n, char *out_buff) {
	char buff[1024];
	memset(buff, '0', sizeof(buff));

	n = read(sockfd, buff, sizeof(buff));
	if(n == -1) {
		printf("ERROR: Error %d reading from socket in server rcv_msg\n", n);
		close(sockfd);
		return -1;
	} else if(n > 0) {
		buff[n] = 0;
		strcpy(out_buff, buff);
		return n;
	} else {
		strcpy(out_buff, "\0");
	}

	close(sockfd);
	return 0;
}

void destroy_server() {
	close(listenfd);
	close(sockfd);
}
