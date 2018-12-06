#ifndef SERVER_H
#define SERVER_H

int listenfd;

/*
 * Starts the server that will actively listen on the specified port.
 */
void init_server(int port);

/*
 * Return the message received from the server
 */
void *receive_msg(unsigned char* out_buff);

#endif
