#include "pch.h"
#include "MainWindow.xaml.h"
#include <iostream>
#include <fstream>
#include <string>

bool connected = false;


#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::windows_socket_sender::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::FileSenderButton(IInspectable const&, RoutedEventArgs const&)
    {
		sendButton().Content(box_value(L"Sending.."));

		// if ftp is done sending and has sent via TCP make the button say "Sent"

    }

    void MainWindow::ConnectButtonFTP(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        connectButton().Content(box_value(L"Connecting.."));

        // connect to FTP server

        // init socket
        WSADATA wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo * result = NULL;
        struct addrinfo * ptr = NULL;
		struct addrinfo hints = { 0 };

        int iResult;

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            std::wcout << L"WSAStartup failed with error: " << iResult << std::endl;
            connectButton().Content(box_value(L"Failed"));
            return;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = getaddrinfo("ftp.example.com", "21", &hints, &result);
        if (iResult != 0) {
            std::wcout << L"getaddrinfo failed with error: " << iResult << std::endl;
            WSACleanup();
            connectButton().Content(box_value(L"Failed"));
            return;
        }

        // Attempt to connect to an address until one succeeds
        for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

            // Create a SOCKET for connecting to server
            ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET) {
                std::wcout << L"Socket failed with error: " << WSAGetLastError() << std::endl;
                WSACleanup();
                connectButton().Content(box_value(L"Failed"));
                return;
            }

            // Connect to server.
            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result);

        if (ConnectSocket == INVALID_SOCKET) {
            std::wcout << L"Unable to connect to server!" << std::endl;
            WSACleanup();
            connectButton().Content(box_value(L"Failed"));
            return;
        }

        connected = true;

        // if TCP connection is successful make the button say "Connected" else "Failed" together with error message
        if (connected)
        {
            connectButton().Content(box_value(L"Connected"));
        }
        else
        {
            connectButton().Content(box_value(L"Failed"));
        }
    }
}
