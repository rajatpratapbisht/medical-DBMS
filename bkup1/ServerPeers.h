
#ifndef __SERVER_PEERS_H__
#define __SERVER_PEERS_H__

#include <cstring>

class Peers{
    private:
    int u_id;
    int port;
    char IP_addr[16];

    public:

    Peers();
    void operator = (const Peers &peers){
        u_id = peers.u_id;
        port = peers.port;
        strcpy(IP_addr, peers.IP_addr);
    }
    void SetPeerData(int uid, int prt, char *ip );

    int GetUID();
    int GetPort();
    void GetIP(char * buffer);

    bool IsValid();

}typedef Peers_t;




#endif