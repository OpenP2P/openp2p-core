#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <pthread.h>
#include "mesh.h"
//#include "overlay.h"
#include "../../connection/server.h"


//use getopt for flags
//change to init function
int main() {
	static const char *input_file = "config/overlay/mesh/mesh.cfg";
	config_t cfg;
	config_setting_t *setting;

	config_init(&cfg);
	config_read_file(&cfg, input_file);

	setting = config_lookup(&cfg, "network_size");
	net_size = config_setting_get_int(setting);

	config_destroy(&cfg);

	return 0;
}
