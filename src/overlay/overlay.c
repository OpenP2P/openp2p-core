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

/*
 * Topologies available
 */
char *topologies_avail[3] = {
  "mesh",
  "chord",
  "kademlia"
};

void *srv_msg() {
  while(1) {
    accept_conn();
    char buff[1024];
    int n = 0;
    do {
      n = rcv_msg(n, buff);
      //TODO properly receive messages
      printf("[NOTIFY] %s", buff);
    } while(n > 0);
  }
}

void overlay_send_message(message_type type, message msg) {
  char *send = malloc(sizeof(msg.payload));
  init_client(msg.address, msg.port);
  sprintf(send, "%d%s\n", type, msg.payload);
  send_msg(send);
  destroy_client();
}

void init_overlay(const char *config_file) {
  printf("INFO: Overlay network initialized\n");
  config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, config_file);

	setting = config_lookup(&cfg, "self_port");
	int port = config_setting_get_int(setting);

	init_server(port);
  pthread_t srv_thread_id;
	pthread_create(&srv_thread_id, NULL, srv_msg, NULL);

  setting = config_lookup(&cfg, "overlay_topology");
	const char *topology = config_setting_get_string(setting);
  setting = config_lookup(&cfg, "overlay_topology_config");
	const char *topology_config = config_setting_get_string(setting);

  // Check if the topology is available
  int topologies_avail_size = sizeof(topologies_avail) / sizeof(char *);
  for (int i = 0; i <  topologies_avail_size; i++) {
    char topo_file[25 + strlen(topologies_avail[i])];
    sprintf(topo_file, "src/overlay/topologies/%s.h", topology);
    if(strcmp(topology, topologies_avail[i]) == 0
      && access(topo_file, F_OK) != -1)
      break;
    else if(i == (sizeof(topologies_avail_size) - 1)) {
      printf("FATAL: overlay_topology %s is not availabe.\n", topology);
      exit(20);
    }
  }

  // Dynamically choose the include header file
  #define TOPOLOGY topology
  #define __topology_header(x) #x
  #define _topology_header(x) __topology_header(x)
  #define topology_header(x) _topology_header(topologies/x.h)
  #include topology_header(TOPOLOGY)

  init_topology(topology_config);

  setting = config_lookup(&cfg, "boot_address");
  const char *boot_address = config_setting_get_string(setting);
  setting = config_lookup(&cfg, "boot_port");
  int boot_port = config_setting_get_int(setting);
  printf("INFO: Bootstrap node = %s:%d\n", boot_address, boot_port);

  join((char *)boot_address, boot_port);

  config_destroy(&cfg);

	pthread_join(srv_thread_id, NULL);
}
