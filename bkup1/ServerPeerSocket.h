#ifndef __PEERSOCKET_H__
#define __PEERSOCKET_H__

#include <string>

#include "Socket.h"


class PeerSocket: public Socket {
public:
	PeerSocket() {}
	~PeerSocket() {}

	int Init(std::string ip, int port);
};


#endif // end of #ifndef __PEERSOCKET_H__
