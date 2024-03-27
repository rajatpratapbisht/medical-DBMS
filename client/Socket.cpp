#include "Socket.h"

#include <iostream>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/types.h>

//-------------------SOCKET TYPE CONSTRUCTOR
Socket::Socket() : is_initialized_(false), nagle_(NAGLE_ON) { }

//-------------------SOCKET TYPE DECONSTRUCTOR
Socket::~Socket() {
	if (is_initialized_) {
		Close();
	}
}

//------------------- SEND WRAPPER FUNCTION
int Socket::Send(char *buffer, int size, int flags) {
	int bytes_written = 0;
	int offset = 0;
	while (size > 0) {
		bytes_written = send(fd_, buffer + offset, size, flags);
		if (bytes_written < 0) {
			/*
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				perror("ERROR: send retry");
				continue;
			}
			*/
			perror("ERROR: failed to send");
			Close();
			return 0;
		}

		//-------------------SEND WON'T BE ABLE TO SEND ALL THE DATA IN ONE FULL SWEEP 
		size -= bytes_written;
		offset += bytes_written;
		assert(size >= 0);		//-------------------IF THE CONDITION FAILS THERE DEFINITELY AN ERROR OCCURED
	}
	return 1;
}

//------------------- RECEIVE WRAPPER FUNCTION
int Socket::Recv(char *buffer, int size, int flags) {
	int bytes_read = 0;
	int offset = 0;
	while (size > 0) {
		bytes_read = recv(fd_, buffer + offset, size, flags);
		if (bytes_read <= 0) {
			/*
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				//perror("ERROR: recv retry");
				continue;
			}
			*/
			//perror("ERROR: failed to recv");
			Close();
			return 0;
		}
		assert(bytes_read != 0);
		//------READ BUFFER SENT IN SMALLER SECTIONS
		size -= bytes_read;
		offset += bytes_read;
		assert(size >= 0);
	}
	return 1;
}

//------------------- NAGLE SET SWITCH FUNCTION
int Socket::NagleOn(bool on_off) {
	nagle_ = (on_off ? NAGLE_ON : NAGLE_OFF);
	int result = setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
				(void *) &nagle_, sizeof(int));
	if (result < 0) {
		perror("ERROR: setsockopt failed");
		return 0;
	}
	return 1;
}

//------------------- IF NAGLE IS ON
bool Socket::IsNagleOn() {
	return (nagle_ == NAGLE_ON) ? true : false;
}

//-------------------CLOSE ERROR EXIT SOCKET FD
void Socket::Close() {
	shutdown(fd_, SHUT_RDWR);
	close(fd_);
	//perror("Socket closed");
	is_initialized_ = false;
}






