// #include <BulletDynamics/btBulletDynamicsCommon.h>
#include <enet/enet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <time.h>

#define HOST "localhost"
#define PORT 0xCC00

struct cc_client {
    uint32_t id;
    char *name;
    int ip_version;
    uint64_t ipv6_addr[2];
    uint32_t ipv4_addr;
    ENetPeer *peer;
    ENetHost *server;
    ENetAddress address;
};

class CC_Server {
  private:
    ENetPeer *peer;
    ENetHost *server;
    ENetAddress address;
    ENetEvent evt;
    uint32_t nClients;
    std::vector<cc_client *> clients;
    void *config;
    void *commands;
    void process_pkg(ENetEvent evt);

  public:
    CC_Server(int ip_version, uint64_t ipv6_addr[2], uint32_t ipv4_addr, int port);
    ~CC_Server();
    void read_config(char *name);
    void connect(cc_client *cli);
    void disconnect(cc_client *cli);
    void loop();
};
