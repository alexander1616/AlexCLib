#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#include "eventhandler.c"


