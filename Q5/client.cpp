#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);  // Use the same port as the server
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Connection failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    const char *message = "Hello from client!";
    int bytesWritten = write(clientSocket, message, strlen(message));
    if (bytesWritten == -1) {
        std::cerr << "Failed to write data to socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        std::cerr << "Failed to read data from socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Received response from server: " << buffer << std::endl;

    close(clientSocket);

    return 0;
}
