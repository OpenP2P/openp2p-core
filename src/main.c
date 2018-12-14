#include <stdio.h>
#include <stdlib.h>
#include "overlay/overlay.h"

//dummy application
int main(int argc, char **argv) {
	const char *config_file = argv[1];
	init_overlay(config_file);
	
	return 0;
}
