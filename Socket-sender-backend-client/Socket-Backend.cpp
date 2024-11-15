#include "Socket-Backend.h"
#include "main.h"

namespace FTP
{
	void uploadToFtp( std::string& server,  std::string& username,  std::string& password, std::string& filename) {
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

			// Get extended error information
			DWORD dwExtendedError;
			char szErrorBuffer[256];
			DWORD dwBufferLength = sizeof(szErrorBuffer);
			if (InternetGetLastResponseInfoA(&dwExtendedError, szErrorBuffer, &dwBufferLength)) {
				printf("Extended error information: %s\n", szErrorBuffer);
			}
			else {
				printf("Failed to get extended error information.\n");
			}

			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			return;
		}
		printf("FtpOpenFile succeeded.\n");

		const char* buffer = "this is a test";
		DWORD bytesWritten;
		BOOL result = InternetWriteFile(hFtpFile, buffer, (DWORD)strlen(buffer), &bytesWritten);
		if (!result) {
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
		printf("File uploaded successfully to FTP server at location: /test.txt\n");

	}

	void requestFromFtp( std::string& server,  std::string& username,  std::string& password, std::string& filename) {
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

			// Get extended error information
			DWORD dwExtendedError;
			char szErrorBuffer[256];
			DWORD dwBufferLength = sizeof(szErrorBuffer);
			if (InternetGetLastResponseInfoA(&dwExtendedError, szErrorBuffer, &dwBufferLength)) {
				printf("Extended error information: %s\n", szErrorBuffer);
			}
			else {
				printf("Failed to get extended error information.\n");
			}

			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			return;
		}
		printf("FtpOpenFile succeeded.\n");

		char buffer[256];
		DWORD bytesRead;
		BOOL result = InternetReadFile(hFtpFile, buffer, sizeof(buffer), &bytesRead);
		if (!result) {
			printf("InternetReadFile failed with error: %d\n", GetLastError());
			InternetCloseHandle(hFtpFile);
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			return;
		}
		printf("InternetReadFile succeeded. Bytes read: %ld\n", bytesRead);

		InternetCloseHandle(hFtpFile);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		printf("Handles closed successfully.\n");

		buffer[bytesRead] = '\0';
		printf("Read data: %s\n", buffer);

	}


}
