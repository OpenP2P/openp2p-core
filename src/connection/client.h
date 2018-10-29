#ifndef CLIENT_H
#define CLIENT_H

typedef struct _client {
  char  *dest_address;
  int   dest_port;
  int   socket;
} client;

static client cli;

void init_client(char *d_address, int d_port);

void send_data(char *data);

void destroy_client();

#endif
