#include "ServerPeers.h"

Peers::Peers(){
    u_id = -1;
    port = -1;

}

void Peers::SetPeerData(int uid, int prt, char *ip){
    uid = uid;
    port =prt;
    strcpy (IP_addr, ip);

}

int Peers::GetUID() {return u_id;}
int Peers::GetPort() {return port;}
void Peers::GetIP(char *buffer){
    strcpy(buffer, IP_addr);
}

bool Peers::IsValid(){
    if (u_id == -1)
        return false;
    else
        return true;
}