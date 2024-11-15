# Windows Socket Sender
# Windows Socket Sender FTP

This project consists of a client-server architecture designed to facilitate file transfers and credential management. The current implementation uses a Command Line Interface (CLI) for the client, with plans to develop a more user-friendly graphical interface in the future. The backend client handles user credentials and communicates with the server, which manages connections and authentication.

## Client

The client is implemented in `CLI.cpp`. It allows users to save, load, and delete credentials, and perform file upload and download operations via FTP.

### Key Functions

- `saveCredentials`: Saves server, username, and password to a file.
- `loadCredentials`: Loads server, username, and password from a file.
- `deleteCredentials`: Deletes the credentials file.
- `CLI::start`: Main function to start the CLI, handle user inputs, and perform actions like upload, download, delete, and connect.

### Usage

1. Start the CLI: Run the client application.
2. Load Credentials: If credentials are saved, the user can choose to use them or delete them.
3. Enter New Credentials: If no credentials are loaded, the user is prompted to enter new ones.
4. Perform Actions: The user can upload, download, delete credentials, connect to a new server, or exit the program.

## Server

The server is implemented in `Server.cpp`. It listens for client connections, receives credentials, and performs basic authentication.

### Key Functions

- `Server::start`: Initializes Winsock, sets up the listening socket, accepts client connections, and handles received data.
- `Server::stop`: Stops the server.
- `Server::restart`: Restarts the server.

### Usage

1. Start the Server: Run the server application.
2. Listen for Connections: The server listens on a specified port for incoming client connections.
3. Authenticate Clients: The server receives and authenticates client credentials.

## Backend Client

The backend client is the entry point of the application, implemented in `Socket-sender-backend.cpp`. It starts the CLI and handles exceptions.

### Usage

1. Run the Application: Execute the backend client to start the CLI.
2. Handle Errors: Any exceptions are caught and displayed.

## Future Plans

The current CLI will be replaced with a more user-friendly graphical interface to enhance the user experience. The core functionality of managing credentials and file transfers will remain the same, but with a more intuitive and visually appealing interface.

## Conclusion

This project provides a robust foundation for managing file transfers and user credentials in a client-server architecture. The CLI serves as a functional prototype, with plans for a more sophisticated UI in the future. The server handles connections and authentication, ensuring secure communication between the client and server.
