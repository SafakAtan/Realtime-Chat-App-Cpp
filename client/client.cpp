// client.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    // Sunucu adı üzerinden DNS çözümleme (server, docker-compose.yml'deki sunucu ismi)
    server = gethostbyname("server");
    if (server == NULL) {
        std::cerr << "Sunucu bulunamadı" << std::endl;
        return -1;
    }

    // Socket oluştur
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket oluşturulamadı" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Sunucuya bağlan
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Bağlantı başarısız" << std::endl;
        return -1;
    }

    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << "Sunucudan mesaj: " << buffer << std::endl;

    close(sock);
    return 0;
}
