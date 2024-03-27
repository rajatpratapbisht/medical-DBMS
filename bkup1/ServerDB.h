#ifndef __SERVERDB_H__
#define __SERVERDB_H__



#include <iostream>
#include <sqlite3.h>
#include <map>
#include "Messages.h"
#include <cstring>

extern std::map<int, Hospitals_t> hosp_map_LFU;
extern std::map<int, Doctors_t> doc_map_LFU;
extern std::map<int, Patients_t> pat_map_LFU;
extern std::map<int, Patient_Log_t> pat_log_map_LFU;

extern unsigned int num_DB_Reqs;

//#########################################################
//############# Class: Hosp_DB
//#########################################################
class Hosp_DB
{
    Hospitals hosp;
    static int Hosp_callback(void *NotUsed, int argc, char **argv, char **azColName)
    {
        Hospitals h;
        // azColName[i+0] = ID
        // azColName[i+1] = ADDRESS
        // azColName[i+2] = DOC_COUNT
        // azColName[i+3] = BED_COUNT
        // azColName[i+4] = BED_EMPTY
        h.SetHospital(atoi(argv[0]),
                      atoi(argv[1]),
                      atoi(argv[2]),
                      atoi(argv[3]),
                      atoi(argv[4]), 0);

        if(h.IsValid())
            hosp_map_LFU.insert(std::pair<int, Hospitals_t>(h.GetId(), h));

        num_DB_Reqs++;
        return 0;
    }

public:
    ~Hosp_DB(){}
    int CreateTable();
    int InsertTable();
    int ReadTable(int h_id);
    int updateTable();
    Hospitals_t ReturnHospital();
};

//#########################################################
//############# Class: Doc_DB
//#########################################################
class Doc_DB
{
    Doctors doc;

public:
    static int Doc_callback(void *flag, int argc, char **argv, char **azColName)
    {
        {
            Doctors d;
            // azColName[i+0] = ID
            // azColName[i+1] = HOSP_ID
            // azColName[i+2] = SPECIALITY
            d.SetDoctors(atoi(argv[0]),
                         atoi(argv[1]),
                         *argv[2], 0);
            
            if(d.IsValid())
                doc_map_LFU.insert(std::pair<int, Doctors_t>(d.GetId(), d));
            
            num_DB_Reqs++;
            return 0;
        }
    }
    ~Doc_DB(){}
    //-----------------------------
    int CreateTable();
    //-----------------------------
    int InsertTable();
    //-----------------------------
    int ReadTable(int req_id);
    //-----------------------------
    int updateTable();
    //-----------------------------
    Doctors_t ReturnDoctor();
    //-----------------------------
};

//#########################################################
//############# Class:Pat_DB
//#########################################################
//#################################################
class Pat_DB
{
    Patients_t pat;
    int units = 0;

public:
    static int Pat_callback(void *flag, int argc, char **argv, char **azColName)
    {
        Patients p;

       

        for (int i = 0; i < argc; i += 3)
        {
            // azColName[i+0] = ID
            // azColName[i+1] = age
            // azColName[i+2] = address
            p.SetPatients(atoi(argv[0]),
                          atoi(argv[1]),
                          atoi(argv[2]), 0);
            
            if(p.IsValid())
                pat_map_LFU.insert(std::pair<int, Patients_t>(p.GetId(), p));
        }

        num_DB_Reqs++;
        return 0;
    }

    ~Pat_DB(){};
    //-----------------------------
    int updateTable();
    //-----------------------------
    int CreateTable();
    //-----------------------------
    int InsertTable();
    //-----------------------------
    int ReadTable(int p_id);
    //-----------------------------
    Patients_t ReturnPatient();
};
//#########################################################
//############# Class: PatLog_DB
//#########################################################
class PatLog_DB
{
    Patient_Log pat_log;

public:
    ~PatLog_DB(){}
    
    static int PL_callback(void *flag, int argc, char **argv, char **azColName)
    {
        //---- to read data
        Patient_Log pl;
        int ex;
        int ad;
        if (strcmp(argv[2], "Y") == 0)
        {
            ex = 1;
        }
        else
            ex = 0;
        if (strcmp(argv[3], "Y") == 0)
        {
            ad = 1;
        }
        else
            ad = 0;

        // azColName[i+0] = PAT_ID
        // azColName[i+1] = DOC_ID
        // azColName[i+2] = EXAMINED
        // azColName[i+3] = ADMITTED
        pl.SetPatient_Log(atoi(argv[0]),
                          atoi(argv[1]),
                          ex,
                          ad, 0);
        
        if(pl.IsValid())
            pat_log_map_LFU.insert(std::pair<int, Patient_Log_t>(pl.GetPatId(), pl));
        
        num_DB_Reqs++;
        return 0;
    }
    //-----------------------------
    int CreateTable();
    //-----------------------------
    int InsertTable();

    //-----------------------------
    int ReadTable(int id); // int d_or_p)

    Patient_Log_t ReturnPatientLog();
    

    int UpdateTable(int id);
};
#endif // end of #ifndef __SERVERDB_H__