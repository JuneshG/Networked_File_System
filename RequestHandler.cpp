// RequestHandler.cpp
#include "RequestHandler.hpp"
#include <sstream>    // for std::istringstream
#include <algorithm>    // for std::transform
#include <cctype>       // for std::toupper
#include <filesystem>   // for std::filesystem::create_directories

// Constructor: just store references to FileSystem and UserManager
RequestHandler::RequestHandler(FileSystem& fs_, UserManager& um_)
  : fs(fs_), um(um_)
{}

// processRequest: parse the command, dispatch to fs or um, return a response
std::string RequestHandler::processRequest(const std::string& request) {
    std::istringstream iss(request);
    std::string cmd;
    iss >> cmd;
    if (cmd.empty()) return "";   // silently ignore blank

    // uppercase the command for case‐insensitive matching
    std::transform(cmd.begin(), cmd.end(), cmd.begin(),
                   [](unsigned char c){ return std::toupper(c); });

    if (cmd == "CREATE_DIR") {
        std::string dir;
        iss >> dir;
        // use create_directories, which won't error if it already exists
        try {
            std::filesystem::create_directories("server_files/" + dir);
            return "OK\n";
        }
        catch (const std::filesystem::filesystem_error&) {
            return "ERR_CREATE\n";
        }
    }
    else if (cmd == "DELETE_DIR") {
        std::string dir;
        iss >> dir;
        try {
            std::filesystem::remove_all("server_files/" + dir);
            return "OK\n";
        }
        catch (const std::filesystem::filesystem_error&) {
            return "ERR_DELETE\n";
        }
    }
    
    else if (cmd == "WRITE_FILE") {
        std::string filename;
        iss >> filename;
        std::string content;
        std::getline(iss, content);
        if (!content.empty() && content[0] == ' ')
            content.erase(0,1);
        return fs.writeFile(filename, content) ? "OK\n" : "ERR_WRITE\n";
    }
    else if (cmd == "LIST_FILES") {
        std::string dir; 
        iss >> dir;
        return fs.listFiles(dir);
    }
    else if (cmd == "REGISTER") {
        std::string user, pass;
        iss >> user >> pass;
        return um.registerUser(user, pass) ? "OK\n" : "ERR_USER_EXISTS\n";
    }
    else if (cmd == "LOGIN") {
        std::string user, pass;
        iss >> user >> pass;
        return um.login(user, pass) ? "OK\n" : "ERR_LOGIN\n";
    }

    else if (cmd == "DELETE_FILE") {
        std::string filename;
        iss >> filename;
        return fs.deleteFile(filename) ? "OK\n" : "ERR_DELETE_FILE\n";
    }

    
    return "ERR_UNKNOWN_CMD\n";
}
