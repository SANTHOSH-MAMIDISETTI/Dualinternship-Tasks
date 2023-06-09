#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);  // Use desired port
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any network interface

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Failed to listen for connections." << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection." << std::endl;
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        std::cerr << "Failed to read data from socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Received message from client: " << buffer << std::endl;

    const char *response = "Hello from server!";
    int bytesWritten = write(clientSocket, response, strlen(response));
    if (bytesWritten == -1) {
        std::cerr << "Failed to write data to socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}
// lsof -i :8080
