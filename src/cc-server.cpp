#include "cc-server.h"

CC_Server::CC_Server(int ip_version, uint64_t ipv6_addr[2], uint32_t ipv4_addr, int port) {
    if (enet_initialize()) {
         fprintf(stderr, "An error occurred while initializing ENet.\n");
        //return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    
    //~ enet_address_set_host(&address, HOST);
    address.host = 0x00000000;
    //~ address.host = ENET_HOST_ANY;
    address.port = PORT;
    
    server = enet_host_create(&address, 256, 2, 0, 0);
    
    if (server == NULL) {
        fprintf(stderr, "Cannot create enet server host\n");
        exit(EXIT_FAILURE);
    } else {
        uint8_t o1, o2, o3, o4;
        o4 = (address.host & 0xFF000000) >> 24;
        o3 = (address.host & 0xFF0000) >> 16;
        o2 = (address.host & 0xFF00) >> 8;
        o1 = (address.host & 0xFF);
        fprintf(stderr, "Started server at [%s] %u.%u.%u.%u:%u\n", HOST, o1, o2, o3, o4, PORT);
    }
}

CC_Server::~CC_Server() {
    printf("Server quit\n");
    enet_host_destroy(server);
}

void CC_Server::disconnect(cc_client *cli) {
    peer = cli->peer;
    enet_peer_disconnect(peer, 0);
    
    while (enet_host_service(server, &evt, 3000) > 0) {
        switch (evt.type) {
          case ENET_EVENT_TYPE_NONE:
            break;
        
          case ENET_EVENT_TYPE_DISCONNECT:
            printf("Client disconnected\n");
            return;
        
          default:
            enet_packet_destroy(evt.packet);
            break;
        }
    }
    
    printf("Timeout reached, resetting peer\n");
    enet_peer_reset(peer);
}

void CC_Server::loop() {
    while (enet_host_service(server, &evt, 1000) > 0) {
        switch (evt.type) {
          case ENET_EVENT_TYPE_CONNECT:
            uint8_t o1, o2, o3, o4;
            o4 = (evt.peer->address.host & 0xFF000000) >> 24;
            o3 = (evt.peer->address.host & 0x00FF0000) >> 16;
            o2 = (evt.peer->address.host & 0x0000FF00) >> 8;
            o1 = (evt.peer->address.host & 0x000000FF);
            printf("A client connects! %u.%u.%u.%u:%u\n",
                    o1, o2, o3, o4,
                    evt.peer -> address.port);
            evt.peer->data = strdup("event.peer.data");
            break;
        
          case ENET_EVENT_TYPE_DISCONNECT:
            printf("%x:%u disconnected\n",
                    evt.peer -> address.host,
                    evt.peer -> address.port);
            evt.peer -> data = NULL;
            break;
        
          case ENET_EVENT_TYPE_RECEIVE:
            //~ printf("Received a packet (%u bytes) from %x:%u on channel %u:\n%s\n",
                    //~ evt.packet->dataLength,
                    //~ evt.peer -> address.host,
                    //~ evt.peer -> address.port,
                    //~ evt.channelID,
                    //~ evt.packet -> data);
            this->process_pkg(evt);
            enet_packet_destroy(evt.packet);
            break;
        
          default:
            printf("Nothing happened.\n");
            break;
        }
    }
}

void CC_Server::process_pkg(ENetEvent event) {
    ENetPacket *packet = event.packet;
    if (packet->data[0] == 'B') {
        printf("(%x:%u) c2a: %s\n", event.peer->address.host, event.peer->address.port, packet->data);
        ENetPacket *p = enet_packet_create(packet->data+1, packet->dataLength, ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(server, 1, p);
        enet_host_flush(server);
    } else {
        printf("(%x:%u) c2s: %s\n", evt.peer->address.host, evt.peer->address.port, packet->data);
    }
}

int main(int argc, char **argv, char **envp) {
    uint64_t ipv6_addr[2] = {0, 0};
    uint32_t ipv4_addr = 0x00000000;
    CC_Server *srv = new CC_Server(4, ipv6_addr, ipv4_addr, 0xCC00);
    while(1) srv->loop();
    
    return 0;
}
