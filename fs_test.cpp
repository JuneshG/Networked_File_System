// fs_test.cpp
#include <iostream>
#include "FileSystem.hpp"

int main() {
    std::cout << std::boolalpha;   // print true/false

    // 1) Point at a folder on disk (it will be created if needed)
    FileSystem fs("server_data/"); // Create a FileSystem object with the base directory "server_data/"
    // This sets up the "filing cabinet" location where all files will be stored.

    // 2) Test createDirectory
    bool ok = fs.createDirectory("documents"); // Create a new directory named "documents" in the base directory
    // This is like adding a new drawer to the "filing cabinet" for organizing files.
    std::cout << "createDirectory(\"documents\"): " << ok << "\n";  // Print the result of the directory creation (true/false)

    // 3) Test writeFile
    ok = fs.writeFile("documents/notes.txt", "Hello, CloudFS!"); // Write content to a file named "notes.txt" in the "documents" directory
    // This is like typing into a document and saving it in the drawer.
    std::cout << "writeFile(\"documents/notes.txt\"): " << ok << "\n";  // Print the result of the file writing (true/false)

    // 4) Test listFiles
    std::string listing = fs.listFiles("documents"); // List all files in the "documents" directory
    // This is like checking the contents of the drawer to see what files are there.
    std::cout << "listFiles(\"documents\"):\n" << listing << "\n"; // Print the list of files in the "documents" directory


    return 0;
}
