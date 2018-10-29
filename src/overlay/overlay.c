#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include <unistd.h>
#include "overlay.h"
#include "mesh/mesh.h"
#include "../connection/server.h"
#include "../connection/client.h"

void notify(unsigned char *data) {
  printf("%s", data);
}

//use getopt for flags
//change to init function
int main() {

  port = 5000;

	pthread_t srv_thread_id;
	pthread_create(&srv_thread_id, NULL, server, (void *)&port);

  init_client("127.0.0.1", port);

  send_message("test test\n");
  send_message("test test\n");

  destroy_client();

	pthread_join(srv_thread_id, NULL);

	return 0;
}
