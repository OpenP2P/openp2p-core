all:
	gcc -Wall -pthread `pkg-config --cflags libconfig` \
	-o bin/main \
	src/main.c \
	src/overlay/overlay.c \
	src/overlay/topologies/mesh.c \
	src/connection/server.c \
	src/connection/client.c \
	`pkg-config --libs libconfig`
