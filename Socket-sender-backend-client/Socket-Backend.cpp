#include "Socket-Backend.h"
#include "main.h"
#include <fstream>
#include <vector>

namespace FTP {
    void uploadToFtp(std::string& server, std::string& username, std::string& password, std::string& filename) {
        // Open the file to upload
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            printf("Failed to open local file: %s\n", filename.c_str());
            return;
        }

        std::vector<char> fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        HINTERNET hInternet = InternetOpenA("FTP", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet == NULL) {
            printf("InternetOpen failed with error: %d\n", GetLastError());
            return;
        }
        printf("InternetOpen succeeded.\n");

        HINTERNET hConnect = InternetConnectA(hInternet, server.c_str(), INTERNET_DEFAULT_FTP_PORT, username.c_str(), password.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
        if (hConnect == NULL) {
            printf("InternetConnect failed with error: %d\n", GetLastError());
            InternetCloseHandle(hInternet);
            return;
        }
        printf("InternetConnect succeeded.\n");

        HINTERNET hFtpFile = FtpOpenFileA(hConnect, filename.c_str(), GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY, 0);
        if (hFtpFile == NULL) {
            DWORD dwError = GetLastError();
            printf("FtpOpenFile failed with error: %d\n", dwError);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return;
        }
        printf("FtpOpenFile succeeded.\n");

        DWORD bytesWritten;
        BOOL result = InternetWriteFile(hFtpFile, fileContents.data(), (DWORD)fileContents.size(), &bytesWritten);
        if (!result || bytesWritten != fileContents.size()) {
            printf("InternetWriteFile failed with error: %d\n", GetLastError());
            InternetCloseHandle(hFtpFile);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return;
        }
        printf("InternetWriteFile succeeded. Bytes written: %ld\n", bytesWritten);

        InternetCloseHandle(hFtpFile);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        printf("Handles closed successfully.\n");
        printf("File uploaded successfully to FTP server at location: /%s\n", filename.c_str());
    }

    void requestFromFtp(std::string& server, std::string& username, std::string& password, std::string& filename) {
        HINTERNET hInternet = InternetOpenA("FTP", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet == NULL) {
            printf("InternetOpen failed with error: %d\n", GetLastError());
            return;
        }
        printf("InternetOpen succeeded.\n");

        HINTERNET hConnect = InternetConnectA(hInternet, server.c_str(), INTERNET_DEFAULT_FTP_PORT, username.c_str(), password.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
        if (hConnect == NULL) {
            printf("InternetConnect failed with error: %d\n", GetLastError());
            InternetCloseHandle(hInternet);
            return;
        }
        printf("InternetConnect succeeded.\n");

        HINTERNET hFtpFile = FtpOpenFileA(hConnect, filename.c_str(), GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, 0);
        if (hFtpFile == NULL) {
            DWORD dwError = GetLastError();
            printf("FtpOpenFile failed with error: %d\n", dwError);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return;
        }
        printf("FtpOpenFile succeeded.\n");

        char buffer[1024];
        DWORD bytesRead;
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile.is_open()) {
            printf("Failed to open local file for writing: %s\n", filename.c_str());
            InternetCloseHandle(hFtpFile);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return;
        }

        while (true) {
            BOOL result = InternetReadFile(hFtpFile, buffer, sizeof(buffer), &bytesRead);
            if (!result) {
                printf("InternetReadFile failed with error: %d\n", GetLastError());
                outFile.close();
                InternetCloseHandle(hFtpFile);
                InternetCloseHandle(hConnect);
                InternetCloseHandle(hInternet);
                return;
            }
            if (bytesRead == 0) break; // EOF

            outFile.write(buffer, bytesRead);
        }
        outFile.close();

        printf("InternetReadFile succeeded.\n");
        InternetCloseHandle(hFtpFile);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        printf("Handles closed successfully.\n");
        printf("File downloaded successfully from FTP server to local file: %s\n", filename.c_str());
    }
}
