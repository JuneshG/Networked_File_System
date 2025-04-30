# 🌐 AWS Deployed Simple Networked File System
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue?logo=c%2B%2B)
![Build](https://img.shields.io/badge/Build-g%2B%2B-success?logo=gnu)

A lightweight **TCP client-server file system** written in modern C++17.  
Clients can create directories, upload / download files, and list directory
contents remotely. The server supports multi-user login / registration and can be
deployed on an **AWS EC2** instance for world-wide access.

> **Course:** CSC 474/574 Computer Networks — Spring 2025  
> **Author:** Junesh Gautam  

---

## ✨  Key Features
| Capability | Example Command (from client) | Handler Module |
|------------|--------------------------------|----------------|
| Create directory | `CREATE_DIR reports` | `FileSystem::createDirectory()` |
| Remove directory | `DELETE_DIR reports` | `std::filesystem::remove_all()` |
| Write file       | `WRITE_FILE reports/summary.txt Hello` | `FileSystem::writeFile()` |
| List directory   | `LIST_FILES reports` | `FileSystem::listFiles()` |
| Register user    | `REGISTER alice pw123` | `UserManager::registerUser()` |
| Login user       | `LOGIN alice pw123` | `UserManager::login()` |

---

## 🖼️  Architecture Diagram

> ![image](https://github.com/user-attachments/assets/450a5236-ed11-4b42-b7e0-b056be85ae7f)


## Building 
### Linux (g++)

git clone https://github.com/<yourname>/aws-networked-fs.git \
cd aws-networked-fs \
g++ -std=c++17 Server.cpp FileSystem.cpp UserManager.cpp RequestHandler.cpp main.cpp -pthread -o server \
g++ -std=c++17 Client.cpp -o client

### Windows (MiNGW)

g++ -std=c++17 Server.cpp FileSystem.cpp UserManager.cpp RequestHandler.cpp main.cpp -lws2_32 -o server.exe
g++ -std=c++17 Client.cpp -lws2_32 -o client.exe

## 🏃‍♂️ Running Locally

#### Terminal 1
./server            # prints “Server listening …”

#### Terminal 2
./client            # connects to 127.0.0.1:8080

#### Example Session
> REGISTER alice pw123
Server: OK \
> CREATE_DIR docs \
Server: OK \
> WRITE_FILE docs/hi.txt Hello \
Server: OK \
> LIST_FILES docs \
Server: hi.txt

## ☁️ Deploying on AWS EC2
1. Launch Ubuntu 22.04 instance, open TCP 8080 in Security Group.

2. ssh -i key.pem ubuntu@<EC2-IP>

3. sudo apt update && sudo apt install -y g++ git

4. Clone repo & build (g++ … -pthread -o server).

5. Run nohup ./server & (keeps running after logout).

6. Edit Client.cpp → inet_addr("<EC2-IP>"), rebuild client locally, run.

Now you have a cloud-hosted file system. Multiple remote clients can connect simultaneously.


## 🧪 Test Checklist
| Test | Command(s) | Expected |
|------|------------|----------|
| Happy path | `CREATE_DIR demo` → `OK` | folder exists on server |
| File write | `WRITE_FILE demo/a.txt hi` | `OK`; server file holds text |
| List files | `LIST_FILES demo` | `a.txt` |
| Auth | `REGISTER bob pw` → `OK`; `LOGIN bob pw` → `OK`; wrong pass → `ERR_LOGIN` |
| Concurrency | two clients create dirs | both succeed |


## 💻 File Overview

| File | Purpose |
|------|---------|
| `Server.cpp / .hpp` | opens socket, spawns thread per client |
| `RequestHandler.cpp / .hpp` | parses each command, routes to modules |
| `FileSystem.cpp / .hpp` | wraps `<filesystem>` for mkdir / file I/O |
| `UserManager.cpp / .hpp` | in-memory user registration & login |
| `Client.cpp` | simple interactive test client |
| `docs/flow.svg` | architecture diagram |

## 🤝 Contributing
1. Fork → feature branch → PR.

2. Follow C++17 style, clang-format 14.

3. Include a brief test or demo in your PR description.

## 📜 License
MIT – free for personal and commercial use, just keep the notice.

