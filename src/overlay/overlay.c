#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include <unistd.h>
#include "overlay.h"
#include "topologies/mesh.h"
#include "../connection/server.h"
#include "../connection/client.h"
#include "../connection/message.h"

void init_overlay(const char *config_file) {
  config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, config_file);

	setting = config_lookup(&cfg, "self_port");
	self_port = config_setting_get_int(setting);

	pthread_t srv_thread_id;
	pthread_create(&srv_thread_id, NULL, server, (void *)&self_port);

  //TODO use this
  setting = config_lookup(&cfg, "overlay_topology");
	topology = config_setting_get_string(setting);
  setting = config_lookup(&cfg, "overlay_topology_config");
	const char *topology_config = config_setting_get_string(setting);

  //TODO depend on topology
  init_topology(topology_config);

  setting = config_lookup(&cfg, "boot_address");
	const char *boot_address = config_setting_get_string(setting);
  setting = config_lookup(&cfg, "boot_port");
	int boot_port = config_setting_get_int(setting);

  join((char *)boot_address, boot_port);

  config_destroy(&cfg);

	pthread_join(srv_thread_id, NULL);
}

void notify(unsigned char *data) {
  printf("[NOTIFY] %s", data);
}

void send_message(message_type type, message msg) {
  char *addr = msg.address;
  int port = msg.port;
  init_client(addr, port);
  send_data("[JOIN]\n");
  destroy_client();
}
