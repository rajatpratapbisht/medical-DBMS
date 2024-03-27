#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>

#include "ClientSocket.h"
#include "Messages.h"

class ClientStub {
private:
	ClientSocket socket;
public:
	ClientStub();
	int Init(std::string ip, int port);
	Hospitals_t RequestHospital(RequestData request);
	Doctors_t RequestDoctor(RequestData request);
	Patients_t RequestPatent(RequestData request);
	Patient_Log_t RequestPatientLog(RequestData request);
	Acknowledgement_t UpdatePatientLog(RequestData request);
};


#endif // end of #ifndef __CLIENT_STUB_H__
