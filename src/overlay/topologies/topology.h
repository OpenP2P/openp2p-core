#ifndef TOPOLOGY_H
#define TOPOLOGY_H

/*
 * Structure of a node in the overlay.
 */
typedef struct _node {
  int id;
  char *address;
  int port;
} node;

/*
 * Initialize the topology.
 */
void init_topology(const char *cfg_file);

/*
 * Notify the topology of new messages from other nodes.
 */
void notify_topology(unsigned char *data);

/*
 * Send join message when the node joins the network.
 */
void join(char *address, int port);

//TODO avoid warning
node return_self();
//TODO route, leave

#endif
