#include "ServerStub.h"
#include <stdio.h>
#include<cstring>
#include <arpa/inet.h>

ServerStub::ServerStub() {}

//------------------- INITIALIZE STUB FOR SOCKET COMMUNICATION
void ServerStub::Init(std::unique_ptr<ServerSocket> socket)
{
	this->socket = std::move(socket);
}
//------------------- RECEIVE DATA FROM SOCKET IS CONVERTED TO PROGRAM UNDERSTANDABLE TYPE

RequestData ServerStub::ReceiveRequest()
{
	char buffer[64];
	RequestData req;
	if (socket->Recv(buffer, req.Size(), 0))
	{
		req.Unmarshal(buffer);
	}
	return req;
}
//------------------- SEND THE PROGRAM UNDERSTANDABLE DATATYPE TO SOCKET STREAM TYPE DATA

int ServerStub::SendHospData(Hospitals hosp)
{
	char buffer[32];
	hosp.Marshal(buffer);
	return socket->Send(buffer, hosp.Size(), 0);
}

int ServerStub::SendDocData(Doctors doc)
{
	char buffer[32];
	doc.Marshal(buffer);
	return socket->Send(buffer, doc.Size(), 0);
}

int ServerStub::SendPatData(Patients pat)
{
	char buffer[32];
	pat.Marshal(buffer);
	return socket->Send(buffer, pat.Size(), 0);
}

int ServerStub::SendPatLogData(Patient_Log pat_log)
{
	char buffer[32];
	pat_log.Marshal(buffer);
	//printf("%s\n", buffer);
	return socket->Send(buffer, pat_log.Size(), 0);
}

int ServerStub::SendAck(Acknowledgement ack){
	
	char buffer[32];
	ack.Marshal(buffer);
	return socket->Send(buffer, ack.Size(), 0);
}