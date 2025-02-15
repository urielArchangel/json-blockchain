#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

void* handle_client(void* socket_desc) {
    int sock = *(int*)socket_desc;
    char message[1024];
    read(sock, message, 1024);
    printf("Received Block: %s\n", message);
    close(sock);
    free(socket_desc);
    return NULL;
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server listening on port %d...\n", PORT);
    while ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))) {
        pthread_t thread;
        int* new_sock = malloc(sizeof(int));
        *new_sock = new_socket;
        pthread_create(&thread, NULL, handle_client, (void*)new_sock);
    }
}

void connect_to_peer(const char* ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == 0) {
        printf("Connected to peer %s:%d\n", ip, port);
    }
    close(sock);
}

void broadcast_block(const char* block_data) {
    connect_to_peer("127.0.0.1", PORT);
    printf("Broadcasting Block: %s\n", block_data);
}
