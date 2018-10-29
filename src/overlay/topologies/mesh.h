#ifndef MESH_H
#define MESH_H

typedef struct _mesh_node {
  int identifier;
  int conn_num;
  struct _mesh_node *conn;
} mesh_node;

static int net_size;
static mesh_node self;

void init_topology(const char *cfg_file);

void join(char *address, int port);

#endif
