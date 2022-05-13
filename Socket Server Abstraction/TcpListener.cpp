#include <iostream>

#include "TcpListener.h"

CTcpListener::CTcpListener(std::string ipAddress, int port, MessageReceivedHandler handler)
: m_ipAddress(ipAddress), m_port(port), m_handler(handler)
{
    
}

CTcpListener::~CTcpListener() {
    Cleanup();
    }
    
// Send a message to the specified client
void CTcpListener::Send(int clientSocket, std::string msg) {
    send(clientSocket, msg.c_str(), msg.size(), 0);
}
    
// Init winsock
bool CTcpListener::Init() {
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    
    int wsInit = WSAStartup(ver, &data);
    if (wsInit != 0) {
        std::cerr << "WSAStartup failed with error: " << wsInit << std::endl;
        // TODO: inform caller about failure
        
    }
    return wsInit == 0;
}
    
    
// Main processing loop
void CTcpListener::Run() {
    char buf[MAX_BUFFER_SIZE];

    while (true) {
        // Create a listening socket
        SOCKET listening = CreateSocket();
        if (listening == INVALID_SOCKET) {
            std::cerr << "Failed to create socket" << std::endl;
            break;
        }
        // Wait for conn
        SOCKET client = WaitForConnection(listening);
        if (client != INVALID_SOCKET) {
            closesocket(listening);
            int bytesReceived = 0;
            // loop receive/send
            do {
               ZeroMemory(buf, MAX_BUFFER_SIZE);
               bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
               if (bytesReceived > 0) {
                   if (m_handler != NULL) {
                       m_handler(this, client, std::string(buf, 0, bytesReceived));
                   }
                   else {
                       std::cerr << "No handler set, m_handler NULL" << std::endl;
                   }
               }
            } while (bytesReceived > 0);

            std::cout << "No more data from client, closing.." << std::endl;
            closesocket(client);
        }else{
            std::cerr << "Failed to accept connection" << std::endl;
            break;
        }

    }
    
}
    
// send back message
    
// Cleanup
void CTcpListener::Cleanup() {
    WSACleanup();
}

// create a listening socket
SOCKET CTcpListener::CreateSocket() {
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening != INVALID_SOCKET) {
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(m_port);
        inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

        int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
        if (bindOk != SOCKET_ERROR) {
            int listenOk = listen(listening, SOMAXCONN);
            if (listenOk == SOCKET_ERROR) {
                std::cerr << "ListenOk failed with error: " << WSAGetLastError() << std::endl;
                return -1;
            }
        }
        else {
            std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
            return -1;
        }
    }
    else {
        std::cerr << "Socket Creation failed with error: " << WSAGetLastError() << std::endl;
        return -1;
    }
    return listening;
}
    
    
// wait for a connection
SOCKET CTcpListener::WaitForConnection(SOCKET listening) {
    SOCKET client = accept(listening, NULL, NULL);
    return client;
}

