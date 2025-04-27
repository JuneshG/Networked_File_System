// fs_test.cpp
#include <iostream>
#include "FileSystem.hpp"

int main() {
    std::cout << std::boolalpha;   // print true/false

    // 1) Point at a folder on disk (it will be created if needed)
    FileSystem fs("server_data/");

    // 2) Test createDirectory
    bool ok = fs.createDirectory("documents");
    std::cout << "createDirectory(\"documents\"): " << ok << "\n";

    // 3) Test writeFile
    ok = fs.writeFile("documents/notes.txt", "Hello, CloudFS!");
    std::cout << "writeFile(\"documents/notes.txt\"): " << ok << "\n";

    // 4) Test listFiles
    std::string listing = fs.listFiles("documents");
    std::cout << "listFiles(\"documents\"):\n" << listing << "\n";

    return 0;
}
