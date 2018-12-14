#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include <time.h>
#include "topology.h"
#include "mesh.h"
#include "../overlay.h"

static unsigned int id;
static node *conn;

void message_receiver(char *msg) {
	printf("receiver: %s\n", msg);
}

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

	printf("INFO: Mesh topology initialized\n");
	printf("INFO: Node ID = %d\n", id);
}

void join(char *address, int port) {
	message msg;
	msg.address = address;
	msg.port = port;
	msg.payload = malloc(sizeof(id)+4);
	sprintf(msg.payload, "%d", id);

	overlay_send_message(JOIN, msg);
}
