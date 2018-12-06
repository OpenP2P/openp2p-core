#ifndef OVERLAY_H
#define OVERLAY_H

#include "../connection/message.h"

/*
 * Topologies available
 */
typedef enum _topologies {
  MESH = 0,
  CHORD = 1,
  KADEMLIA = 2,
  PASTRY = 3
} topologies;

/*
 * Initialize the overlay.
 */
void init_overlay(const char *config_file);

/*
 * Recieve notifications from the communication layer and send it to the topology layer.
 */
void notify(unsigned char *data);

/*
 * Send message trough the communication layer.
 */
void send_message(message_type type, message msg);

#endif
