#include "cc-server.h"

CC_Server::CC_Server(int ip_version, uint64_t ipv6_addr[2], uint32_t ipv4_addr, int port) {
    if (enet_initialize()) {
         fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    
    ENetAddress address;
    ENetHost *server;
    address.host = ENET_HOST_ANY;
    address.port = port;
    
    server = enet_host_create(&address, 256, 2, 0, 0);
    
    if (server == NULL) {
        fprintf(stderr, "Cannot create enet server host")
        exit(EXIT_FAILURE);
    }
    
    
    
    enet_host_destroy(server);
}
