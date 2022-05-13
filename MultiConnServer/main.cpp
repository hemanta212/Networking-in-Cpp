#include <iostream>
#include <wS2tcpip.h>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::cerr;
using std::string;
using std::ostringstream;

int main() {

    // initialize winsock 
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsok = WSAStartup(ver, &wsData);
    if (wsok != 0) {
        cerr << "WSAStartup failed: cant initialize win sock" << "\r\n";
        return -1;
    }

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "Can't Create socket " << "\r\n";
        return -2;
    }

    // bind ip and port to the socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton ...

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // tell the winsock that socket is for listening
    listen(listening, SOMAXCONN);

    // initlialize a (file descriptor)fd set, empty it and add listening socket(file descriptor) to it
    fd_set master;
    FD_ZERO(&master);

    FD_SET(listening, &master);

    while (true) {
        fd_set copy = master;
       
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

        for (int i = 0; i < socketCount; i++) {
            SOCKET sock = copy.fd_array[i];
            if (sock == listening) {
                // Accept a new connection
                SOCKET client = accept(listening, nullptr, nullptr);
                // Send the welcome msg to connected client
                ostringstream ss;
                ss << "Welcome to the server! #" << client << "\r\n";
                string welcomeMsg = ss.str();
                send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

                ostringstream ssn;
                ssn << "Socket #" << client << " has joined!" << "\r\n";
                string broadcastMsg = ssn.str();
                for (unsigned int i = 0; i < master.fd_count; i++) {
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != listening) {
                            send(outSock, broadcastMsg.c_str(), broadcastMsg.size()+1, 0);
                        }
                    }

                // Add the new connection to the master fd set (connected sockets list)
                FD_SET(client, &master);
            }
            else {
                char buf[4096];
                ZeroMemory(buf, 4096);
                // Accept a new message
                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0) {
                    // drop the client
                    closesocket(sock);
                    FD_CLR(sock, &master);
                    ostringstream ss;
                    ss << "Socket #" << sock << ":" << " left the chat." << "\r\n";
                    for (unsigned int i = 0; i < master.fd_count; i++) {
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != listening) {
                            send(outSock, ss.str().c_str(), ss.str().size() + 1, 0);
                        }
                    }
                }
                else {
                // send msg to other client and not to the listening socket
                    for (unsigned int i = 0; i < master.fd_count; i++) {
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != listening && outSock != sock) {
                            // construct a string from a stream
                            ostringstream ss;
                            ss << "Socket #" << sock << ":" << buf << "\n";
                            string strOut = ss.str();
                            send(outSock, strOut.c_str(), strOut.size()+1, 0);
                        }
                    }
                }
            }
        }
    }

    // cleanup winsock
        WSACleanup();
        return 0;
}