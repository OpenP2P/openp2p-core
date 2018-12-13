#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "overlay.h"
#include "../connection/server.h"
#include "../connection/client.h"
#include "../connection/message.h"

void *srv_msg() {
  while(1) {
    accept_conn();
    char buff[1024];
    int n = 0;
    do {
      n = receive_msg(n, buff);
      printf("[NOTIFY] %s", buff);
    } while(n > 0);
  }
}

void init_overlay(const char *config_file) {
  config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, config_file);

	setting = config_lookup(&cfg, "self_port");
	int port = config_setting_get_int(setting);

	init_server(port);
  pthread_t srv_thread_id;
	pthread_create(&srv_thread_id, NULL, srv_msg, NULL);

  //TODO use this
  setting = config_lookup(&cfg, "overlay_topology");
	const char *topology = config_setting_get_string(setting);
  setting = config_lookup(&cfg, "overlay_topology_config");
	const char *topology_config = config_setting_get_string(setting);
  if(strcmp(topology, "mesh")) {
    #include "topologies/mesh.h"

    //TODO depend on topology
    init_topology(topology_config);

    setting = config_lookup(&cfg, "boot_address");
  	const char *boot_address = config_setting_get_string(setting);
    setting = config_lookup(&cfg, "boot_port");
  	int boot_port = config_setting_get_int(setting);

    join((char *)boot_address, boot_port);

    config_destroy(&cfg);
  }

	pthread_join(srv_thread_id, NULL);
}

void send_message(message_type type, message msg) {
  char *send = malloc(sizeof(msg.payload));
  init_client(msg.address, msg.port);
  sprintf(send, "%d%s\n", type, msg.payload);
  send_msg(send);
  destroy_client();
}
