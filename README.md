# Windows Socket Sender

A Windows C++/C application with functionality to send files quickly over the network from one computer to another. No bloat, no compromises.

## Description

This is a simple Command Line Interface where you can quickly send files over the network via TCP to an FTP server listening on standard port 21.

TODO:
- This is a simple WinUI 3 Application where you can send files from one computer to another using sockets on Windows.

A solution to set up a server-client setup from computer to computer over the network is to have an FTP intermediate server that receives a file from a client and sends it to the receiver (another user/client).

### Option 1: Direct Connection with Port Forwarding

1. Port Forwarding: Configure the router on the server's network to forward the FTP port (usually port 21 for control commands and a range of ports for data transfer) to the internal IP address of the server machine.
2. Public IP Address: The client needs to know the public IP address of the server's network. This can be found by searching "What is my IP" in a web browser on the server machine.
3. Firewall Configuration: Ensure that the firewall on the server machine and the router allows incoming connections on the specified FTP port(s).
4. FTP Server Software: Install and configure FTP server software on the server machine (e.g., FileZilla Server, vsftpd).
5. Client Connection: The client connects to the server using an FTP client (e.g., FileZilla Client) with the server's public IP address and the forwarded port.

### Option 2: Using an Intermediate FTP Server

1. Setup FTP Server: Set up an FTP server on a machine that is accessible from both the client and the server. This could be a cloud-based server or a dedicated FTP server.
2. Upload Files to FTP Server: The client uploads files to the FTP server using an FTP client.
3. Download Files from FTP Server: The server machine downloads files from the FTP server using an FTP client or custom software.

Example of Direct Connection with Port Forwarding - Server Setup

1. Port Forwarding: Forward port 21 (and a range of ports for data transfer) to the internal IP address of the server machine.
2. Install FTP Server Software: Install and configure FTP server software (e.g., FileZilla Server).