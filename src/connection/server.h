#ifndef SERVER_H
#define SERVER_H

/*
 * Starts the server that will actively listen on the specified port.
 */
void init_server(int port);

/*
 * Accept connections from the listening socket.
 */
void accept_conn();

/*
 * Receive messages from the listening socket.
 */
int rcv_msg(int n, char *out_buff);

/*
 * Close the listening socket.
 */
void destroy_client();

#endif
