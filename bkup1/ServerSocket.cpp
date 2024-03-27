#include <iostream>

#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/types.h>

#include "ServerSocket.h"

//-------------------CONSTRUCTOR TO PRESET VALUES
ServerSocket::ServerSocket(int fd, bool nagle_on) {
	fd_ = fd;
	is_initialized_ = true;
	NagleOn(nagle_on);
}

//------------------- INITIALIZE COMMUNICATION OVER TCP
bool ServerSocket::Init(int port, char * IP_ADDRESS) {
	if (is_initialized_) {
		return true;
	}

	struct sockaddr_in addr;
	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ < 0) {
		perror("ERROR: failed to create a socket");
		return false;
	}

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	// addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	addr.sin_port = htons(port);

	if ((bind(fd_, (struct sockaddr *) &addr, sizeof(addr))) < 0) {
		perror("ERROR: failed to bind");
		return false;
	}

	listen(fd_, 8); 	//listen to fd_ with a backlog of queue(size = 8) of pending connection 

	is_initialized_ = true;
	return true;
}

//------------------- accept request is a list of various open connections with diff IDs
std::unique_ptr<ServerSocket> ServerSocket::Accept() {
	int accepted_fd;
	struct sockaddr_in addr;
	unsigned int addr_size = sizeof(addr);
	accepted_fd = accept(fd_, (struct sockaddr *) &addr, &addr_size);
	if (accepted_fd < 0) {
		perror("ERROR: failed to accept connection");
		return nullptr;
	}

	return std::unique_ptr<ServerSocket>(new ServerSocket(accepted_fd, IsNagleOn()));
}
//##################################################################################################