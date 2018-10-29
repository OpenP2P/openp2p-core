#ifndef OVERLAY_H
#define OVERLAY_H

#include "../connection/message.h"

static int self_port;
static const char *topology;

void init_overlay(const char *config_file);

void notify(unsigned char *data);

void send_message(message_type type, message msg);

#endif
