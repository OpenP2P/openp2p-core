#ifndef OVERLAY_H
#define OVERLAY_H

#include "../connection/message.h"

/*
 * Initialize the overlay.
 */
void init_overlay(const char *config_file);

/*
 * Recieve notifications from the communication layer and send it to the topology layer.
 */
void overlay_notify(unsigned char *data);

/*
 * Send message API function.
 */
void overlay_send_message(message_type type, message msg);

#endif
