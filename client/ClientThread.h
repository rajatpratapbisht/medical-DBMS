#ifndef __CLIENT_THREAD_H__
#define __CLIENT_THREAD_H__

#include <chrono>
#include <ctime>
#include <string>

#include "ClientStub.h"
#include "ClientTimer.h"

class ClientThreadClass
{
private:
    int table;              //---- 1-hospital, 2-doctor, 3-patient, 4-pat_log
    int condition =  1;     //---- 1-id, 2-address
    int type;               //---- 1-read, 2-insert, 3-update, 4-delete
    int condition_data;
    int requester;          //---- 1-hospital, 2-doctor, 3-patient

    ClientStub stub;

    ClientTimer timer;

public:
    ClientThreadClass();
    void ThreadBody(std::string ip, int port, int id, int request_type, int req_table);
    
    ClientTimer GetTimer();

};



#endif // end of #ifndef __CLIENT_THREAD_H__