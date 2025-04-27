// RequestHandler.cpp
#include "RequestHandler.hpp"
#include <sstream>    // for std::istringstream

// Constructor: just store references to FileSystem and UserManager
RequestHandler::RequestHandler(FileSystem& fs_, UserManager& um_)
  : fs(fs_), um(um_)
{}

// processRequest: parse the command, dispatch to fs or um, return a response
std::string RequestHandler::processRequest(const std::string& request) {
    std::istringstream iss(request);
    std::string cmd;
    iss >> cmd;

    if (cmd == "CREATE_DIR") {
        std::string dir; 
        iss >> dir;
        return fs.createDirectory(dir) ? "OK\n" : "ERR_CREATE\n";
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

    return "ERR_UNKNOWN_CMD\n";
}
