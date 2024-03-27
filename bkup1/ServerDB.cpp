#include "ServerDB.h"

#define DATABASE_NAME "medical.db"

std::map<int, Hospitals_t> hosp_map_LFU;
std::map<int, Doctors_t> doc_map_LFU;
std::map<int, Patients_t> pat_map_LFU;
std::map<int, Patient_Log_t> pat_log_map_LFU;

unsigned int num_DB_Reqs = 0;

//#########################################################
//############# Class:Hosp_DB
//#########################################################

int Hosp_DB::CreateTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "CREATE TABLE HOSPITALS (ID INTEGER PRIMARY KEY AUTOINCREMENT, ADDRESS int not null, DOC_COUNT int not null, BED_COUNT int not null, BED_EMPTY int not null)";

    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Hosp_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}

//-----------------------------------------------------------
int Hosp_DB::InsertTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string sql = "INSERT into HOSPITALS (ADDRESS, DOC_COUNT, BED_COUNT, BED_EMPTY) VALUES ";

    char values[50];

    // OPEN DATABASE
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // CREATE SQL STATEMENTS
    snprintf(values, 50,
             "(%d, %d, %d, %d);",
             hosp.GetAddress(), hosp.GetDocCount(), hosp.GetBedCount(), hosp.GetBedEmpty());
    sql.append(values);

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Hosp_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    else
    {
        fprintf(stdout, "Records INSERTED successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
//-----------------------------------------------------------
int Hosp_DB::ReadTable(int h_id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string condition = " WHERE ID = " + std::to_string(h_id);

    std::string sql = "SELECT * from HOSPITALS ";

    // Open database
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    if (h_id != -1)
    {
        sql.append(condition);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), Hosp_callback, 0, &zErrMsg);

    if(hosp_map_LFU.count(h_id) != 0)
        hosp = hosp_map_LFU.at(h_id);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    sqlite3_close(db);
    return 0;
}
//-----------------------------------------------------------
// int Hosp_DB::updateTable();
//-----------------------------------------------------------
Hospitals_t Hosp_DB::ReturnHospital() { return hosp; }
//-----------------------------------------------------------

//#########################################################
//############# Class: Doc_DB
//#########################################################

int Doc_DB::CreateTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "CREATE TABLE DOCTORS (ID integer primary key autoincrement, HOSP_ID int not null, SPECIALITY text not null, FOREIGN KEY(HOSP_ID) REFERENCES HOSPITALS(ID))";

    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Doc_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}
int Doc_DB::InsertTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string sql = "INSERT into DOCTORS (HOSP_ID, SPECIALITY) VALUES ";

    char values[50];

    // OPEN DATABASE
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // CREATE SQL STATEMENTS
    snprintf(values, 50,
             "(%d, \'%c\');",
             doc.GetHospId(), doc.GetSepciality());
    sql.append(values);

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Doc_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    else
    {
        fprintf(stdout, "Records INSERTED successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
int Doc_DB::ReadTable(int req_id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string condition = " WHERE ID = " + std::to_string(req_id);

    std::string sql = "SELECT * from DOCTORS ";

    // Open database
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    if (req_id != -1)
    {
        sql.append(condition);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), Doc_callback, 0, &zErrMsg);

    if(doc_map_LFU.count(req_id) != 0)
        doc = doc_map_LFU.at(req_id);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    sqlite3_close(db);
    return 0;
}
// int Doc_DB::updateTable();
Doctors_t Doc_DB::ReturnDoctor() { return doc; }

//#########################################################
//############# Class:Pat_DB
//#########################################################

// int Pat_DB::updateTable();
int Pat_DB::CreateTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "CREATE TABLE PATIENTS (ID integer primary key autoincrement, AGE int not null, ADDRESS int not null)";

    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Pat_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}

//-----------------------------
int Pat_DB::InsertTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string sql = "INSERT into PATIENTS (AGE, ADDRESS) VALUES ";

    char values[50];

    // OPEN DATABASE
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // CREATE SQL STATEMENTS
    snprintf(values, 50,
             "(%d, %d);",
             pat.GetAge(), pat.GetAddress());
    sql.append(values);

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), Pat_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    else
    {
        fprintf(stdout, "Records INSERTED successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

//-----------------------------
int Pat_DB::ReadTable(int p_id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    std::string condition = " WHERE ID = " + std::to_string(p_id);

    std::string sql = "SELECT * from PATIENTS ";

    // Open database
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    if (p_id != -1)
    {
        sql.append(condition);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), Pat_callback, 0, &zErrMsg);

    if(pat_map_LFU.count(p_id) != 0)
        pat = pat_map_LFU.at(p_id);

    // pat_map.erase(p_id);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    sqlite3_close(db);
    return 0;
}

Patients_t Pat_DB::ReturnPatient() { return pat; }
//#########################################################
//############# Class: PatLog_DB
//#########################################################

int PatLog_DB::CreateTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "CREATE TABLE PATIENTLOG (PAT_ID int not null, DOC_ID not null, EXAMINED TEXT not null, ADMITTED TEXT not null, FOREIGN KEY(PAT_ID) REFERENCES PATIENTS(ID), FOREIGN KEY(DOC_ID) REFERENCES DOCTORS(ID))";

    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), PL_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}

//-----------------------------
int PatLog_DB::InsertTable()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char ex;
    char ad;
    ex = (pat_log.GetExamined() == 1) ? 'Y' : 'N';
    ad = (pat_log.GetAdmitted() == 1) ? 'Y' : 'N';

    std::string sql = "INSERT into PATIENTLOG (PAT_ID, DOC_ID, EXAMINED, ADMITTED) VALUES ";

    char values[50];

    // OPEN DATABASE
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // CREATE SQL STATEMENTS
    snprintf(values, 50,
             "(%d, %d, \'%c\', \'%c\' );",
             pat_log.GetPatId(), pat_log.GetDocId(), ex, ad);
    sql.append(values);

    // EXECUTE SQL STATEMENTS
    rc = sqlite3_exec(db, sql.c_str(), PL_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    else
    {
        fprintf(stdout, "Records INSERTED successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

//-----------------------------
int PatLog_DB::ReadTable(int id) // int d_or_p)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string condition;
    // char *flag = "r";
    std::string sql = "SELECT * from PATIENTLOG WHERE PAT_ID = " + std::to_string(id);

    // Open database
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), PL_callback, 0, &zErrMsg);

    if(pat_log_map_LFU.count(id) != 0)
        pat_log = pat_log_map_LFU.at(id);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }
    sqlite3_close(db);
    return 0;
}

Patient_Log_t PatLog_DB::ReturnPatientLog() { return pat_log; }

int PatLog_DB::UpdateTable(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string condition;
    std::string sql = "UPDATE PATIENTLOG SET EXAMINED = \'Y\' WHERE doc_id = " + std::to_string(id);

    // Open database
    rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), PL_callback, 0, &zErrMsg);

    // pat_log = pat_log_map_LFU.at(id);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 1;
}