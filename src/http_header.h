#ifndef __HEADER__
#define __HEADER__

#define _XOPEN_SOURCE 700
#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

//#define EXIT_SUCCESS 1

int socket_setting(const char* hostname); 
int download_html(const char* hostname, int socket);

#endif
