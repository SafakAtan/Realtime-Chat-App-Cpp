#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>

void receive_messages(int sock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(sock, buffer, sizeof(buffer));
        if (valread > 0) {
            std::cout << "Message from server: " << buffer << std::endl;
        } else {
            std::cerr << "Connection closed or read error." << std::endl;
            break;
        }
    }
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct addrinfo hints, *res;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Resolve the server address
    int status = getaddrinfo("server", "8080", &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return -1;
    }

    // Create socket
    if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        std::cerr << "Socket creation failed." << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        std::cerr << "Connection error." << std::endl;
        return -1;
    }

    std::cout << "Connected to the server!" << std::endl;

    freeaddrinfo(res);

    // Create a thread for receiving messages
    std::thread receiver(receive_messages, sock);
    receiver.detach(); // Run the thread separately

    // Message sending loop
    while (true) {
        std::string message;
        std::cout << "Enter your message (type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        send(sock, message.c_str(), message.size(), 0);
    }

    close(sock);
    return 0;
}
