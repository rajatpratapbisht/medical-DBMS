#include <iostream>
#include <memory>

#include "ServerThread.h"
#include "ServerStub.h"
#include "ServerPeersStub.h"
#include "ServerPeers.h"

std::map<int, Hospitals_t> hosp_map;
std::map<int, Doctors_t> doc_map;
std::map<int, Patients_t> pat_map;
std::map<int, Patient_Log_t> pat_log_map;

extern std::map<int, Hospitals_t> hosp_map_LFU;
extern std::map<int, Doctors_t> doc_map_LFU;
extern std::map<int, Patients_t> pat_map_LFU;
extern std::map<int, Patient_Log_t> pat_log_map_LFU;

extern unsigned int num_DB_Reqs;

//--------------------------------------------------------
using namespace std;
//--------------------------------------------------------

//------------------------------------------------------------------------------------------------
//------------------ clear LFU cache after DB_req = 1000;
void clearAll_LFU()
{
    hosp_map_LFU.clear();
    doc_map_LFU.clear();
    pat_map_LFU.clear();
    pat_log_map_LFU.clear();

    std::cout << "All LFU Cache Cleared\n...";
}

//------------------------------------------------------------------------------------------------
//------------------ clear MFU cache after clear all cache request
void clearALL_MFU()
{
    hosp_map.clear();
    doc_map.clear();
    pat_map.clear();
    pat_log_map.clear();

    std::cout << "All MFU Cache Cleared\n...";
}

//------------------------------------------------------------------------------------------------

Hospitals_t MedicalSystem::CreateHospData(RequestData req)
{
    Hosp_DB hdb;
    hdb.ReadTable(req.GetConditionData());
    return hdb.ReturnHospital();
}
//--------------------------------------------------------
Doctors_t MedicalSystem::CreateDocData(RequestData req)
{
    Doc_DB ddb;
    ddb.ReadTable(req.GetConditionData());
    return ddb.ReturnDoctor();
}
//-------------------------------------------------------
Patients_t MedicalSystem::CreatePatData(RequestData req)
{
    Pat_DB pdb;
    pdb.ReadTable(req.GetConditionData());
    return pdb.ReturnPatient();
}
//--------------------------------------------------------
Patient_Log_t MedicalSystem::CreatePatLogData(RequestData req)
{
    PatLog_DB pldb;
    pldb.ReadTable(req.GetConditionData()); // reqstr);
    return pldb.ReturnPatientLog();
}
Acknowledgement_t MedicalSystem::UpdatePatLog(RequestData request)
{

    Acknowledgement acknow;

    std::promise<Acknowledgement_t> prom;
    std::future<Acknowledgement_t> fut = prom.get_future();

    std::unique_ptr<DBMS_update> req = std::unique_ptr<DBMS_update>(new DBMS_update);
    req->acknow = acknow;
    req->request = request;
    req->prom = std::move(prom);

    dbms_rq_lock.lock();
    dbms_rq.push(std::move(req));
    dbms_rq_cv.notify_one();
    dbms_rq_lock.unlock();

    acknow = fut.get();

    // acknow.SetAck(pldb.UpdateTable(req.GetConditionData()));

    if (pat_log_map.size() != 0)
        pat_log_map.clear();

    return acknow;
}

//------------------- OPERATION OF NORMAL MUTEX LOCK-LESS THREAD
void MedicalSystem::MainFrame(std::unique_ptr<ServerSocket> socket, int id, int my_uid, int bk1_port, char *bk1_ip, int bk2_port, char *bk2_ip)
{
    int req_type;

    RequestData request;
    Hospitals hospital;
    Doctors doctor;
    Patients patient;
    Patient_Log patient_log;
    Acknowledgement acknow;

    ServerStub stub;

    stub.Init(std::move(socket));

    while (true)
    {

        request = stub.ReceiveRequest();
        if (!request.IsValid())
        {
            break;
        }

        req_type = request.GetType();

        switch (req_type)
        {
        case 1: // read req
        {
            switch (request.GetTable())
            {
            case 1: // hospitals
            {
                Hospitals hospital;

                int id = request.GetConditionData();

                if (hosp_map.count(id) == 0)
                {
                    if (hosp_map_LFU.count(id) == 0)
                    {
                        cout << "requesting DB: \n";
                        hospital = CreateHospData(request);
                    }
                    else
                    {
                        hosp_map_LFU.at(id).SetCacheFlag();
                        hospital = hosp_map_LFU.at(id);
                        if (hosp_map_LFU.at(id).GetCacheFlag() > 5)
                            hosp_map.insert(std::pair<int, Hospitals_t>(id, hosp_map_LFU.at(id)));
                    }
                }
                else
                {
                    hospital = hosp_map.at(id);
                }

                stub.SendHospData(hospital);

                if (hospital.IsValid())
                    hospital.print();
                else
                    std::cout << "Invalid hopital at requested ID: " << request.GetConditionData() << std::endl;
            }
            break;

            case 2: // doctors
            {
                Doctors doctor;

                int id = request.GetConditionData();

                if (doc_map.count(id) == 0)
                {
                    if (doc_map_LFU.count(id) == 0)
                    {
                        cout << "requesting DB: \n";
                        doctor = CreateDocData(request);
                    }
                    else
                    {
                        doc_map_LFU.at(id).SetCacheFlag();
                        doctor = doc_map_LFU.at(id);
                        if (doc_map_LFU.at(id).GetCacheFlag() > 5)
                            doc_map.insert(std::pair<int, Doctors_t>(id, doc_map_LFU.at(id)));
                    }
                }
                else
                {
                    doctor = doc_map.at(id);
                }

                stub.SendDocData(doctor);

                if (doctor.IsValid())
                    doctor.print();
                else
                    std::cout << "Invalid doctor at requested ID: " << request.GetConditionData() << std::endl;
            }
            break;

            case 3: // patient
            {
                Patients patient;

                int id = request.GetConditionData();

                if (pat_map.count(id) == 0)
                {
                    if (pat_map_LFU.count(id) == 0)
                    {
                        cout << "requesting DB: \n";
                        patient = CreatePatData(request);
                    }
                    else
                    {
                        pat_map_LFU.at(id).SetCacheFlag();
                        patient = pat_map_LFU.at(id);
                        if (pat_map_LFU.at(id).GetCacheFlag() > 5)
                            pat_map.insert(std::pair<int, Patients>(id, pat_map_LFU.at(id)));
                    }
                }

                else
                {
                    patient = pat_map.at(id);
                }

                stub.SendPatData(patient);

                if (patient.IsValid())
                    patient.print();
                else
                    std::cout << "Invalid patient at requested ID: " << request.GetConditionData() << std::endl;
            }
            break;

            case 4: // patient_log
            {
                Patient_Log patient_log;

                int id = request.GetConditionData();

                if (pat_log_map.count(id) == 0)
                {
                    if (pat_log_map_LFU.count(id) == 0)
                    {
                        cout << "requesting DB: \n";
                        patient_log = CreatePatLogData(request);
                    }
                    else
                    {
                        pat_log_map_LFU.at(id).SetCacheFlag();
                        patient_log = pat_log_map_LFU.at(id);
                        if (pat_log_map_LFU.at(id).GetCacheFlag() > 5)
                            pat_log_map.insert(std::pair<int, Patient_Log>(id, pat_log_map_LFU.at(id)));
                    }
                }
                else
                {
                    patient_log = pat_log_map.at(id);
                }

                stub.SendPatLogData(patient_log);

                if (patient_log.IsValid())
                    patient_log.print();
                else
                    std::cout << "Invalid patient_log at requested ID: " << request.GetConditionData() << std::endl;
            }
            break;

            default:
                break;
            }

            //  if(num_DB_Reqs > 500)
            //     {
            //         clearAll_LFU();
            //         num_DB_Reqs = 0;
            //     }
        }

        break;

        case 2: // write req
        {
            // write
        }

        break;

        case 3: // update req
        {
            clearAll_LFU();
            clearALL_MFU();
            Acknowledgement acknow;
            Acknowledgement ack_bk1;
            Acknowledgement ack_bk2;
            PeerStub p_stub1;
            PeerStub p_stub2;

            // update self
            acknow = UpdatePatLog(request);
            // send it to bkup 1
            if (my_uid == 1)
            {
                p_stub1.Init(bk1_ip, bk1_port);

                do
                {
                    ack_bk1 = p_stub1.UpdatePatientLog(request);
                } while (!ack_bk1.IsValid());

                // send it to bkup 2
                p_stub2.Init(bk2_ip, bk2_port);
                do
                {
                    ack_bk2 = p_stub2.UpdatePatientLog(request);

                } while (!ack_bk2.IsValid());

                if (ack_bk1.IsValid() && ack_bk2.IsValid())
                    stub.SendAck(acknow);
            }
            else
                stub.SendAck(acknow);
        }
        break;

        case 4: // delete req
        {
            // delete
        }
        break;

        default:
            std::cout << "INVALID REQUEST TYPE: " << req_type << std::endl;
        }
        break;
    }
}

//------------------- OPERATION OF MUTEX LOCK BASED THREAD IMPLEMENTAION
void MedicalSystem::DBMS_thread(int id)
{
    std::unique_lock<std::mutex> ul(dbms_rq_lock, std::defer_lock);

    while (true)
    {
        ul.lock();
        PatLog_DB pldb;
        if (dbms_rq.empty())
        {
            dbms_rq_cv.wait(ul, [this]
                            { return !dbms_rq.empty(); });
        }

        auto req = std::move(dbms_rq.front());
        dbms_rq.pop();

        ul.unlock();

        std::this_thread::sleep_for(std::chrono::microseconds(1000));

        // req->laptop.SetExpertId(id);
        // req->prom.set_value(req->laptop);

        req->acknow.SetAck(pldb.UpdateTable(req->request.GetConditionData()));
        req->prom.set_value(req->acknow);
    }
}
