// server.cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Forcefully attaching socket to the port 8080
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    const char *hello = "Hello from server";
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";
    
    close(new_socket);
    close(server_fd);
    return 0;
}
