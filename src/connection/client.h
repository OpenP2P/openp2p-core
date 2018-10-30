#ifndef CLIENT_H
#define CLIENT_H

/*
 * Structure for the client used for the current communications.
 */
typedef struct _client {
  char *dest_address;
  int dest_port;
  int socket;
} client;

/*
 * The client beign used.
 */
static client cli;

/*
 * Initialize the client.
 */
void init_client(char *d_address, int d_port);

/*
 * Send data through the client.
 */
void send_data(char *data);

/*
 * Close the client socket and resets the client structure.
 */
void destroy_client();

#endif
