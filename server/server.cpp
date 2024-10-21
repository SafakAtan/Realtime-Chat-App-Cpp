#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

std::vector<int> clients; // Vector to hold client sockets

void handle_client(int client_socket) {
    char buffer[1024];
    int valread;

    while ((valread = read(client_socket, buffer, sizeof(buffer))) > 0) {
        buffer[valread] = '\0'; // Null terminate the buffer
        std::cout << "Message received: " << buffer << std::endl;

        // Send the message to all clients
        for (int client : clients) {
            if (client != client_socket) { // Do not send to the sender
                send(client, buffer, strlen(buffer), 0);
            }
        }
    }

    // Remove the client from the list when done
    std::cout << "Client disconnected." << std::endl;
    clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed." << std::endl;
        return -1;
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Set socket options failed." << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Binding failed." << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listening failed." << std::endl;
        return -1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    while (true) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Accept failed." << std::endl;
            return -1;
        }

        std::cout << "New client connected." << std::endl;
        clients.push_back(new_socket); // Add new client to the list

        // Create a new thread to handle the client
        std::thread(handle_client, new_socket).detach();
    }

    return 0;
}
