#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "../../connection/message.h"

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
 * Message receiver and pre-processor.
 */
void message_receiver(char *msg);

/*
 * Message processor.
 */
void message_processor(message_type type, message msg);

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
