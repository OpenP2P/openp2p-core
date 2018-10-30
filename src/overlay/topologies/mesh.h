#ifndef MESH_H
#define MESH_H

/*
 * Structure of a node in the mesh overlay.
 */
typedef struct _mesh_node {
  int id;
  char *address;
  int port;
} mesh_node;

/*
 * Identifier of this node.
 */
static int id;

/*
 * Pointer to all the connections made with this node.
 * The network size must be specified in the mesh config file.
 */
static mesh_node *conn;

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

#endif
