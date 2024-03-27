#include "ServerPeersStub.h"
#include <stdio.h>
#include<cstring>


PeerStub::PeerStub() {}

int PeerStub::Init(std::string ip, int port)
{
	return socket.Init(ip, port);
}

Hospitals_t PeerStub::RequestHospital(RequestData request)
{
	Hospitals hosp;

	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0))
	{
		size = hosp.Size();

		if (socket.Recv(buffer, size, 0))
		{
			hosp.Unmarshal(buffer);
		}
	}
	return hosp;
}
///////////////////////////
Doctors_t PeerStub::RequestDoctor(RequestData request)
{
	Doctors doc;

	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0))
	{
		size = doc.Size();

		if (socket.Recv(buffer, size, 0))
		{
			doc.Unmarshal(buffer);
		}
	}
	return doc;
}
///////////////////////////
Patients_t PeerStub::RequestPatent(RequestData request)
{
	Patients patient;

	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0))
	{
		size = patient.Size();

		if (socket.Recv(buffer, size, 0))
		{
			patient.Unmarshal(buffer);
		}
	}
	return patient;
}
///////////////////////////
Patient_Log_t PeerStub::RequestPatientLog(RequestData request)
{
	Patient_Log patient_log;

	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0))
	{
		size = patient_log.Size();

		if (socket.Recv(buffer, size, 0))
		{
			patient_log.Unmarshal(buffer);
		}
	}
	return patient_log;
}
////////////////////////////////
Acknowledgement_t PeerStub::UpdatePatientLog(RequestData request)
{
	Acknowledgement ack;

	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0))
	{
		size = ack.Size();
		if (socket.Recv(buffer, size, 0))
		{
			ack.Unmarshal(buffer);
		}
	}
	return ack;
}
