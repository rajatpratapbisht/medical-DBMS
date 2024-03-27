#ifndef __SERVER_STUB_H__
#define __SERVER_STUB_H__

#include <memory>

#include "ServerSocket.h"
#include "Messages.h"
#include<iostream>
class ServerStub {
private:
	std::unique_ptr<ServerSocket> socket;
public:
	ServerStub();
	void Init(std::unique_ptr<ServerSocket> socket);
	// LaptopOrder ReceiveOrder();
	RequestData ReceiveRequest();
	
	// int SendLaptop(LaptopInfo info);
	int SendHospData(Hospitals hosp);
	int SendDocData(Doctors doc);
	int SendPatData(Patients pat);
	int SendPatLogData(Patient_Log pat_log);
	int SendAck(Acknowledgement ack);
};

#endif // end of #ifndef __SERVER_STUB_H__
