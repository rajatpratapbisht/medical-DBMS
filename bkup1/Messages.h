#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define DATABASE_NAME "medical.db"



//############################################################################
//################ CLASS: HOSPITALS ##########################################
//############################################################################
class Hospitals
{
private:
    int id;
    int address;
    int doc_count;
    int bed_count;
    int bed_empty;
    int cache_read;

public:
    Hospitals();
    void operator=(const Hospitals &hosp)
    {
        id = hosp.id;
        address = hosp.address;
        doc_count = hosp.doc_count;
        bed_count = hosp.bed_count;
        bed_empty = hosp.bed_empty;
        cache_read = hosp.cache_read;
    }

    void SetHospital(int h_id, int addr, int d_count, int b_count, int b_empty, int ch_rd);
    void SetCacheFlag();

    int GetId();
    int GetAddress();
    int GetDocCount();
    int GetBedCount();
    int GetBedEmpty();
    int GetCacheFlag();

    int Size();

    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();

}typedef Hospitals_t;

//############################################################################
//################ CLASS: DOCTORS ############################################
//############################################################################
class Doctors
{
private:
    int id;
    char sepciality;
    int hosp_id;
    int cache_read;
public:
    Doctors();
    void operator=(const Doctors &docs)
    {
        id = docs.id;
        sepciality = docs.sepciality;
        hosp_id = docs.hosp_id;
        cache_read = docs.cache_read;
    }

    void SetDoctors(int d_id, int h_id, char spec, int ch_rd );
    void SetCacheFlag();

    int GetId();
    char GetSepciality();
    int GetHospId();
    int GetCacheFlag();

    int Size();

    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();
}typedef Doctors_t;

//############################################################################
//################ CLASS: PATIENTS ##########################################
//############################################################################
class Patients
{
private:
    int id;
    int age;
    int address;
    int cache_read;
public:
    Patients();
    void operator=(const Patients &pat)
    {
        id = pat.id;
        age = pat.age;
        address = pat.address;
        cache_read = pat.cache_read;
    }

    void SetPatients(int p_id, int ag, int addr, int ch_rd );
    void SetCacheFlag();

    int GetId();
    int GetAddress();
    int GetAge();
    int GetCacheFlag();

    int Size();

    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();
}typedef Patients_t;

//############################################################################
//################ CLASS: PATIENTLOG ##########################################
//############################################################################
class Patient_Log
{
private:
    int pat_id;
    int doc_id;
    int examined;
    int admitted;
    int cache_read;
public:
    Patient_Log();
    void operator=(const Patient_Log &p_log)
    {
        pat_id = p_log.pat_id;
        doc_id = p_log.doc_id;
        examined = p_log.examined;
        admitted = p_log.admitted;
        cache_read = p_log.cache_read;
    }

    void SetPatient_Log(int p_id, int d_id, int ex, int ad, int ch_rd );
    void SetCacheFlag();

    int GetPatId();
    int GetDocId();
    int GetExamined();
    int GetAdmitted();
    int GetCacheFlag();

    int Size();

    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();
}typedef Patient_Log_t;

//############################################################################
//################ CLASS: REQUESTDATA ##########################################
//############################################################################
class RequestData
{
    private:
    int table;  //1-hospital, 2-doctor, 3-patient, 4-pat_log
    int condition; //1-id, 2-address
    int type; // 1-read, 2-insert, 3-update, 4-delete
    int condition_data;
    int requester; //1-hospital, 2-doctor, 3-patient, 4-pat_log
    public:

    RequestData();
    void operator=(const RequestData &req)
    {
        table = req.table;
        condition = req.condition;
        type = req.type;
        condition_data = req.condition_data;
        requester = req.requester;
    }
    void SetRequest(int tab, int cdn, int typ, int cdn_data, int reqstr);
    
    int GetTable();
    int GetCondition();
    int GetType();
    int GetConditionData();
    int Getrequester();

    int Size();
    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();

}typedef RequestData_t;


class Acknowledgement{
    int ack;
    public:
    Acknowledgement();
    void operator = (const Acknowledgement &acknow)
    {
        ack = acknow.ack;
    }
    void SetAck(int i);

    int GetAck();

    int Size();
    void Marshal(char *buffer);
    void Unmarshal(char *buffer);
    bool IsValid();
    void print();
}typedef Acknowledgement_t;
#endif // #ifndef __SERVER_MESSAGES_H__