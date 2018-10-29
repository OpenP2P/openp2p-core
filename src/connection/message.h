#ifndef MESSAGE_H
#define MESSAGE_H

typedef enum _message_type {
  JOIN = 0,
  LEAVE = 1,
  REDIRECT = 2
} message_type;

typedef struct _message {
  char *address;
  int port;
  char *payload;
} message;

#endif
