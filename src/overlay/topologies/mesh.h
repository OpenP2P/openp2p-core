#ifndef MESH_H
#define MESH_H

typedef struct _mesh_node {
  int id;
  char *address;
  int port;
} mesh_node;

static int id;
static mesh_node *conn;

void init_topology(const char *cfg_file);

void notify_topology(unsigned char *data);

void join(char *address, int port);

#endif
