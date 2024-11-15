#ifndef SOCKET_BACKEND_H
#define SOCKET_BACKEND_H

#include <string>

namespace FTP {
    void uploadToFtp( std::string& server,  std::string& username,  std::string& password,  std::string& filename);
    void requestFromFtp( std::string& server,  std::string& username,  std::string& password,  std::string& filename);
}

#endif // SOCKET_BACKEND_H
