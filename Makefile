all:
	mkdir -p bin
	gcc -Wall -pthread `pkg-config --cflags libconfig` \
	-o bin/main \
	src/main.c \
	src/connection/client.c \
	src/connection/server.c \
	src/overlay/overlay.c \
	src/overlay/topologies/mesh.c \
	`pkg-config --libs libconfig`
