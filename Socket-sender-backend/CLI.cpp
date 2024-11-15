#include "CLI.h"
#include "Socket-Backend.h"
#include <iostream>
#include <fstream>
#include <string>

void saveCredentials(const std::string& server, const std::string& username, const std::string& password) {
    std::ofstream outFile("credentials.txt");
    if (outFile.is_open()) {
        outFile << server << std::endl;
        outFile << username << std::endl;
        outFile << password << std::endl;
        outFile.close();
    }
}

bool loadCredentials(std::string& server, std::string& username, std::string& password) {
    std::ifstream inFile("credentials.txt");
    if (inFile.is_open()) {
        std::getline(inFile, server);
        std::getline(inFile, username);
        std::getline(inFile, password);
        inFile.close();
        return true;
    }
    return false;
}

void deleteCredentials() {
    std::remove("credentials.txt");
}

void CLI::start() {
    std::string role;
    std::cout << "Are you a client or server? (client/server): ";
    std::getline(std::cin, role);

    if (role == "server") {
        // Server-specific logic here
        std::cout << "Server mode selected. Implement server logic here." << std::endl;
        return;
    }
    else if (role != "client") {
        std::cout << "Invalid role. Exiting." << std::endl;
        return;
    }

    std::string server, username, password;
    bool credentials_loaded = loadCredentials(server, username, password);

    if (credentials_loaded) {
        std::string useOldCredentials;
        std::cout << "Do you want to connect to the latest server with saved credentials? (yes/no): ";
        std::getline(std::cin, useOldCredentials);

        if (useOldCredentials == "no") {
            deleteCredentials();
            credentials_loaded = false;
        }
    }

    if (!credentials_loaded) {
        std::cout << "Enter server: ";
        std::getline(std::cin, server);
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        std::string saveOption;
        std::cout << "Do you want to save these credentials for future use? (yes/no): ";
        std::getline(std::cin, saveOption);

        if (saveOption == "yes") {
            saveCredentials(server, username, password);
        }
    }

    std::string input;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);

        if (input == "upload") {
            std::string filename = "test.txt";
            FTP::uploadToFtp(server, username, password, filename);
        }
        else if (input == "download") {
            std::string filename = "test.txt";
            FTP::requestFromFtp(server, username, password, filename);
        }
        else if (input == "delete") {
            std::string confirmation;

            std::cout << "!! You are about to do an action that can't be reversed, would you like to continue?" << '\n';

            std::cin >> confirmation;

            if (confirmation == "yes") {
                std::cout << "Are you sure you want to delete the credentials for the latest server you connected to?!" << '\n';

                deleteCredentials();
                std::cout << "Credentials deleted." << '\n';
            }
        }
        else if (input == "connect") {
            std::string confirmation;

            std::cout << "!! You are about to do an action that can't be reversed, would you like to continue?" << '\n';

            std::cin >> confirmation;

            if (confirmation == "yes") {
                deleteCredentials();
                start();
                break;
            }
        }
        else if (input == "help") {
            std::cout << "Commands: " << '\n';
            std::cout << "upload - Upload a file to the server" << '\n';
            std::cout << "download - Download a file from the server" << '\n';
            std::cout << "delete - Delete the credentials for the latest server you connected to" << '\n';
            std::cout << "connect - Connect to a new server with new credentials" << '\n';
            std::cout << "exit - Exit the program" << '\n';
        }
        else if (input == "exit") {
            break;
        }
        std::cout << "You entered: " << input << '\n';
    }
}
