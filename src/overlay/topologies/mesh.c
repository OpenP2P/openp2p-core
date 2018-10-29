#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include "mesh.h"
#include "../overlay.h"
#include "../../connection/message.h"

void init_topology(const char *cfg_file) {
	config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, cfg_file);

	setting = config_lookup(&cfg, "network_size");
	net_size = config_setting_get_int(setting);

	self.identifier = rand();
	self.conn_num = 0;
	self.conn = malloc(sizeof(mesh_node) * net_size);

	config_destroy(&cfg);
}

void join(char *address, int port) {
	message msg;
	msg.address = address;
	msg.port = port;
	send_message(JOIN, msg);
}
