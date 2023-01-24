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
#include "client_control_handler.h"

// Local routine for this file
static CCH_data_t *CCH_data_alloc(){
	CCH_data_t *p;
	p = malloc(sizeof(CCH_data_t));
	if (p == 0){
		printf("No memory.\n");
		return 0;
	};
	p->fd = 0;
	return p;
};

static void CCH_data_free(CCH_data_t *p){
	if (p == 0){
		return;
	};
	printf("Freeing data.\n");
	free(p);
};

static int CCH_bind(CCH_data_t* p, char* host, int port){
#define SA struct sockaddr
	struct sockaddr_in servaddr; //#define TCPIP AF_INET;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(host);
	servaddr.sin_port = htons(port);
	printf("Port = %d %x\n", port, port);
	printf("sin_port = %d %x\n", servaddr.sin_port, servaddr.sin_port);
	if (connect(p->fd, (SA*)&servaddr, sizeof(servaddr))
		!=0){
		printf("Connection with the server failed...\n");
		return -1;
	} else { 
		printf("Connected to the server. \n");
	};
	return 0;
};

//external access methods
int CCH_write(CCH_data_t* p, void* source, int size){
	int n = write(p->fd, source, size);
	if (n < size){
		printf("Cannot write all of size[%d] returned[%d]\n", size, n);
		return n;
	};
	return n;
};

int CCH_read(CCH_data_t* p, void* destination, int size){
	int n = read(p->fd, destination, size);
	if (n < size){
		printf("Cannot read all of size[%d], returned[%d]\n", size, n);
		return n;
	};
	return n;
};

void CCH_close(CCH_data_t* p){
	if (p == 0){
		return;
	};
	if (p->fd != 0){
		printf("Closing the socket at: [%d]\n",	p->fd);
		close(p->fd);
		p->fd = 0;
	};
	CCH_data_free(p);
	return; 
};

CCH_data_t* CCH_create(char* host, int port){
	CCH_data_t *p;
	p = CCH_data_alloc();
	p->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (p->fd == -1){
		printf("Socket creation failed...\n");
		CCH_data_free(p);
		return 0;
	} else {
		printf("Socket successfully created!\n");
	};
	int b = CCH_bind(p, host, port);
	if (b < 0){
		printf("Fail to bind host:[%s], port:[%d].\n", host, port);
		CCH_close(p);
		return 0;
	};
	return p;
};

CCH_data_t* CCH_accept(int port){
	CCH_data_t* p;
	p = CCH_data_alloc();
	int sockfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
	int value = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(void *)&value, sizeof(value))){
    	printf("Can't set SO_REUSEADDR (%d) - %d", errno, sockfd);
        close(sockfd);
        exit(0);
	}

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...(%d)\n", errno);
        perror("Bind fail");
        exit(0);
    }
    else
        printf("Socket successfully binded to port:[%d]\n", port);

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
	p->fd = sockfd;
    return p;
};

