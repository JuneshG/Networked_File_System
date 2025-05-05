#include "FileSystem.hpp"

#include <filesystem>
// namespace fs = std::experimental::filesystem;

#include <fstream> // For file operations (like reading/writing files)
#include <iostream> // For console output (like printing messages)
#include <string> // For string operations (like std::string)



FileSystem::FileSystem(const std::string& baseDir) : baseDir(baseDir) { // Constructor to initialize the base directory for file operations
    fs::create_directories(baseDir); // Create the base directory if it doesn't exist (like setting up the "filing cabinet" for the first time)
    // This ensures that the base directory is ready for use. If the "filing cabinet" doesn't exist, create it.     
}

bool FileSystem::createDirectory(const std::string& dirName) {  // Create a new directory (folder) in the base directory (like adding a new drawer to the "filing cabinet")
    // Combine base directory + directory name (e.g., "server_files/documents/")
    return fs::create_directory(baseDir + dirName); // Create the directory (like adding a new drawer to the "filing cabinet")
}


bool FileSystem::writeFile(const std::string& filename, const std::string& content) { // Write content to a file (like typing into a document)
    // Check if the filename is valid (like checking if the document name is correct)
    // Combine base directory + filename (e.g., "server_files/notes.txt")
    std::string fullPath = baseDir + filename;

    // Open the file in write mode (like creating a new document)
    std::ofstream file(fullPath);

    // Check if the file opened successfully
    if (file.is_open()) {
        // Write content to the file (like typing into the document)
        file << content;
        // Close the file (save and close)
        file.close();
        return true; // Success!
    }
    return false; // Failed to open the file
}

std::string FileSystem::listFiles(const std::string& dirName) { // List all files in a directory (like checking the contents of a drawer)
    // Check if the directory name is valid (like checking if the drawer name is correct)
    // Combine base directory + directory name (e.g., "server_files/documents/")
    std::string fullPath = baseDir + dirName; // Full path to the directory
    // Check if the directory exists (like checking if the drawer is there) 
    // String to hold the list of files (like a text list)
    std::string filesList;  // Initialize an empty string to hold the list of files
    // Check if the directory exists

    // Loop through all files in the directory (like scrolling through files in Explorer)
    for (const auto& entry : fs::directory_iterator(fullPath)) {
        // Add each filename to the list
        filesList += entry.path().filename().string() + "\n";
    }

    return filesList; // Return the list (e.g., "file1.txt\nfile2.txt\n")
}

bool FileSystem::deleteFile(const std::string& filename) {
    // Combine base directory + filename (e.g., "server_files/notes.txt")
    std::string fullPath = baseDir + filename; // Full path to the file

    // Check if the file exists and delete it (like removing a document from the drawer)
    return fs::remove(fullPath); // Remove the file (like throwing away a document)
}

// int main() {
//     FileSystem fs("server_files/"); // Create a FileSystem object // Sets up the "filing cabinet" location

//     // Test createDirectory()
//     fs.createDirectory("documents"); // Creates "server_files/documents"

//     // Test writeFile()
//     fs.writeFile("documents/notes.txt", "Hello World"); // Creates "notes.txt"

//     // Test listFiles()
//     std::string files = fs.listFiles("documents");
//     std::cout << "Files in 'documents':\n" << files << std::endl;

//     return 0;
// }

