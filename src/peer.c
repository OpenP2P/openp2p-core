#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void receiveMsg(int sockfd) {
	char buff[1024];
	memset(buff, '0', sizeof(buff));

	int n= 0;
	while((n = read(sockfd, buff, sizeof(buff))) > 0) {
		buff[n] = 0;
		fputs(buff, stdout);
		printf("\n");
	}
}

void sendMsg(int sockfd) {
	char buff[1024];
	memset(buff, '0', sizeof(buff));

	scanf("%s", buff);
	write(sockfd, buff, strlen(buff));
}

void *server(void *port) {
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(*(int *)port);

	//AF_INET - IPv4 SOCK_STREAM - TCP
	//support more addresses and udp
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0
		|| listen(listenfd, 10) < 0) {
		printf("Failed to init node!\n");
		exit(-1);
	}

	//TODO multiple clients
	int connfd = accept(listenfd, NULL, NULL);

	while(1) {
		receiveMsg(connfd);
	}

	close(connfd);
}

void *client(void *port) {
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(*(int *)port);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//TODO change
	while(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
		sleep(1);
	}

	while(1) {
		sendMsg(sockfd);
	}

	close(sockfd);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: peer srv_port cli_port");
		return -1;
	}

	int srv_port = atoi(argv[1]), cli_port = atoi(argv[2]);
	pthread_t srv_thread_id, cli_thread_id;

	//TODO use only one thread!?
	pthread_create(&srv_thread_id, NULL, server, (void *)&srv_port);
	pthread_create(&cli_thread_id, NULL, client, (void *)&cli_port);

	pthread_join(srv_thread_id, NULL);
	pthread_join(cli_thread_id, NULL);

	return 0;
}
