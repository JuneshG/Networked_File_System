#include "Server.hpp"
#include "RequestHandler.hpp" // Include the FileSystem header for file operations
#include <iostream> // For console output (like printing messages)
#include <stdexcept> // For exception handling (like catching errors)

void Server::handleClient(SOCKET clientSockt) { // Function to manage one client
    
    FileSystem fs("server_files/"); // Create a FileSystem object with the base directory "server_files/"
    UserManager um; // Create a UserManager object for user management (like the "security ledger")
    RequestHandler requestHandler(fs, um); // Create a RequestHandler object to process requests (like the "waiter" who takes orders)

    char buffer[1024]; // Buffer to store incoming data (like a notepad for taking orders)

    while (true) { // Loop to keep the connection open (like a restaurant keeping the table ready for orders)
        int bytesReceived = recv(clientSockt, buffer, sizeof(buffer), 0); // Receive data from the client (like taking an order)
        if (bytesReceived <= 0) { // Check if the connection is closed or an error occurred
            break; // Exit the loop if there's no data (client disconnected)
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received string (like finishing a sentence)
        std::string request(buffer); // Convert the buffer to a string (like writing down the order)

        std::string response = requestHandler.processRequest(request); // Process the request and get a response (like preparing the food)
        send(clientSockt, response.c_str(), response.size(), 0); // Send the response back to the client (like serving the food)
    }
    {
        /* code */
    }
    

}
