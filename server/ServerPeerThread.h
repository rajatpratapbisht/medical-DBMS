#ifndef _SERVER_PEER_THREAD_H__
#define _SERVER_PEER_THREAD_H__


#include <chrono>
#include <ctime>
#include <string>

#include "ServerPeersStub.h"
#include "ServerPeerTimer.h"

class PeerThreadClass
{
private:
    int table;              //---- 1-hospital, 2-doctor, 3-patient, 4-pat_log
    int condition =  1;     //---- 1-id, 2-address
    int type;               //---- 1-read, 2-insert, 3-update, 4-delete
    int condition_data;
    int requester;          //---- 1-hospital, 2-doctor, 3-patient

    PeerStub stub;

    ClientTimer timer;

public:
    PeerThreadClass();
    void PeerThreadBody(std::string ip, int port, int id, int request_type, int req_table);
    
    ClientTimer GetTimer();

};

#endif