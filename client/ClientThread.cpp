#include "ClientThread.h"

ClientThreadClass::ClientThreadClass() {}

void ClientThreadClass::ThreadBody(std::string ip, int port, int id, int request_type, int req_table)
{
    table = req_table;
    type = request_type;
    condition_data = id;
    requester = req_table; // default

    if(type == 3)
    {
        ip = "127.0.0.1";
        port = 2474;
    }
    if (!stub.Init(ip, port))
    {
        std::cout << "Thread " << id << " failed to connect" << std::endl;
        return;
    }

    // initialise data types
    RequestData request;
    Hospitals hospital;
    Doctors doctor;
    Patients patient;
    Patient_Log patient_log;
    Acknowledgement acknow;

    // // set request
    // if (table == 4 && type == 3)
    // {
    //     // update patlog only by doctor;
    //     request.SetRequest(table, condition, type, condition_data, 3);
    // }
    // else
    // {
    //     // normal request
    //     request.SetRequest(table, condition, type, condition_data, requester);
    // }

    request.SetRequest(table, condition, type, condition_data, requester);

    if (!request.IsValid())
    {
        std::cout << "INVALID REQUEST \n";
        return;
    }
    // initiate request
    switch (table)
    {
    case 1: // hospitals table req
    {
        timer.Start();
        hospital = stub.RequestHospital(request);
        timer.EndAndMerge();

        if (hospital.IsValid())
        {
            hospital.print();
        }
        else
        {
            std::cout << "INVALID HOSPITAL DATA for ID: " << id << std::endl;
        }
    }
    break;

    case 2: // doctors table req
    {
        timer.Start();
        doctor = stub.RequestDoctor(request);
        timer.EndAndMerge();

        if (doctor.IsValid())
        {
            doctor.print();
        }
        else
        {
            std::cout << "INVALID DOCTOR DATA for ID: " << id << std::endl;
        }
    }
    break;

    case 3: // patients table req
    {
        timer.Start();
        patient = stub.RequestPatent(request);
        timer.EndAndMerge();

        if (patient.IsValid())
        {
            patient.print();
        }
        else
        {
            std::cout << "INVALID PATIENT DATA for ID: " << id << std::endl;
        }
    }
    break;

    case 4: // patient_log table req
    {
        if (type == 1) // read request only by patient
        {
            timer.Start();
            patient_log = stub.RequestPatientLog(request);
            timer.EndAndMerge();

            if (patient_log.IsValid())
            {
                patient_log.print();
            }
            else
            {
                std::cout << "INVALID PATIENT LOG DATA for ID: " << id << std::endl;
            }
        }
        else if (type == 3) // update pat_log only by doctors
        {
            timer.Start();
            acknow = stub.UpdatePatientLog(request);
            timer.EndAndMerge();

            if (acknow.IsValid())
            {
                acknow.print();
            }
            else
            {
                std::cout << "INVALID ACKNOWLEDGEMENT DATA for ID: " << id << std::endl;
            }
        }
    }
    break;

    default:
        std::cout << "INVALID Table request: " << table << std::endl;
        break;
    }
}
ClientTimer ClientThreadClass::GetTimer()
{
    return timer;
}
