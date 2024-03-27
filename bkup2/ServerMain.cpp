#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "ServerSocket.h"
#include "ServerPeerSocket.h"

#include "ServerThread.h"

#include "ServerPeers.h"
#include "ServerStub.h"
#include "ServerPeersStub.h"

#include "Messages.h"
#include "ServerDB.h"
#include <memory>
#include <map>
#include <cstring>

#include <fstream>

int main(int argc, char *argv[])
{
	int port = 2474;
	char IP1[16] = "127.0.0.1";
	char IP2[16] = "127.0.0.2";
	char IP3[16] = "127.0.0.3";

	std::map<int, Peers_t> serverPeers;

	Peers mainServer;
	Peers backup1;
	Peers backup2;

	mainServer.SetPeerData(1, 2474, IP1);
	backup1.SetPeerData(2, 2474, IP2 );
	backup2.SetPeerData(3, 2474, IP3);


	serverPeers.insert(std::pair<int, Peers_t>(1, mainServer));
	serverPeers.insert(std::pair<int, Peers_t>(2, backup1));
	serverPeers.insert(std::pair<int, Peers_t>(3, backup2));
	
	int my_uid;
	int req_count = 0;
	int num_experts = 1;

	ServerSocket socket;
	PeerSocket peer_socket;

	MedicalSystem medSys;


	std::unique_ptr<ServerSocket> new_socket;

	std::vector<std::thread> thread_vector;

	//-------------------READ RUN TIME ARGUMENTS ---------------------------------------------------------
	if (argc < 2)
	{
		std::cout << "not enough arguments" << std::endl;
		std::cout << argv[0] << "[my_uid #]" << std::endl;
		return 0;
	}

	my_uid = atoi(argv[1]);

	switch (my_uid)
	{
	case 1: // main server
			//-------------------INITIALISE ServerSocket TYPE SOCKET COMMUNICATION FOR SERVER END---------------------------------------------------
		if (!socket.Init(port, IP1))
		{
			std::cout << "Socket initialization failed" << std::endl;
			return 0;
		}

		break;

	case 2: // replica 1
			//-------------------INITIALISE ServerSocket TYPE SOCKET COMMUNICATION FOR SERVER END---------------------------------------------------
		if (!socket.Init(port, IP2))
		{
			std::cout << "Socket initialization failed" << std::endl;
			return 0;
		}
		break;

	case 3: // replica 2
			//-------------------INITIALISE ServerSocket TYPE SOCKET COMMUNICATION FOR SERVER END---------------------------------------------------
		if (!socket.Init(port, IP3))
		{
			std::cout << "Socket initialization failed" << std::endl;
			return 0;
		}
		break;

	default:
		return 0;
	}


	//-------------------CREATE EXPERT TYPE THREADS WITH ADMIN PRIVELAGES---------------------------------------------
	for (int i = 0; i < num_experts; i++)
	{
		std::thread dbms_thread(&MedicalSystem::DBMS_thread,
								&medSys, req_count++);
		thread_vector.push_back(std::move(dbms_thread));
	}

	while ((new_socket = socket.Accept()))
	{
		std::thread read_thread(&MedicalSystem::MainFrame, &medSys, std::move(new_socket), req_count++, my_uid, 
							serverPeers.at(2).GetPort(), IP2, 
							serverPeers.at(3).GetPort(), IP3);
		thread_vector.push_back(std::move(read_thread));
	}
	return 0;
}
