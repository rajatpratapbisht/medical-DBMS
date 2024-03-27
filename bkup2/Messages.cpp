#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include "Messages.h"

//############################################################################
//################ CLASS: HOSPITALS ##########################################
//############################################################################
//-----------------------------HOSPITAL CONSTRUCTOR-------------------------------------
Hospitals::Hospitals()
{
    id = -1;
    address = -1;
    doc_count = -1;
    bed_count = -1;
    bed_empty = -1;
    cache_read = 0;
}
//-----------------------------SET HOSPITAL INFORMATION-------------------------------------
void Hospitals::SetHospital(int h_id, int addr, int d_count, int b_count, int b_empty, int ch_rd)
{
    id = h_id;
    address = addr;
    doc_count = d_count;
    bed_count = b_count;
    bed_empty = b_empty;
    cache_read = ch_rd;
}

//----------------------------- IF READ FROM THE CACHE MEMORY WE SET THIS FLAG TO 1
void Hospitals::SetCacheFlag()
{
    cache_read += 1;
}

//----------------------------- QUERY FOR CLASS OBEJCT DATA-------------------------------------
int Hospitals::GetId() { return id; }
int Hospitals::GetAddress() { return address; }
int Hospitals::GetDocCount() { return doc_count; }
int Hospitals::GetBedCount() { return bed_count; }
int Hospitals::GetBedEmpty() { return bed_empty; }
int Hospitals::GetCacheFlag() { return cache_read; }

//-----------------------------RETURN SIZE OF HOSPITAL CLASS-------------------------------------
int Hospitals::Size()
{
    return sizeof(id) + sizeof(address) + sizeof(doc_count) + sizeof(bed_count) + sizeof(bed_empty) + sizeof(cache_read);
}

//-----------------------------MARSHAL HOSPITAL DATA FOR TCP/UDP-------------------------------------
void Hospitals::Marshal(char *buffer)
{
    int net_id = htonl(id);
    int net_address = htonl(address);
    int net_doc_count = htonl(doc_count);
    int net_bed_count = htonl(bed_count);
    int net_bed_empty = htonl(bed_empty);
    int net_cahce_read = htonl(cache_read);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_id, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(buffer + offset, &net_address, sizeof(net_address));
    offset += sizeof(net_address);

    memcpy(buffer + offset, &net_doc_count, sizeof(net_doc_count));
    offset += sizeof(net_doc_count);

    memcpy(buffer + offset, &net_bed_count, sizeof(net_bed_count));
    offset += sizeof(net_bed_count);

    memcpy(buffer + offset, &net_bed_empty, sizeof(net_bed_empty));
    offset += sizeof(net_bed_empty);

    memcpy(buffer + offset, &net_cahce_read, sizeof(net_cahce_read));
    offset += sizeof(net_cahce_read);
}

//-----------------------------UN-MARSHAL HOSPITAL DATA FROM TCP/UDP-------------------------------------
void Hospitals::Unmarshal(char *buffer)
{
    int net_id;
    int net_address;
    int net_doc_count;
    int net_bed_count;
    int net_bed_empty;
    int net_cahce_read;

    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_id, buffer + offset, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(&net_address, buffer + offset, sizeof(net_address));
    offset += sizeof(net_address);

    memcpy(&net_doc_count, buffer + offset, sizeof(net_doc_count));
    offset += sizeof(net_doc_count);

    memcpy(&net_bed_count, buffer + offset, sizeof(net_bed_count));
    offset += sizeof(net_bed_count);

    memcpy(&net_bed_empty, buffer + offset, sizeof(net_bed_empty));
    offset += sizeof(net_bed_empty);

    memcpy(&net_cahce_read, buffer + offset, sizeof(net_cahce_read));

    // copy data to the class data types
    id = ntohl(net_id);
    address = ntohl(net_address);
    doc_count = ntohl(net_doc_count);
    bed_count = ntohl(net_bed_count);
    bed_empty = ntohl(net_bed_empty);
    cache_read = ntohl(net_cahce_read);
}

//-----------------------------CHECK IF HOSPITAL DATA IS VALID-------------------------------------
bool Hospitals::IsValid()
{
    return (id != -1);
}

//-----------------------------PRINTOUT HOSPITAL DATA-------------------------------------
void Hospitals::print()
{
    if (cache_read > 0)
        std::cout << "reading from cache:" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "ADDRESS: " << address << std::endl;
    std::cout << "DOCTOR COUNT: " << doc_count << std::endl;
    std::cout << "TOTAL BED CAPACITY: " << bed_count << std::endl;
    std::cout << "REMAING EMPTY BEDS: " << bed_empty << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}

//############################################################################
//################ CLASS: DOCTORS ############################################
//############################################################################
//-----------------------------DOCTORS CONSTRUCTOR-------------------------------------
Doctors::Doctors()
{
    id = -1;
    sepciality = '\0';
    hosp_id = -1;
    cache_read = 0;
}
//-----------------------------SET DOCTORS INFORMATION-------------------------------------
void Doctors::SetDoctors(int d_id, int h_id, char spec, int ch_rd)
{
    id = d_id;
    sepciality = spec;
    hosp_id = h_id;
    cache_read = ch_rd;
}

//----------------------------- IF READ FROM THE CACHE MEMORY WE SET THIS FLAG TO 1
void Doctors::SetCacheFlag()
{
    cache_read += 1;
}

//----------------------------- QUERY FOR CLASS OBEJCT DATA TYPES
int Doctors::GetId() { return id; }
char Doctors::GetSepciality() { return sepciality; }
int Doctors::GetHospId() { return hosp_id; }
int Doctors::GetCacheFlag() { return cache_read; }

//-----------------------------RETURN SIZE OF DOCTORS CLASS-------------------------------------
int Doctors::Size()
{
    return sizeof(id) + sizeof(sepciality) + sizeof(hosp_id) + sizeof(cache_read);
}
//-----------------------------MARSHAL DOCTORS DATA FOR TCP/UDP-------------------------------------
void Doctors::Marshal(char *buffer)
{
    int net_id = htonl(id);
    int net_sepciality = htonl(sepciality);
    int net_hosp_id = htonl(hosp_id);
    int net_cahce_read = htonl(cache_read);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_id, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(buffer + offset, &net_sepciality, sizeof(net_sepciality));
    offset += sizeof(net_sepciality);

    memcpy(buffer + offset, &net_hosp_id, sizeof(net_hosp_id));
    offset += sizeof(net_hosp_id);

    memcpy(buffer + offset, &net_cahce_read, sizeof(net_cahce_read));
}
//-----------------------------UN-MARSHAL DOCTORS DATA FROM TCP/UDP-------------------------------------
void Doctors::Unmarshal(char *buffer)
{
    int net_id;
    int net_sepciality;
    int net_hosp_id;
    int net_cahce_read;

    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_id, buffer + offset, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(&net_sepciality, buffer + offset, sizeof(net_sepciality));
    offset += sizeof(net_sepciality);

    memcpy(&net_hosp_id, buffer + offset, sizeof(net_hosp_id));
    offset += sizeof(net_hosp_id);

    memcpy(&net_cahce_read, buffer + offset, sizeof(net_cahce_read));

    // copy data to the class data types
    id = ntohl(net_id);
    sepciality = ntohl(net_sepciality);
    hosp_id = ntohl(net_hosp_id);
    cache_read = ntohl(net_cahce_read);
}
//-----------------------------CHECK IF DOCTORS DATA IS VALID-------------------------------------
bool Doctors::IsValid()
{
    return (id != -1);
}
//-----------------------------PRINTOUT DOCTORS DATA-------------------------------------
void Doctors::print()
{
    if (cache_read > 0)
        std::cout << "reading from cache:" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "SPECIALTY: " << sepciality << std::endl;
    std::cout << "HOSPITAL ID: " << hosp_id << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}

//############################################################################
//################ CLASS: PATIENTS ##########################################
//############################################################################

//------------------ PATIENTS CLASS CONSTRUCTOR
Patients::Patients()
{
    id = -1;
    age = -1;
    address = -1;
    cache_read = 0;
}

//------------------ SET PATIENT INFORMATION INTO CLASS OBJECTS
void Patients::SetPatients(int p_id, int ag, int addr, int ch_rd)
{
    id = p_id;
    age = ag;
    address = addr;
    cache_read = ch_rd;
}

//----------------------------- IF READ FROM THE CACHE MEMORY WE SET THIS FLAG TO 1
void Patients::SetCacheFlag()
{
    cache_read += 1;
}

//------------------ QUERY FOR CAERTAIN SPECIFIC DATA FROM CLASS OBEJCTS
int Patients::GetId() { return id; }
int Patients::GetAddress() { return address; }
int Patients::GetAge() { return age; }
int Patients::GetCacheFlag() { return cache_read; }

//------------------ GET SIZE OF THE CLASS OBJECT
int Patients::Size()
{
    return sizeof(id) + sizeof(age) + sizeof(address) + sizeof(cache_read);
}

//------------------ MARSHALL DATA FOR COMMUNICATION
void Patients::Marshal(char *buffer)
{
    int net_id = htonl(id);
    int net_age = htonl(age);
    int net_address = htonl(address);
    int net_cahce_read = htonl(cache_read);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_id, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(buffer + offset, &net_age, sizeof(net_age));
    offset += sizeof(net_age);

    memcpy(buffer + offset, &net_address, sizeof(net_address));
    offset += sizeof(net_address);

    memcpy(buffer + offset, &net_cahce_read, sizeof(net_cahce_read));
}

//------------------ UNMARSHALL THE RECEIVED DATA INTO CLASS OBJECT DATA TYPE
void Patients::Unmarshal(char *buffer)
{
    int net_id;
    int net_age;
    int net_address;
    int net_cahce_read;

    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_id, buffer + offset, sizeof(net_id));
    offset += sizeof(net_id);

    memcpy(&net_age, buffer + offset, sizeof(net_age));
    offset += sizeof(net_age);

    memcpy(&net_address, buffer + offset, sizeof(net_address));
    offset += sizeof(net_address);

    memcpy(&net_cahce_read, buffer + offset, sizeof(net_cahce_read));

    // copy data to the class data types
    id = ntohl(net_id);
    age = ntohl(net_age);
    address = ntohl(net_address);
    cache_read = ntohl(net_cahce_read);
}

//------------------CHECK IF THE DATA RECEEIVED IS VAID
bool Patients::IsValid()
{
    return (id != -1);
}

//------------------ PRINT DATA STORED IN CLASS OBJECT
void Patients::print()
{
    if (cache_read > 0)
        std::cout << "reading from cache:" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "AGE: " << age << std::endl;
    std::cout << "ADDRESS: " << address << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}

//############################################################################
//################ CLASS: PATIENTLOG ##########################################
//############################################################################

//------------------PATIENT LOG CONSTRUCTOR---------------
Patient_Log::Patient_Log()
{
    pat_id = -1;
    doc_id = -1;
    examined = 0;
    admitted = 0;
    cache_read = 0;
}

//------------------ SET INFORMATION INTO OBJECT

void Patient_Log::SetPatient_Log(int p_id, int d_id, int ex, int ad, int ch_rd)
{
    pat_id = p_id;
    doc_id = d_id;
    examined = ex;
    admitted = ad;
    cache_read = ch_rd;
}
//-----------------------------
void Patient_Log::SetCacheFlag()
{
    cache_read += 1;
}

//------------------ QUERRY SPECIFIC PRIVATE DATA TYPES
int Patient_Log::GetPatId() { return pat_id; }
int Patient_Log::GetDocId() { return doc_id; }
int Patient_Log::GetExamined() { return examined; };
int Patient_Log::GetAdmitted() { return admitted; }
int Patient_Log::GetCacheFlag() { return cache_read;}

//------------------ GET SIZE OF THE OBJECT CLASS
int Patient_Log::Size()
{
    return sizeof(pat_id) + sizeof(doc_id) + sizeof(examined) + sizeof(admitted);
}

//------------------ MARSHAL DATA FOR OUT COMMUNICATION
void Patient_Log::Marshal(char *buffer)
{
    int net_pat_id = htonl(pat_id);
    int net_doc_id = htonl(doc_id);
    int net_examined = htonl(examined);
    int net_admitted = htonl(admitted);
    int net_cahce_read = htonl(cache_read);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_pat_id, sizeof(net_pat_id));
    offset += sizeof(net_pat_id);

    memcpy(buffer + offset, &net_doc_id, sizeof(net_doc_id));
    offset += sizeof(net_doc_id);

    memcpy(buffer + offset, &net_examined, sizeof(net_examined));
    offset += sizeof(net_examined);

    memcpy(buffer + offset, &net_admitted, sizeof(net_admitted));
    offset += sizeof(net_admitted);

    memcpy(buffer + offset, &net_cahce_read, sizeof(net_cahce_read));
}

//------------------ UNMARSHALL RECEIVED DATA INTO CLASS OBJECTS TYPE
void Patient_Log::Unmarshal(char *buffer)
{
    int net_pat_id;
    int net_doc_id;
    int net_examined;
    int net_admitted;
    int net_cahce_read;

    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_pat_id, buffer + offset, sizeof(net_pat_id));
    offset += sizeof(net_pat_id);

    memcpy(&net_doc_id, buffer + offset, sizeof(net_doc_id));
    offset += sizeof(net_doc_id);

    memcpy(&net_examined, buffer + offset, sizeof(net_examined));
    offset += sizeof(net_examined);

    memcpy(&net_admitted, buffer + offset, sizeof(net_admitted));
    offset += sizeof(net_admitted);

    memcpy(&net_cahce_read, buffer + offset, sizeof(net_cahce_read));

    // copy data to the class data types
    pat_id = ntohl(net_pat_id);
    doc_id = ntohl(net_doc_id);
    examined = ntohl(net_examined);
    admitted = ntohl(net_admitted);
    cache_read = ntohl(net_cahce_read);
}

//------------------ CHEECK IF THE DATA IS VALID OR NOT
bool Patient_Log::IsValid()
{
    return (pat_id != -1);
}

//------------------ PRINT OUT DATA STORED IN OBJECT CLASS
void Patient_Log::print()
{
    if (cache_read > 0)
        std::cout << "reading from cache:" << std::endl;
    std::cout << "PATIENT ID: " << pat_id << std::endl;
    std::cout << "DOCTOR ID: " << doc_id << std::endl;
    std::cout << "EXAMINED: " << (examined == 1 ? "YES" : "NO") << std::endl;
    std::cout << "ADMITTED: " << (admitted == 1 ? "YES" : "NO") << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}

//############################################################################
//################ CLASS: REQUEST DATA ##########################################
//############################################################################
RequestData::RequestData()
{
    table = -1;
    condition = -1;
    type = -1;
    condition_data = -1;
}
void RequestData::SetRequest(int tab, int cdn, int typ, int cdn_data, int reqstr)
{
    table = tab;
    condition = cdn;
    type = typ;
    condition_data = cdn_data;
    requester = reqstr;
}

int RequestData::GetTable() { return table; }
int RequestData::GetCondition() { return condition; }
int RequestData::GetType() { return type; }
int RequestData::GetConditionData() { return condition_data; }
int RequestData::Getrequester() { return requester; }

void RequestData::Marshal(char *buffer)
{
    int net_table = htonl(table);
    int net_condition = htonl(condition);
    int net_type = htonl(type);
    int net_condition_data = htonl(condition_data);
    int net_requester = htonl(requester);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_table, sizeof(net_table));
    offset += sizeof(net_table);

    memcpy(buffer + offset, &net_condition, sizeof(net_condition));
    offset += sizeof(net_condition);

    memcpy(buffer + offset, &net_type, sizeof(net_type));
    offset += sizeof(net_type);

    memcpy(buffer + offset, &net_condition_data, sizeof(net_condition_data));
    offset += sizeof(net_condition_data);

    memcpy(buffer + offset, &net_requester, sizeof(net_requester));
    offset += sizeof(net_requester);
}

//------------------ UNMARSHALL RECEIVED DATA INTO CLASS OBJECTS TYPE
void RequestData::Unmarshal(char *buffer)
{
    int net_table;
    int net_condition;
    int net_type;
    int net_condition_data;
    int net_requester;

    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_table, buffer + offset, sizeof(net_table));
    offset += sizeof(net_table);

    memcpy(&net_condition, buffer + offset, sizeof(net_condition));
    offset += sizeof(net_condition);

    memcpy(&net_type, buffer + offset, sizeof(net_type));
    offset += sizeof(net_type);

    memcpy(&net_condition_data, buffer + offset, sizeof(net_condition_data));
    offset += sizeof(net_condition_data);

    memcpy(&net_requester, buffer + offset, sizeof(net_requester));
    offset += sizeof(net_requester);

    // copy data to the class data types
    table = ntohl(net_table);
    condition = ntohl(net_condition);
    type = ntohl(net_type);
    condition_data = ntohl(net_condition_data);
    requester = ntohl(net_requester);
}

//------------------ CHEECK IF THE DATA IS VALID OR NOT
bool RequestData::IsValid()
{
    if (table > 0 && table < 5 && condition > 0 && condition < 3 && type > 0 && type < 5 && requester > 0 && requester < 5)
        return true;

    else
        return false;
}
int RequestData::Size()
{
    return sizeof(table) + sizeof(condition) + sizeof(type) + sizeof(condition_data) + sizeof(requester);
}
//------------------ PRINT OUT DATA STORED IN OBJECT CLASS
void RequestData::print()
{
    std::string tab;
    std::string cdn;
    std::string typ;
    std::string cdn_data;
    switch (table)
    {
    case 1:
        tab = "HOSPITALS";
        break;
    case 2:
        tab = "DOCTROS";
        break;
    case 3:
        tab = "PATIENTS";
        break;
    case 4:
        tab = "PATIENTLOG";
        break;

    default:
        break;
    }
    switch (condition)
    {
    case 1:
        cdn = "ID";
        break;
    case 2:
        cdn = "ADDRESS";
        break;

    default:
        break;
    }
    switch (type)
    {
    case 1:
        typ = "read"; // 1-read, 2-insert, 3-update, 4-delete
        break;
    case 2:
        typ = "insert";
        break;
    case 3:
        typ = "update";
        break;
    case 4:
        typ = "delete";
        break;

    default:
        break;
    }
    std::cout << "table ID: " << tab << std::endl;
    std::cout << "condition ID: " << cdn << std::endl;
    std::cout << "type: " << typ << std::endl;
    std::cout << "condition data: " << condition_data << std::endl;
    std::cout << "requester: " << requester << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}

//############################################################################
//################ CLASS: Acknowledgement ##########################################
//############################################################################
Acknowledgement::Acknowledgement()
{
    ack = -1;
}
void Acknowledgement::SetAck(int i)
{
    ack = i;
}

int Acknowledgement::GetAck() { return ack; }

int Acknowledgement::Size() { return sizeof(ack); }
void Acknowledgement::Marshal(char *buffer)
{
    int net_ack = htonl(ack);

    int offset = 0;

    // MARSHALL DATA
    memcpy(buffer + offset, &net_ack, sizeof(net_ack));
    offset += sizeof(net_ack);
}
void Acknowledgement::Unmarshal(char *buffer)
{
    int net_ack;
    int offset = 0;

    // UN-MARSHALL DATA
    memcpy(&net_ack, buffer + offset, sizeof(net_ack));
    offset += sizeof(net_ack);

    // copy data to the class data types
    ack = ntohl(net_ack);
}
bool Acknowledgement::IsValid()
{
    if (ack > 0)
        return true;
    else
        return false;
}
void Acknowledgement::print()
{
    std::cout << "acknowledgement: " << ack << std::endl;
    std::cout << "############################################" << std::endl
              << std::endl;
}