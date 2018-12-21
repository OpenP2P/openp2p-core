#ifndef MESSAGE_H
#define MESSAGE_H

/*
 * Message types.
 */
typedef enum _message_type {
  JOIN = 0,
  LEAVE = 1,
  REDIRECT = 2
} message_type;

/*
 * Structure of a message.
 */
typedef struct _message {
  char *address;
  int port;
  char *payload;
  size_t payload_size;
} message;

#endif
