#include "Server.h"
#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wininet.h>

#pragma comment(lib, "Ws2_32.lib")

namespace Server
{
    void Server::start()
    {
        WSADATA wsaData;
        SOCKET ListenSocket = INVALID_SOCKET;
        SOCKET ClientSocket = INVALID_SOCKET;
        struct addrinfo* result = NULL;
        struct addrinfo hints;
        int iResult;
        const char* port = "12345";

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            std::cerr << "WSAStartup failed: " << iResult << std::endl;
            return;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        iResult = getaddrinfo(NULL, port, &hints, &result);
        if (iResult != 0)
        {
            std::cerr << "getaddrinfo failed: " << iResult << std::endl;
            WSACleanup();
            return;
        }

        // Create a SOCKET for the server to listen for client connections
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET)
        {
            std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
            freeaddrinfo(result);
            WSACleanup();
            return;
        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }

        freeaddrinfo(result);

        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR)
        {
            std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }

        std::cout << "Server started. Listening on port: " << port << std::endl;

        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET)
        {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }

        std::cout << "Client connected." << std::endl;

        // Receive the username and password from the client
        std::vector<char> buffer(1024);
        iResult = recv(ClientSocket, buffer.data(), buffer.size(), 0);
        if (iResult > 0)
        {
            std::string receivedData(buffer.data(), iResult);
            std::cout << "Received data: " << receivedData << std::endl;

            // Assuming the format is "username:password"
            size_t delimiterPos = receivedData.find(':');
            if (delimiterPos != std::string::npos)
            {
                std::string username = receivedData.substr(0, delimiterPos);
                std::string password = receivedData.substr(delimiterPos + 1);

                std::cout << "Username: " << username << std::endl;
                std::cout << "Password: " << password << std::endl;

                // Here you can add your authentication logic
                if (username == "expectedUsername" && password == "expectedPassword")
                {
                    std::cout << "Authentication successful." << std::endl;
                }
                else
                {
                    std::cout << "Authentication failed." << std::endl;
                }
            }
        }
        else if (iResult == 0)
        {
            std::cout << "Connection closed by client." << std::endl;
        }
        else
        {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
        }

        // Cleanup
        closesocket(ClientSocket);
        closesocket(ListenSocket);
        WSACleanup();
    }

    void Server::stop()
    {
        // Stop the server
        std::cout << "Server stopped." << std::endl;
    }

    void Server::restart()
    {
        // Restart the server
        std::cout << "Server restarting..." << std::endl;
        stop();
        start();
    }
} // namespace Server
