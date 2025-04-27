// FileSystem.hpp
#pragma once // Prevent this header from being included multiple times (like a "do not duplicate" stamp)

//include necessary libraries for string and file system operations
#include <string> // Standard C++ library for string manipulation (like std::string(text handling)) 
#include <filesystem>
namespace fs = std::filesystem;

class FileSystem { // Class definition for file system operations and its functionalities and data members and methods
private: // Private members of the class
    std::string baseDir; // Root folder for all operations (e.g., "server_files/" acts like a "filing cabinet"). The base directory where all files are stored. This is like the main folder where all the files are kept.

public:
    // Constructor: Called when creating a FileSystem object (e.g., FileSystem fs("server_files/");)
    FileSystem(const std::string& baseDir); // Constructor to initialize the base directory for file operations. The "filing cabinet" where all files are stored. Sets up the "filing cabinet" location

    //Public method (tools users can interact with):

    bool createDirectory(const std::string& dirName); // Creates a directory (folder) in the base directory. Like adding a new drawer to the "filing cabinet" for organizing files. The "drawer" where files are stored.
    bool writeFile(const std::string& filename,        // Adds a "file" to a drawer
        const std::string& content);        // (like putting a document in a folder)
std::string listFiles(const std::string& dirName); // Lists all "files" in a drawer (like an inventory list)
};