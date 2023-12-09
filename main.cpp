#include <iostream>
#include <winsock2.h>
int main() {
    WSADATA wsaData;
    WSADATA* ptr = &wsaData;
    int wsaerr = 0;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, ptr);
    if (wsaerr!= 0) {
        std::cout << "The winsock dll not found!" << '\n';
    } else {
        std::cout << "The winsock dll is found!" << '\n';
        std::cout << "The status: " << wsaData.szSystemStatus << '\n';
    }
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "ERROR at socket " << WSAGetLastError() << '\n';
        WSACleanup();
        return 0;
    } else {
        std::cout << "socket is ok!\n";
    }
    struct sockaddr_in serverAddr;
    int serverAddrSize = sizeof(serverAddr);
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientSocket, (sockaddr*)&serverAddr, serverAddrSize) == SOCKET_ERROR) {
        std::cout << "CLIENT CONNECT FAILED " << WSAGetLastError() << '\n';
        WSACleanup();
        return 0;
    } else {
        std::cout << "Client connection succeeded!\n";
    }

    char buffer[200];
    printf("Enter your message ");
    std::cin.getline(buffer, 200);
    int byteCount = send(clientSocket, buffer, 200, 0);
    if (byteCount != 200) {
        printf("Sent byte error! Sent %d bytes instead of 200\n", byteCount);
    }
    return 0;
}