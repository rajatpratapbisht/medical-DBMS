#include <array>
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>

#include "ClientSocket.h"
#include "ClientThread.h"
#include "ClientStub.h"
#include "ClientTimer.h"

int main(int argc, char *argv[])
{
	std::string ip;
	int port;

	int num_request;
	int request_type;
	int table;

	ClientTimer timer;

	std::vector<std::shared_ptr<ClientThreadClass>> client_vector;
	std::vector<std::thread> thread_vector;

	//-------------------READ RUN TIME ARGUMENTS ---------------------------------------------------------
	if (argc < 6)
	{
		std::cout << "not enough arguments" << std::endl;
		std::cout << "[USAGE]: " << argv[0] << "[ip] [port #] ";
		std::cout << "[# num_request] [table 1-h 2-d 3-p 4-plog ] [request type 1-read or 3-update]" << std::endl;
		return 0;
	}

	ip = argv[1];
	port = atoi(argv[2]);
	num_request = atoi(argv[3]);
	table = atoi(argv[4]);
	request_type = atoi(argv[5]);

	if (num_request < 1 || table < 1 || table > 4 || request_type > 4 || request_type < 1)
	{
		std::cout << "INVALID DATA passed in arguments\n";
		std::cout << "[USAGE]: " << argv[0] << "[ip] [port #] ";
		std::cout << "[# num_clients] [table 1-h 2-d 3-p 4-plog ] [request type 1-read or 3-update]" << std::endl;
		return 0;
	}

	ClientStub stub;

	timer.Start();
	for (int i = 1; i <= num_request; i++)
	{

		auto client_cls = std::shared_ptr<ClientThreadClass>(new ClientThreadClass());

		std::thread client_thread(&ClientThreadClass::ThreadBody, client_cls,
								  ip, port, i, request_type, table);

		client_vector.push_back(std::move(client_cls));
		thread_vector.push_back(std::move(client_thread));
	}
	for (auto &th : thread_vector)
	{
		th.join();
	}
	timer.End();

	for (auto &cls : client_vector)
	{
		timer.Merge(cls->GetTimer());
	}
	timer.PrintStats();

	return 1;
}
