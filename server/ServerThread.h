#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include "ServerSocket.h"
#include <map>
#include "Messages.h"
#include "ServerDB.h"

//-------------------EXPERT THREAD DATA TYPE OPERATION---------------------------------
struct DBMS_update
{
    Acknowledgement acknow;
    RequestData request;
    // PatLog_DB pl_db;
    std::promise<Acknowledgement> prom;
};

class MedicalSystem
{
private:
    //-------------------EXPERT THREAD REQUIRES ,
    std::queue<std::unique_ptr<DBMS_update>> dbms_rq; //---------REQ_QUEUE
    std::mutex dbms_rq_lock;                        //------MUTEX LOCK and
    std::condition_variable dbms_rq_cv;

    Hospitals_t CreateHospData(RequestData req);
    Doctors_t CreateDocData(RequestData req);
    Patients_t CreatePatData(RequestData req);
    Patient_Log_t CreatePatLogData(RequestData req);
    Acknowledgement_t UpdatePatLog(RequestData req);

public:
    void MainFrame(std::unique_ptr<ServerSocket> socket, int id, int my_uid, int bk1_port, char * bk1_ip, int bk2_port, char *bk2_ip);   //--------main req handler
    void DBMS_thread(int id);                                       //--------DBMS THREAD OPERATION
};
#endif // end of #ifndef __SERVERTHREAD_H__