all:
	gcc -pthread `pkg-config --cflags libconfig` \
	-o bin/overlay \
	src/overlay/overlay.c \
	src/connection/server.c \
	src/connection/client.c \
	`pkg-config --libs libconfig`
