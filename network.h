#ifndef NETWORK_H
#define NETWORK_H

void start_server();
void connect_to_peer(const char* ip, int port);
void broadcast_block(const char* block_data);

#endif
