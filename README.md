# Windows Socket Sender FTP

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/mbn-code/Windows-Socket-Sender-FTP)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](#)
[![Issues](https://img.shields.io/github/issues/mbn-code/Windows-Socket-Sender-FTP)](https://github.com/mbn-code/Windows-Socket-Sender-FTP/issues)

A modern, easy-to-use FTP client for Windows that allows you to transfer files quickly and reliably.

[Watch Demo Video](https://www.youtube.com/watch?v=KvRyteNzrcI)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Basic Usage](#basic-usage)
  - [Example Commands](#example-commands)
- [Error Handling](#error-handling)
- [Security Notes](#security-notes)
- [Contributing](#contributing)
- [License](#license)
- [FAQ](#faq)
- [Support](#support)
- [Acknowledgments](#acknowledgments)
- [Contact](#contact)

## Overview

This application provides a straightforward way to transfer files using the FTP protocol with a clean command-line interface. Built with C++, it offers robust file transfer capabilities while maintaining simplicity in usage.

## Features

- Simple command-line interface
- Secure file uploads and downloads
- Password-protected connections
- Progress tracking for file transfers
- Error handling with clear messages
- Support for passive FTP mode
- Compatible with standard FTP servers

## Getting Started

### Prerequisites

- Windows operating system
- [Visual C++ Redistributable (Latest Version)](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)

### Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/mbn-code/windows-socket-sender-ftp.git
   ```
2. **Navigate to the Project Directory**
   ```bash
   cd Windows-Socket-Sender-FTP
   ```
3. **Build the Application**
   - Open the solution file in Visual Studio.
   - Build the solution in Release mode.
4. **Run the Executable**
   - Navigate to the `Release` folder.
   - Run the executable from the command line:
     ```bash
     WindowsSocketSenderFTP.exe
     ```

### Basic Usage

1. **Open the Application**
   ```bash
   WindowsSocketSenderFTP.exe
   ```
2. **Enter Your FTP Server Details**
   - **Server Address**
   - **Username**
   - **Password**
3. **Select Your Operation**
   - Type `upload` or `download` when prompted.
4. **Choose Your File(s)**
   - TODO: Provide the path to the file(s) you wish to transfer. ATM: It's hardcoded.
5. **Monitor the Transfer Progress**
   - Progress will be displayed in the command line interface.

### Example Commands

- **Upload a File to the Server**
  ```bash
  upload
  ```
- **Download a File from the Server**
  ```bash
  download
  ```
- **Delete Saved Server Credentials**
  ```bash
  delete
  ```
- **Connect to a New Server with New Credentials**
  ```bash
  connect
  ```
- **Exit the Program**
  ```bash
  exit
  ```

## Error Handling

The application provides clear error messages if something goes wrong:

- **Connection Issues**
  - Unable to reach the server.
- **Authentication Failures**
  - Incorrect username or password.
- **File Transfer Problems**
  - Issues during upload or download.
- **Server Response Errors**
  - Unexpected responses from the FTP server.

## Security Notes

- All passwords are handled securely.
- Supports standard FTP security measures.
- Implements proper connection encryption when available.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## FAQ

**Q:** Does this application support SFTP?

**A:** Currently, only standard FTP is supported. SFTP support is planned for a future release.

**Q:** Can I transfer multiple files at once?

**A:** Yes, you can specify multiple files or directories to transfer.

**Q:** How do I enable passive mode?

**A:** The application uses passive mode by default. No additional configuration is needed.

## Support

For support, please open an [issue](https://github.com/mbn-code/Windows-Socket-Sender-FTP/issues)

## Acknowledgments

- **[Winsock API](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)** - For network communication
- **[Visual Studio](https://visualstudio.microsoft.com/)** - Development environment

## Contact

Created by [@mbn-code](https://github.com/mbn-code) - feel free to contact me!
