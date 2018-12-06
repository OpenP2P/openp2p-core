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
 * Identifier of this node.
 */
static int id;

/*
 * Pointer to all the connections made with this node.
 * The network size must be specified in the config file.
 */
static node *conn;

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

//TODO route, leave

#endif
