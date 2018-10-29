#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"
#include "../overlay/overlay.h"

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
		printf("Failed to init server!\n");
		exit(-1);
	}

	while(1) {
		int sockfd = accept(listenfd, NULL, NULL);

    unsigned char buff[1024];
  	memset(buff, '0', sizeof(buff));

  	int n= 0;
  	while((n = read(sockfd, buff, sizeof(buff))) > 0) {
  		buff[n] = 0;
      notify(buff);
  	}

		close(sockfd);
	}
}
