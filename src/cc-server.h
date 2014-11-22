#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <enet/enet.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm.h>
#include <unistd.h>
#include <time.h>

struct client {
    uint32_t id;
    char *name;
    int ip_version;
    uint64_t ipv6_addr[2];
    uint32_t ipv4_addr;
    int port;
    void *sock_c2s;
    void *sock_s2c;
};

class CC_Server {
  private:
    uint32_t nClients;
    struct client clients[256];
    void *config;
    void *commands;
    void process_pkg(ENetEvent *evt);

  public:
    CC_Server(int ip_version, uint64_t ipv6_addr[2], uint32_t ipv4_addr, int port);
    ~CC_Server();
    void read_config(char *name);
    void connect(client *cli);
    void disconnect(client *cli);
}
