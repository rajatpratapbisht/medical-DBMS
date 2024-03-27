#ifndef __SERVER_PEERS_STUB_H__
#define __SERVER_PEERS_STUB_H__

#include <string>

#include "ServerPeerSocket.h"
#include "Messages.h"

class PeerStub {
private:
	PeerSocket socket;
public:
	PeerStub();
	int Init(std::string ip, int port);
	
    Hospitals_t RequestHospital(RequestData request);
	
    Doctors_t RequestDoctor(RequestData request);
	
    Patients_t RequestPatent(RequestData request);
	
    Patient_Log_t RequestPatientLog(RequestData request);
	
    Acknowledgement_t UpdatePatientLog(RequestData request);
};


#endif // end of #ifndef __SERVER_PEERS_STUB_H__
