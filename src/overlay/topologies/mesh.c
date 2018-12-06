#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include <time.h>
#include "topology.h"
#include "mesh.h"
#include "../overlay.h"
#include "../../connection/message.h"

void init_topology(const char *cfg_file) {
	config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, cfg_file);

	setting = config_lookup(&cfg, "network_size");
	int net_size = config_setting_get_int(setting);

	srand(time(NULL));
	id = rand();
	conn = malloc(sizeof(node) * net_size);

	config_destroy(&cfg);
}

void join(char *address, int port) {
	message msg;
	msg.address = address;
	msg.port = port;
	msg.payload = malloc(sizeof(id));
	//replacement to itoa()
	sprintf(msg.payload, "%d", id);

	send_message(JOIN, msg);
}
